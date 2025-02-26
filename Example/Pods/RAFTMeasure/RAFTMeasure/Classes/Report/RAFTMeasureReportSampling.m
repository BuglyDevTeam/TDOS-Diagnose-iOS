//
//  RAFTMeasureReportSampling.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureReportSampling.h"
#import "RAFTMeasureUtils.h"
#import "RAFTMeasureComInfo.h"
#import "RAFTMeasureLogger.h"

@interface RAFTMeasureReportSampling ()

// 启动上报记录：在APP期间每个组件仅上报一次。
@property (nonatomic, strong) NSMutableArray *startUpRecordList;

@end

@implementation RAFTMeasureReportSampling

- (instancetype)init {
    self = [super init];
    if (self) {
        _startUpRecordList = [NSMutableArray array];
    }
    return self;
}

#pragma mark - SLI上报抽样逻辑
- (RAFTMEASURE_SAMPLING_RESULT)sliSamplingResult:(RAFTMeasureComInfo *)comInfo
                                             key:(NSString *)key
                                    samplingRate:(int)samplingRate {
    // 新的一天需要先清空之前的记录
    [self resetSLISamplingOnANewDay];
    
    // SLI上报次数限制
    RAFTMEASURE_SAMPLING_RESULT result = [self checkSLILimit:comInfo key:key];
    if (result != RAFTMEASURE_SAMPLING_RESULT_REPORT) {
        return result;
    }
    
    // SLI上报抽样：业务传递的抽样率限制
    if (([RAFTMeasureUtils randomNumber0_1] * 100 + 1) > samplingRate) {
        return RAFTMEASURE_SAMPLING_RESULT_SLI_COMRATE_LIMIT;
    }
    
    // SLI上报总体抽样：如果业务抽样率高于规定的抽样率，那么再进行一次全局抽样。
    if (samplingRate > RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE && (([RAFTMeasureUtils randomNumber0_1] * 100 + 1) > RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE)) {
        return RAFTMEASURE_SAMPLING_RESULT_SLI_RATE_LIMIT;
    }
    
    // 更新SLI上报次数记录
    [self writeSLISampling:comInfo key:key];
    
    return RAFTMEASURE_SAMPLING_RESULT_REPORT;
}

- (RAFTMEASURE_SAMPLING_RESULT)checkSLILimit:(RAFTMeasureComInfo *)comInfo key:(NSString *)key {
    // 读取已有记录
    NSDictionary *record = [self readSLISampling];
    
    // 如果record为空，说明NSUserDefaults异常，则认为APP受限，不允许上报。
    if (!record) {
        return RAFTMEASURE_SAMPLING_RESULT_SLI_APP_LIMIT;
    }
    
    // 超过单App上报次数
    int appReportCount = [record[RAFTMEASURE_SAMPLING_APP_REPORT_COUNT] intValue];
    if (appReportCount > RAFTMEASURE_SAMPLING_SLI_MAXAPPREPORT_COUNT) {
        return RAFTMEASURE_SAMPLING_RESULT_SLI_APP_LIMIT;
    }
    // 超过组件上报次数
    int comReportCount = [record[[comInfo comUniKey]] intValue];
    if (comReportCount > RAFTMEASURE_SAMPLING_SLI_MAXCOMREPORT_COUNT) {
        return RAFTMEASURE_SAMPLING_RESULT_SLI_COM_LIMIT;
    }
    // 超过Key上报次数
    int keyReportCount = [record[[comInfo comUniKeyWithReportKey:key]] intValue];
    if (keyReportCount > RAFTMEASURE_SAMPLING_SLI_MAXCOMWITHKEYREPORT_COUNT) {
        return RAFTMEASURE_SAMPLING_RESULT_SLI_COMWITHKEY_LIMIT;
    }
    
    return RAFTMEASURE_SAMPLING_RESULT_REPORT;
}

#pragma mark - SLI抽样记录存储
- (NSDictionary *)readSLISampling {
    // 读取已有记录
    NSDictionary *record = [[NSUserDefaults standardUserDefaults] dictionaryForKey:RAFTMEASURE_SAMPLING_RECORD_SPACE];
    [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s record = %@", __func__, record.description]];
    return record;
}

- (void)writeSLISampling:(RAFTMeasureComInfo *)comInfo key:(NSString *)key {
    // 读取已有记录
    NSMutableDictionary *record = [NSMutableDictionary dictionary];
    NSDictionary *oldRecord = [self readSLISampling];
    if (oldRecord) {
        [record addEntriesFromDictionary:oldRecord];
    }
    // 更新APP上报次数
    int oldAppReportCount = [record[RAFTMEASURE_SAMPLING_APP_REPORT_COUNT] intValue];
    record[RAFTMEASURE_SAMPLING_APP_REPORT_COUNT] = @(oldAppReportCount + 1);
    // 更新组件上报次数
    int oldComReportCount = [record[[comInfo comUniKey]] intValue];
    record[[comInfo comUniKey]] = @(oldComReportCount + 1);
    // 更新key上报次数
    int oldKeyReportCount = [record[[comInfo comUniKeyWithReportKey:key]] intValue];
    record[[comInfo comUniKeyWithReportKey:key]] = @(oldKeyReportCount + 1);
    // 更新记录时间
    record[RAFTMEASURE_SAMPLING_REPORT_DATE] = [RAFTMeasureUtils currDate];
    // 写⼊更新的信息
    [[NSUserDefaults standardUserDefaults] setObject:[NSDictionary dictionaryWithDictionary:record] forKey:RAFTMEASURE_SAMPLING_RECORD_SPACE];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)resetSLISampling {
    NSMutableDictionary *resetRecord = [NSMutableDictionary dictionary];
    resetRecord[RAFTMEASURE_SAMPLING_REPORT_DATE] = [RAFTMeasureUtils currDate];
    [[NSUserDefaults standardUserDefaults] setObject:resetRecord forKey:RAFTMEASURE_SAMPLING_RECORD_SPACE];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)resetSLISamplingOnANewDay {
    NSDictionary *record = [self readSLISampling];
    if (record) {
        NSDate *currDate = [RAFTMeasureUtils currDate];
        NSDate *lastDate = record[RAFTMEASURE_SAMPLING_REPORT_DATE];
        BOOL isSameDay = [RAFTMeasureUtils isSameDay:currDate bDate:lastDate];
        if (!isSameDay) {
            // 清空数据
            [self resetSLISampling];
        }
    } else {
        // 初始化空数据：同时为了兜底当NSUserDefaults异常，所有的数据读取都为null的情况。
        [[RAFTMeasureLogger sharedInstance] raftMeasureWarnLog:[NSString stringWithFormat:@"%s record is null", __func__]];
        [self resetSLISampling];
    }
}

#pragma mark - StartUp上报抽样逻辑
- (RAFTMEASURE_SAMPLING_RESULT)startUpSamplingResult:(RAFTMeasureComInfo *)comInfo samplingRate:(int)samplingRate {
    @synchronized (self.startUpRecordList) {
        // 启动上报次数限制
        if ([self.startUpRecordList containsObject:[comInfo comUniKey]]) {
            return RAFTMEASURE_SAMPLING_RESULT_STARTUP_REPEAT_LIMIT;
        }
        // 启动上报抽样率限制
        if (([RAFTMeasureUtils randomNumber0_1] * 100 + 1) > samplingRate) {
            return RAFTMEASURE_SAMPLING_RESULT_STARTUP_RATE_LIMIT;
        }
        // 添加进启动上报列表
        [self.startUpRecordList addObject:[comInfo comUniKey]];
        
        return RAFTMEASURE_SAMPLING_RESULT_REPORT;
    }
}

@end
