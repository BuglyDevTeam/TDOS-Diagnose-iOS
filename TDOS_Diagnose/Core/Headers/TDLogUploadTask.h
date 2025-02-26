//
//  TDLogUploadTask.h
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/24.
//  Modified by by raycgwang on 2021/12/29.
//
//  Copyright © 2021 Tencent. All rights reserved.
//  Derived from VBLogSDKiOS

#import <Foundation/Foundation.h>
@class TDLogUploadTaskModel;
@class TDLogStateReportManager;


NS_ASSUME_NONNULL_BEGIN

@protocol TDLogUploadTaskCallback <NSObject>

@required

/// 开始上传时
/// @param info 任务信息
- (void)onUploadTaskBegin:(TDLogUploadTaskModel *)info;

/// 上传结束时
/// @param info 任务信息
/// @param isSuccess 是否成功
- (void)onUploadTaskFinish:(TDLogUploadTaskModel *)info result:(BOOL)isSuccess;

/// 状态上报开始时
/// @param info 任务信息
- (void)onStateSyncBegin:(TDLogUploadTaskModel *)info;

/// 状态上报结束时
/// @param info 任务信息
/// @param isSuccess 是否成功
/// @param errMsg 错误信息
- (void)onStateSyncFinish:(TDLogUploadTaskModel *)info result:(BOOL)isSuccess errMsg:(nullable NSString *)errMsg;

@end


@interface TDLogUploadTask : NSObject

/**
 TDLogUploadTask初始化
 @param uploadTaskInfo 任务详细信息模型
 @param warpUploadCallback 上传开始、成功、失败回调
 @return TDLogUploadTask实例
 */
- (nonnull instancetype)initWithUploadTaskInfo:(TDLogUploadTaskModel *)uploadTaskInfo
                                 stateReporter:(TDLogStateReportManager *)stateReporter
                           warpUploadCallback:(id <TDLogUploadTaskCallback>)warpUploadCallback;

/// Use \c initWithUploadTaskInfo:... to initialize
- (instancetype)init NS_UNAVAILABLE;
/// Use \c initWithUploadTaskInfo:... to initialize
+ (instancetype)new NS_UNAVAILABLE;

/// 执行任务
- (void)execute;

@end

NS_ASSUME_NONNULL_END
