//   
//  RFKTConnectionManager.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "RFKTMsg.h"
#import "RFKTConnectionConfig.h"

NS_ASSUME_NONNULL_BEGIN

@class RFKTConnectionManager;

@protocol RFKTConnectionManagerDelegate <NSObject>

/// Connection established callback
/// @param conn the manager
- (void)onConnected:(RFKTConnectionManager *)conn;

/// Connection closed callback
/// @param conn the manager
- (void)onDisconnected:(RFKTConnectionManager *)conn;

/// Connection received msg callback
/// @param responseMsg RFKTBaseMsg object
/// @param conn the manager
- (void)onMessageReceived:(RFKTBaseMsg *)responseMsg fromConnection:(RFKTConnectionManager *)conn;

@end


/// Manager of remote connection
@interface RFKTConnectionManager : NSObject

/// RFKTConnectionManagerDelegate
@property (nonatomic, weak, nullable) id<RFKTConnectionManagerDelegate> delegate;

/// 连接配置
@property (nonatomic, strong, readonly) RFKTConnectionConfig *config;

///  True if there's an open connection.
@property (nonatomic, assign, readonly) BOOL isOpen;

/// Establish a connection to the server.
- (void)startConnectionWithConfig:(RFKTConnectionConfig *)config;

/// Closes an open connection to the server.
- (void)stopConnection;

/** 发送数据 */
- (void)sendMessage:(RFKTBaseMsg *)msg;


@end

NS_ASSUME_NONNULL_END
