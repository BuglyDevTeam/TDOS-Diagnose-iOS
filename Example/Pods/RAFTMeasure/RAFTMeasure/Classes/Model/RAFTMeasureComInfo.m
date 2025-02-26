//
//  RAFTMeasureComInfo.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureComInfo.h"
#import "RAFTMeasureUtils.h"
#import "RAFTMeasureReportDefines.h"

@implementation RAFTMeasureComInfo

- (instancetype)initWithComName:(NSString *)comName
                         comVer:(NSString *)comVer {
    self = [super init];
    if (self) {
        _comName = comName;
        _comVer = comVer;
    }
    return self;
}

- (BOOL)isDataValid {
    return (self.comName.length > 0 && self.comVer.length > 0);
}

- (NSString *)comUniKey {
    return [NSString stringWithFormat:@"%@_%@", self.comName, self.comVer];
}

- (NSString *)comUniKeyWithReportKey:(NSString *)reportKey {
    return [NSString stringWithFormat:@"%@_%@", [self comUniKey], reportKey];
}

- (NSDictionary *)reportParams {
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    params[RAFTMEASURE_PARAMKEY_COM_NAME] = [RAFTMeasureUtils safeString:self.comName];
    params[RAFTMEASURE_PARAMKEY_COM_VER] = [RAFTMeasureUtils safeString:self.comVer];
    return params;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"RAFTMeasureComInfo[comName = %@, comVer = %@]", self.comName, self.comVer];
}

@end
