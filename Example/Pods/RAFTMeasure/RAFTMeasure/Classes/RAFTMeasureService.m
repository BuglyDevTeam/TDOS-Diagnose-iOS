//
//  RAFTMeasureService.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureService.h"
#import "RAFTMeasureSLIReportItem.h"
#import "RAFTMeasureStartUpReportItem.h"
#import "RAFTMeasureComInfo.h"
#import "RAFTMeasureAppInfo.h"
#import "RAFTMeasureDefines.h"
#import "RAFTMeasureUtils.h"
#import "RAFTMeasureReporter.h"
#import "RAFTMeasureReportSampling.h"
#import "RAFTMeasureLogger.h"

@interface RAFTMeasureService ()

// 上报器
@property (nonatomic, strong) RAFTMeasureReporter *reporter;

// 上报抽样器
@property (nonatomic, strong) RAFTMeasureReportSampling *reportSampling;

// 上报串行队列
@property (nonatomic, strong) dispatch_queue_t queue;

// APP信息
@property (nonatomic, strong) RAFTMeasureAppInfo *appInfo;

@end

@implementation RAFTMeasureService

+ (instancetype)sharedInstance {
    static dispatch_once_t once;
    static RAFTMeasureService *service;
    dispatch_once(&once, ^{
        service = [[RAFTMeasureService alloc] init];
    });
    return service;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        // 初始化上报器
        _reporter = [[RAFTMeasureReporter alloc] init];
        // 初始化上报抽样器
        _reportSampling = [[RAFTMeasureReportSampling alloc] init];
        // 初始化上报串行队列
        _queue = dispatch_queue_create("RAFTMeasureServiceQueue", DISPATCH_QUEUE_SERIAL);
        // 仅在单例初始化时，读取一次APP信息。
        _appInfo = [[RAFTMeasureAppInfo alloc] init];
        _appInfo.appId = [RAFTMeasureUtils safeString:NSBundle.mainBundle.bundleIdentifier];
        _appInfo.appName = [RAFTMeasureUtils safeString:[NSBundle.mainBundle objectForInfoDictionaryKey:@"CFBundleDisplayName"]];
        _appInfo.appVer = [RAFTMeasureUtils safeString:[NSBundle.mainBundle objectForInfoDictionaryKey:@"CFBundleShortVersionString"]];
#if DEBUG
        _appInfo.appDebug = YES;
#else
        _appInfo.appDebug = NO;
#endif
    }
    return self;
}

#pragma mark - Crash监控
- (void)enableCrashMonitor:(RAFTMeasureComInfo *)comInfo {
    dispatch_async(self.queue, ^{
        [[RAFTMeasureLogger sharedInstance] raftMeasureInfoLog:[NSString stringWithFormat:@"%s comInfo = %@", __func__, comInfo.description]];
        NSString *componentId = comInfo.comName;
        NSString *version = comInfo.comVer;
        if (componentId && version) {
            NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
            // 读取已有信息并记录
            NSDictionary *dict = [[NSUserDefaults standardUserDefaults] dictionaryForKey:RAFTMEASURE_CRASH_MONITOR_SP_NAME];
            if (dict) {
                [dictionary addEntriesFromDictionary:dict];
            }
            // 若版本号没有变化，则无需重复写入。
            NSString *lastVer = [dictionary objectForKey:componentId];
            if (lastVer && [lastVer isEqualToString:version]) {
                return;
            }
            // 添加当前组件的唯⼀标识和版本
            [dictionary setValue:version forKey:componentId];
            // 写⼊更新的信息
            [[NSUserDefaults standardUserDefaults] setObject:[NSDictionary dictionaryWithDictionary:dictionary] forKey:RAFTMEASURE_CRASH_MONITOR_SP_NAME];
            // 组件启动上报
            [self reportStartup:comInfo];
        } else {
            [[RAFTMeasureLogger sharedInstance] raftMeasureErrorLog:[NSString stringWithFormat:@"%s Crash Enable Arguments Error!", __func__]];
        }
    });
}

#pragma mark - 成功率上报
- (void)reportSuccess:(RAFTMeasureComInfo *)comInfo
                  key:(NSString *)key
              success:(BOOL)success {
    [self reportSLI:comInfo
            sliName:key
           sliValue:[RAFTMeasureUtils successToString:success]
            sliType:RAFTMEASURE_SLI_TYPE_SUCCESS
       samplingRate:RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE];
}

- (void)reportSuccess:(RAFTMeasureComInfo *)comInfo
                  key:(NSString *)key
              success:(BOOL)success
         samplingRate:(int)samplingRate {
    [self reportSLI:comInfo
            sliName:key
           sliValue:[RAFTMeasureUtils successToString:success]
            sliType:RAFTMEASURE_SLI_TYPE_SUCCESS
       samplingRate:samplingRate];
}

#pragma mark - 平均值上报
- (void)reportAvg:(RAFTMeasureComInfo *)comInfo
              key:(NSString *)key
            value:(long)value {
    [self reportSLI:comInfo
            sliName:key
           sliValue:[@(value) stringValue]
            sliType:RAFTMEASURE_SLI_TYPE_AVG
       samplingRate:RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE];
}

- (void)reportAvg:(RAFTMeasureComInfo *)comInfo
              key:(NSString *)key
            value:(long)value
     samplingRate:(int)samplingRate {
    [self reportSLI:comInfo
            sliName:key
           sliValue:[@(value) stringValue]
            sliType:RAFTMEASURE_SLI_TYPE_AVG
       samplingRate:samplingRate];
}

#pragma mark - 分布值上报
- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                     value:(long)value {
    [self reportSLI:comInfo
            sliName:key
           sliValue:[@(value) stringValue]
            sliType:RAFTMEASURE_SLI_TYPE_DISTRIBUTION
       samplingRate:RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE];
}

- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                    sValue:(NSString *)sValue {
    [self reportSLI:comInfo
            sliName:key
           sliValue:sValue
            sliType:RAFTMEASURE_SLI_TYPE_DISTRIBUTION
       samplingRate:RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE];
}

- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                     value:(long)value
              samplingRate:(int)samplingRate {
    [self reportSLI:comInfo
            sliName:key
           sliValue:[@(value) stringValue]
            sliType:RAFTMEASURE_SLI_TYPE_DISTRIBUTION
       samplingRate:samplingRate];
}

- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                    sValue:(NSString *)sValue
              samplingRate:(int)samplingRate {
    [self reportSLI:comInfo
            sliName:key
           sliValue:sValue
            sliType:RAFTMEASURE_SLI_TYPE_DISTRIBUTION
       samplingRate:samplingRate];
}

#pragma mark - SLI上报收归接口
- (void)reportSLI:(RAFTMeasureComInfo *)comInfo
          sliName:(NSString *)sliName
         sliValue:(NSString *)sliValue
          sliType:(RAFTMEASURE_SLI_TYPE)sliType
     samplingRate:(int)samplingRate {
    dispatch_async(self.queue, ^{
        // 打印输入参数
        [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s SLI Report Begin: comInfo = %@, sliName = %@, sliValue = %@, sliType = %@, samplingRate = %d", __func__, comInfo.description, sliName, sliValue, sliType, samplingRate]];
        
        // 参数合法性校验：不合法将无法上报
        if (![comInfo isDataValid]
            || sliName.length <= 0
            || sliValue.length <= 0
            || sliType.length <= 0
            || !(samplingRate >= 0 && samplingRate <= 100)) {
            [[RAFTMeasureLogger sharedInstance] raftMeasureErrorLog:[NSString stringWithFormat:@"%s SLI Report Arguments Error!", __func__]];
            return;
        }
        
        // 抽样逻辑检测
        RAFTMEASURE_SAMPLING_RESULT samplingResult = [self.reportSampling
                                                      sliSamplingResult:comInfo
                                                      key:sliName
                                                      samplingRate:samplingRate];
        if (samplingResult != RAFTMEASURE_SAMPLING_RESULT_REPORT) {
            // 抽样逻辑不通过，不进行上报
            [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s SLI Report Sampling Limit End: samplingResult = %zd, comInfo = %@, sliName = %@, sliValue = %@, sliType = %@, samplingRate = %d", __func__, samplingResult, comInfo.description, sliName, sliValue, sliType, samplingRate]];
        } else {
            // 抽样逻辑通过，进行上报
            RAFTMeasureSLIReportItem *item = [[RAFTMeasureSLIReportItem alloc] init];
            item.comInfo = (id<RAFTMeasureReportParamProtocol>)comInfo;
            item.sliName = sliName;
            item.sliValue = sliValue;
            item.sliType = sliType;
            item.appInfo = self.appInfo;
            [self.reporter report:item];
            [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s SLI Report Success End: comInfo = %@, sliName = %@, sliValue = %@, sliType = %@, samplingRate = %d, appInfo = %@", __func__, comInfo.description, sliName, sliValue, sliType, samplingRate, self.appInfo.description]];
            // 组件启动上报
            [self reportStartup:comInfo];
        }
    });
}

#pragma mark - StartUp上报
- (void)reportStartup:(RAFTMeasureComInfo *)comInfo {
    dispatch_async(self.queue, ^{
        // 打印输入参数
        [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s Startup Report Begin: comInfo = %@", __func__, comInfo.description]];
        
        // 参数合法性校验：不合法将无法上报
        if (![comInfo isDataValid]
            || !(RAFTMEASURE_SAMPLING_STARTUP_DEFAULT_RATE >= 0 && RAFTMEASURE_SAMPLING_STARTUP_DEFAULT_RATE <= 100)) {
            [[RAFTMeasureLogger sharedInstance] raftMeasureErrorLog:[NSString stringWithFormat:@"%s Startup Report Arguments Error!", __func__]];
            return;
        }
        
        // 抽样逻辑检测
        RAFTMEASURE_SAMPLING_RESULT samplingResult = [self.reportSampling
                                                      startUpSamplingResult:comInfo
                                                      samplingRate:RAFTMEASURE_SAMPLING_STARTUP_DEFAULT_RATE];
        if (samplingResult != RAFTMEASURE_SAMPLING_RESULT_REPORT) {
            // 抽样逻辑不通过，不进行上报
            [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s Startup Report Sampling Limit End: samplingResult = %zd, comInfo = %@", __func__, samplingResult, comInfo.description]];
        } else {
            // 抽样逻辑通过，进行上报
            RAFTMeasureStartUpReportItem *item = [[RAFTMeasureStartUpReportItem alloc] init];
            item.comInfo = (id<RAFTMeasureReportParamProtocol>)comInfo;
            item.samplingRate = [@(RAFTMEASURE_SAMPLING_STARTUP_DEFAULT_RATE) stringValue];
            item.appInfo = self.appInfo;
            [self.reporter report:item];
            [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s Startup Report Success End: comInfo = %@, samplingRate = %@, appInfo = %@", __func__, comInfo.description, item.samplingRate, self.appInfo.description]];
        }
    });
}

#pragma mark - 宿主APP专用
- (RAFTMeasureAppInfo *)appInfo {
    return _appInfo;
}

- (void)setLogDelegate:(id<RAFTMeasureLogProtocol>)logDelegate {
    [[RAFTMeasureLogger sharedInstance] setLogDelegate:logDelegate];
}

- (void)setIsDebug:(BOOL)isDebug {
    [[RAFTMeasureLogger sharedInstance] setIsDebug:isDebug];
}

@end
