//
//  RAFTMeasureAppInfo.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureAppInfo.h"
#import "RAFTMeasureUtils.h"
#import "RAFTMeasureReportDefines.h"

@implementation RAFTMeasureAppInfo

- (instancetype)initWithAppId:(NSString *)appId
                      appName:(NSString *)appName
                       appVer:(NSString *)appVer
                     appDebug:(BOOL)appDebug {
    self = [super init];
    if (self) {
        _appId = appId;
        _appName = appName;
        _appVer = appVer;
        _appDebug = appDebug;
    }
    return self;
}

- (BOOL)isDataValid {
    return (self.appId.length > 0 && self.appName.length > 0 && self.appVer.length > 0);
}

- (NSDictionary *)reportParams {
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    params[RAFTMEASURE_PARAMKEY_APP_ID] = [RAFTMeasureUtils safeString:self.appId];
    params[RAFTMEASURE_PARAMKEY_APP_NAME] = [RAFTMeasureUtils safeString:self.appName];
    params[RAFTMEASURE_PARAMKEY_APP_VER] = [RAFTMeasureUtils safeString:self.appVer];
    params[RAFTMEASURE_PARAMKEY_APP_DEBUG] = self.appDebug ? @"1" : @"0";
    return params;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"RAFTMeasureAppInfo[appId = %@, appName = %@, appVer = %@]", self.appId, self.appName, self.appVer];
}

@end
