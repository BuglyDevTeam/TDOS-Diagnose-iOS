//   
//  RFKTManager+RemoteConfig.h
//  RaftKit
//  
//  Created by raycgwang on 2022/7/20.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTManager.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSString * const kRFKTConfigReqInfo;
FOUNDATION_EXTERN NSString * const kRFKTConfigTipsInfo;

@interface RFKTManager (RemoteConfig)

/// request remote config
- (void)requestRemoteConfigIfNeeded;

@end

NS_ASSUME_NONNULL_END
