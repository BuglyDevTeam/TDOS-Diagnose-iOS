//   
//  TDLogUploadTaskModel.h
//  TDOS-Diagnose
//  
//  Created by raycgwang on 2022/1/11.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogStatusServerModels.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, TDLogUploadTaskState) {
    TDLogUploadTaskState_Init,
    TDLogUploadTaskState_Uploading,
    TDLogUploadTaskState_SuccessStateSyncing,
    TDLogUploadTaskState_FailStateSyncing,
    TDLogUploadTaskState_Finish,
};

/// 数据上报-异常详情定义
typedef NS_ENUM(NSUInteger, TDLogUploadDetailFailType) {
    TDLogUploadDetailFailType_Unknown = 0,
    TDLogUploadDetailFailType_NoFile = 1,
    TDLogUploadDetailFailType_NetError = 2,
    TDLogUploadDetailFailType_COSTokenErr = 3,
    TDLogUploadDetailFailType_COSUrlErr = 4,
    TDLogUploadDetailFailType_COSMultiInitErr = 5,
    TDLogUploadDetailFailType_COSMultiUploadErr = 6,
    TDLogUploadDetailFailType_COSMultiCompleteErr = 7,
    TDLogUploadDetailFailType_COSSimpleErr = 8,
    TDLogUploadDetailFailType_LabelLimit = 9,
    TDLogUploadDetailFailType_COSSimpleCRC64Err = 10,
    TDLogUploadDetailFailType_OtherCOSErr = 100,
};

#define TDLOG_UPLOADTASK_NO_RETRY    NSIntegerMax
typedef void(^TDLogUploadCompletionBlock)(BOOL result, NSString * _Nullable errMsg);


@interface TDLogUploadTaskModel : NSObject

#pragma mark - 基本信息

/// 任务ID（本地生成，用于任务持久化等）
@property (nonatomic, readonly) NSString *taskId;
/// 任务开始时间
@property (nonatomic, readonly) NSTimeInterval startTime;
/// 用户ID
@property (nonatomic, readonly) NSString *guid;
/// 文件全路径
@property (nonatomic, readonly) NSString *filePath;
/// 上报类型
@property (nonatomic, readonly) TDLogUploadType uploadType;
/// 任务状态
@property (nonatomic, assign) TDLogUploadTaskState state;

#pragma mark - 附带信息

/// 日志拉取的命令信息，当前主要为记录taskid
@property (nonatomic, strong) TDLogStatusPullLogCmdInfo *pullLogCmdInfo;
/// 自动上报的附加信息
@property (nonatomic, strong) TDLogUploadStatusAutoLogInfo *autoLogInfo;
/// 外部透传信息
@property (nonatomic, strong, nullable) NSDictionary *extendInfo;
/// 日志加密用的公钥md5
@property (nonatomic, copy, nullable) NSString *encryptPubKeyMd5;

#pragma mark - 结果附带信息

/// 上传成功后的下载地址
@property (nonatomic, copy, nullable) NSString *downloadUrl;

/// 记录上传结束后的回调
@property (nonatomic, copy, nullable) TDLogUploadCompletionBlock completionBlock;

#pragma mark - 重试与失败信息

/// 上传的重试次数
@property (nonatomic, assign) NSInteger uploadRetryTimes;
/// 状态上报的重试次数
@property (nonatomic, assign) NSInteger stateSyncRetryTimes;
/// 失败类型
@property (nonatomic, assign) TDLogUploadFailReason failType;
/// 任务如果失败产生的错误信息
@property (nonatomic, copy, nullable) NSString *errorMsg;

/// 是否强制使用分片上传，YES后强制走分片上传
/// 该值解决普通上传CRC64异常问题
@property (nonatomic, assign) BOOL shouldForceUseMultiPartUpload;

#pragma mark - 数据上报辅助信息

/// 是否使用了COS的分片上传
@property (nonatomic, assign) BOOL isCOSMultiPartUpload;
/// 上传文件大小（压缩包）
@property (nonatomic, assign) NSUInteger uploadFileSize;
/// 任务上一阶段结束时间
@property (nonatomic, assign) NSTimeInterval stepEndTime;
/// 上传失败的详细原因
@property (nonatomic, assign) TDLogUploadDetailFailType uploadDetailFailType;


#pragma mark -

/// Initialize with file's path
/// @param uploadType 上报类型
/// @param filePath 待上传的文件全路径
/// @param guid 用户ID
+ (instancetype)modelWithType:(TDLogUploadType)uploadType filePath:(NSString *)filePath andGuid:(NSString *)guid;


/// Use \c modelWithType:filePath: to initialize
- (instancetype)init NS_UNAVAILABLE;
/// Use \c modelWithType:filePath: to initialize
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
