//
//  RAFTMeasureStartUpReportItem.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureStartUpReportItem.h"
#import "RAFTMeasureUtils.h"
#import "RAFTMeasureReportDefines.h"
#import "RAFTMeasureDefines.h"

@implementation RAFTMeasureStartUpReportItem

- (instancetype)initWithComInfo:(id<RAFTMeasureReportParamProtocol>)comInfo
                   samplingRate:(NSString *)samplingRate
                        appInfo:(id<RAFTMeasureReportParamProtocol>)appInfo {
    self = [super init];
    if (self) {
        _comInfo = comInfo;
        _samplingRate = samplingRate;
        _appInfo = appInfo;
    }
    return self;
}

- (NSDictionary *)reportParams {
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    if (self.comInfo && [self.comInfo respondsToSelector:@selector(reportParams)]) {
        [params addEntriesFromDictionary:[self.comInfo reportParams]];
    }
    params[RAFTMEASURE_PARAMKEY_RATE] = [RAFTMeasureUtils safeString:self.samplingRate];
    params[RAFTMEASURE_PARAMKEY_SLI_TYPE] = [RAFTMeasureUtils safeString:RAFTMEASURE_SLI_TYPE_STARTUP];
    if (self.appInfo && [self.appInfo respondsToSelector:@selector(reportParams)]) {
        [params addEntriesFromDictionary:[self.appInfo reportParams]];
    }
    return params;
}

@end
