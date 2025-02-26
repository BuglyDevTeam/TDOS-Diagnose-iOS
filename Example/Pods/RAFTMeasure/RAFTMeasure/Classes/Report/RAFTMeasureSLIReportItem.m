//
//  RAFTMeasureSLIReportItem.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureSLIReportItem.h"
#import "RAFTMeasureUtils.h"
#import "RAFTMeasureReportDefines.h"

@implementation RAFTMeasureSLIReportItem

- (instancetype)initWithComInfo:(id<RAFTMeasureReportParamProtocol>)comInfo
                        sliName:(NSString *)sliName
                       sliValue:(NSString *)sliValue
                        sliType:(RAFTMEASURE_SLI_TYPE)sliType
                        appInfo:(id<RAFTMeasureReportParamProtocol>)appInfo {
    self = [super init];
    if (self) {
        _comInfo = comInfo;
        _sliName = sliName;
        _sliValue = sliValue;
        _sliType = sliType;
        _appInfo = appInfo;
    }
    return self;
}

- (NSDictionary *)reportParams {
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    if (self.comInfo && [self.comInfo respondsToSelector:@selector(reportParams)]) {
        [params addEntriesFromDictionary:[self.comInfo reportParams]];
    }
    params[RAFTMEASURE_PARAMKEY_SLI_NAME] = [RAFTMeasureUtils safeString:self.sliName];
    params[RAFTMEASURE_PARAMKEY_SLI_VALUE] = [RAFTMeasureUtils safeString:self.sliValue];
    params[RAFTMEASURE_PARAMKEY_SLI_TYPE] = [RAFTMeasureUtils safeString:self.sliType];
    if (self.appInfo && [self.appInfo respondsToSelector:@selector(reportParams)]) {
        [params addEntriesFromDictionary:[self.appInfo reportParams]];
    }
    return params;
}

@end
