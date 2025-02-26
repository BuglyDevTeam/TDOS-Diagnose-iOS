//
//  TDLogUploadFileUploader.h
//  TDOS-Diagnose
//
//  Created by raycgwang on 2022/1/17.
//  Copyright © 2021 Tencent. All rights reserved.
//  Derived from VBLogUploadiOS
//  

#import <Foundation/Foundation.h>
@class TDLogSDKConfig;
@class TDLogUploadTaskModel;
@class TDLogStateReportManager;
@protocol TDLogUploadTaskPersistProtocol;
@protocol TDLogUploadRetryStrategyProtocol;


NS_ASSUME_NONNULL_BEGIN

/// 上传任务管理类
@interface TDLogUploadFileUploader : NSObject

/// 初始化上传模块
/// @param sdkConfig SDK设置
/// @param taskInfoPersist 持久化对象
/// @param retryStrategy 重试策略对象
/// @param stateReporter 状态上报对象
/// @param workQueue 工作任务队列
- (instancetype)initWithSDKConfig:(TDLogSDKConfig *)sdkConfig
                    stateReporter:(TDLogStateReportManager *)stateReporter
                        workQueue:(dispatch_queue_t)workQueue
                       persistIMP:(id<TDLogUploadTaskPersistProtocol>)taskInfoPersist
                    retryStrategy:(id<TDLogUploadRetryStrategyProtocol>)retryStrategy;

/// Use \c initWithSDKConfig:... to Initialize
- (instancetype)init NS_UNAVAILABLE;
/// Use \c initWithSDKConfig:... to Initialize
+ (instancetype)new NS_UNAVAILABLE;


/// 同步上传文件
/// @param info 任务信息
- (void)uploadFile:(TDLogUploadTaskModel *)info;

/// 启动本地持久化的所有未完成的任务
/// @param guid 用户ID
- (void)executeAllUnFinishedTask:(NSString *)guid;

@end

NS_ASSUME_NONNULL_END
