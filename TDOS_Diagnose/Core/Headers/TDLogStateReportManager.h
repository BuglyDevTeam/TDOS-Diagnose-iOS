//   
//  TDLogStateReportManager.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/30.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogConfigServerModels.h"
#import "TDLogStatusServerModels.h"
#import "TDLogUploadTaskModel.h"
@class TDLogSDKConfig;

NS_ASSUME_NONNULL_BEGIN

typedef void (^TDLogUploadStateSyncCompletion)(BOOL isSuccess, NSString *errorMsg);

/// 负责SDK状态上报（SDK同步至后台）
///
/// 包含：1、配置拉取状态，2、文件上传状态
@interface TDLogStateReportManager : NSObject

/// 初始化方法
/// @param sdkConfig SDK配置
- (instancetype)initWithSDKConfig:(TDLogSDKConfig *)sdkConfig;

#pragma mark - 配置状态

/// 发送配置状态更新请求
/// @param colorCmd 配置拉取到的染色命令id
/// @param pullLogCmds 配置拉取到的捞日志命令id
/// @param guid 用户ID
- (void)sendUpdateConfigStatusRequestWithColorInfo:(TDLogConfigColorInfo *)colorCmd
                                   andPullLogInfos:(NSArray<TDLogConfigPullLogCmdDetailInfo *> *)pullLogCmds
                                           forGuid:(NSString *)guid;


#pragma mark - 文件上传 & 临时密钥状态相关

/// 发送开始上传状态，并获取临时密钥（同步调用）
/// @param taskInfo 上传任务信息
- (nullable TDLogUploadStatusResponseInfo *)sendStartUploadStateAndGetCosSecretInfoSync:(TDLogUploadTaskModel *)taskInfo;

/// 发送上传成功状态
/// @param taskInfo 上传任务信息
- (void)sendUploadSuccessState:(TDLogUploadTaskModel *)taskInfo completion:(TDLogUploadStateSyncCompletion)compeltion;

/// 发送上传失败状态
/// @param taskInfo 上传任务信息
- (void)sendUploadFailState:(TDLogUploadTaskModel *)taskInfo completion:(TDLogUploadStateSyncCompletion)compeltion;

@end

NS_ASSUME_NONNULL_END
