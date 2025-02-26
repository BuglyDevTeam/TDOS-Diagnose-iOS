//   
//  RFKTConnectionConfig.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/5.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Configurations of remote connection
@interface RFKTConnectionConfig : NSObject

/// Address of server, such as (ws://www.raftkit.com/ws).
@property (nonatomic, copy) NSString *remoteAddr;

/// A secret msg that user choosed for connection security.
@property (nonatomic, copy) NSString *userToken;

/// Maximum size of a single packet, usually limited by Server.
@property (nonatomic, assign) NSUInteger maxPackageLength;


/// whether the config is equal
/// @param config RFKTConnectionConfig
- (BOOL)isEqualToConfig:(RFKTConnectionConfig *)config;

@end

NS_ASSUME_NONNULL_END
