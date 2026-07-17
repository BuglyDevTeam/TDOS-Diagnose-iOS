//   
//  TDLogDataReport.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/5/28.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
@class TDLogUploadTaskModel;
@class TDLogConfigPullTask;

NS_ASSUME_NONNULL_BEGIN

@interface TDLogDataReport : NSObject

/// Singleton
+ (instancetype)sharedInstance;

/// Report for bugly
+ (void)setupSDKInfoForBuglyReport;

#pragma mark - Business Report

/// 上报日志配置拉取结果
/// @param isSuccess 是否成功
/// @param taskInfo 任务信息
/// @param pullCmdsCount 捞日志命令数量
/// @param hasColorCmd 是否有染色命令
+ (void)reportLogConfigPullResult:(BOOL)isSuccess
                         taskInfo:(TDLogConfigPullTask *)taskInfo
                    pullCmdsCount:(int)pullCmdsCount
                      hasColorCmd:(BOOL)hasColorCmd
                        respError:(nullable NSError *)error;

/// 上报打包结束
/// @param isSuccess 是否成功
/// @param taskInfo 任务详情
+ (void)reportFilePackResult:(BOOL)isSuccess taskInfo:(TDLogUploadTaskModel *)taskInfo;

/// 上报日志文件上传结果
/// @param isSuccess 是否成功
/// @param taskInfo 任务详情
+ (void)reportLogUploadResult:(BOOL)isSuccess taskInfo:(TDLogUploadTaskModel *)taskInfo;

/// 上报状态同步结束
/// @param isSyncSuccess 同步是否成功
/// @param isUploadSuccess 上传是否成功
/// @param isFinishState 是否为最终结束状态
+ (void)reportLogStateSyncResult:(BOOL)isSyncSuccess
                    uploadResult:(BOOL)isUploadSuccess
                   isFinishState:(BOOL)isFinishState
                        taskInfo:(TDLogUploadTaskModel *)taskInfo;

/// 上报重试的任务数量
/// @param retryTaskCount 重试任务数
/// @param guid 用户ID
+ (void)reportLogTaskRetry:(NSString *)guid taskCount:(int)retryTaskCount;

/// 上报处于染色状态
/// @param guid 用户ID
+ (void)reportColorState:(NSString *)guid;

/// 上报客户端时间误差过大 （大于30分钟时上报）
/// @param guid 用户ID
/// @param timeInterval 误差值(server-local)，单位s
+ (void)reportLocalTimeErrorForGuid:(NSString *)guid withInterval:(long)timeInterval;

/// 上报自动上报受限
/// @param guid 用户ID
/// @param limitType 受限原因
/// @param tag 上报标签
+ (void)reportAutoUploadLimitWithGuid:(NSString *)guid limitType:(int)limitType andTag:(NSString *)tag;

@end

NS_ASSUME_NONNULL_END
