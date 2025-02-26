//   
//  TDLogConfigRequestManager.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/29.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogConfigServerModels.h"
@class TDLogSDKConfig;

NS_ASSUME_NONNULL_BEGIN

/// 配置请求代理
@protocol TDLogConfigRequestDelegate <NSObject>

@required

/// 收到需要重置染色级别的命令
- (void)onReceiveNeedResetColorLevelCmd;

/// 收到染色配置命令
/// @param level 日志级别
/// @param endtime 结束时间戳
/// @param guid 用户ID
- (void)onReceiveColorLogCmdWithLevel:(TDLogServerDefColorLevel)level endTimestamp:(time_t)endtime forGuid:(NSString *)guid;

/// 收到捞日志命令
/// @param cmds 命令数组
/// @param guid 用户ID
- (void)onReceiveUploadLogCmds:(NSArray<TDLogConfigPullLogCmdDetailInfo *> *)cmds forGuid:(NSString *)guid;

/// 原始回包，提供状态上报时机
/// @param colorCmd 染色信息
/// @param pullCmds 捞日志信息
/// @param guid 用户ID
- (void)onConfigUpdatedWithColorCmd:(nullable TDLogConfigColorInfo *)colorCmd
                      orPullLogCmds:(nullable NSArray<TDLogConfigPullLogCmdDetailInfo *> *)pullCmds
                            forGuid:(NSString *)guid;

@end


#pragma mark -

/// 日志捞取染色配置拉取管理
@interface TDLogConfigRequestManager : NSObject

@property (nonatomic, weak) id<TDLogConfigRequestDelegate> delegate;

/// 初始化方法
/// @param sdkConfig SDK配置
/// @param delegate 代理
- (instancetype)initWithSDKConfig:(TDLogSDKConfig *)sdkConfig andDelegate:(id<TDLogConfigRequestDelegate>)delegate;

/// Use \c initWithSDKConfig: to initialize
- (instancetype)init NS_UNAVAILABLE;

/// Use \c initWithSDKConfig: to initialize
+ (instancetype)new NS_UNAVAILABLE;


/// 发起捞日志配置查询请求
/// @param delayTime 延迟时间
- (void)requestLogConfigIfNeededWithDelay:(int64_t)delayTime;

/// 强制联网发起请求，忽略其他限频规则，如Push命令触发场景。
- (void)requestUploadLogConfigByForce;

@end

NS_ASSUME_NONNULL_END
