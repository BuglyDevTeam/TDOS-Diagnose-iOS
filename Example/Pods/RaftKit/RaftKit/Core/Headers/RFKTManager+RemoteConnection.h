//   
//  RFKTManager+RemoteConnection.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTManager.h"
#import "RFKTConnectionManager.h"
#import "RFKTConnection.h"
#import "RFKTConnectionConfig.h"


NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const RFKTRemoteConnection_Connected;
FOUNDATION_EXPORT NSString *const RFKTRemoteConnection_Disconnected;

/// Manage remote connection
@interface RFKTManager (RemoteConnection) <RFKTConnectionManagerDelegate, RFKTConnection>

/// 默认的连接管理类
@property (nonatomic, strong, readonly) RFKTConnectionManager *defaultConnectionManager;

/// 初始化远程连接
- (void)setupRemoteConnectionIfNeeded;

/// Start
- (void)startRemoteConnection;

/// Stop
- (void)stopRemoteConnection;

/// Status
- (BOOL)isRemoteConnected;


#pragma mark - Connection Config

/// 当前连接配置信息
- (RFKTConnectionConfig *)currentConnectionConfig;

/// 设置远程连接参数信息
/// @param config 连接设置
- (void)setConnectionConfig:(RFKTConnectionConfig *)config;

@end

@interface RFKTManager (RemoteSessionInfo)

/// 会话“房间”ID，后续待扩展更多信息，如桌面端列表等
/// 当前策略：该ID由调试平台分配，SDK生命周期内保持不变，App杀进程后失效。
@property (nonatomic, nullable, strong) NSString *roomID;

@end


NS_ASSUME_NONNULL_END
