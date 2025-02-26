//   
//  TDLogCOSUploadModels.h
//  TDOS-Diagnose
//  
//  Created by raycgwang on 2022/1/10.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
@class TDLogCosMultipartInfo;
@class TDLogUploadTaskModel;

NS_ASSUME_NONNULL_BEGIN

/// 分片上传的状态
typedef enum : NSUInteger {
    TDCOSUploadState_None,
    TDCOSUploadState_SimpleUploading,               // 简单上传
    TDCOSUploadState_MultiPartPendingInitiate,      // 分片上传-初始化
    TDCOSUploadState_MultiPartPendingUploadPart,    // 分片上传-上传分片
    TDCOSUploadState_MultiPartPendingComplete,      // 分片上传-发送结束消息
    TDCOSUploadState_MultiPartPendingAbort,         // 分片上传-发送取消消息
    TDCOSUploadState_Finish,                        // 任务结束
} TDCOSUploadState;


typedef void (^TDLogCosUploadCallBack)(BOOL succeed, NSString * _Nullable cosDownloadUrl,  NSString * _Nullable errorString);


/// COS上传任务
@interface TDLogCOSUploadTaskInfo : NSObject

/// 待上传的文件路径
@property (nonatomic, copy, nonnull) NSString *filePath;
/// 任务状态
@property (nonatomic, assign) TDCOSUploadState state;
/// 上传任务信息模型
@property (nonatomic, strong) TDLogUploadTaskModel *uploadTaskInfo;
/// 任务回调，每次启动前赋值
@property (nonatomic, strong, nullable) TDLogCosUploadCallBack callback;

#pragma mark - 分片上传相关

/// 是否分片上传任务
@property (nonatomic, assign) BOOL isMultiPartUpload;
/// 分片上传的ID
@property (nonatomic, copy, nullable) NSString *multiPartUploadID;
/// 分片编号 （1-10000）
@property (nonatomic, assign) int partNumber;
/// 自定义分片大小
@property (nonatomic, assign) NSUInteger sliceSize;
/// 已上传的大小
@property (nonatomic, assign) NSUInteger uploadedSize;
/// 已上传的分片的信息 （cos返回）
@property (nonatomic, strong) NSMutableArray<TDLogCosMultipartInfo *> *uploadedPartInfos;

@end



/// 分块上传中每一个数据块信息
@interface TDLogCosMultipartInfo : NSObject

/// 块编号
@property (strong, nonatomic) NSString *partNumber;
/// 每个块文件的MD5算法校验值
@property (strong, nonatomic) NSString *eTag;

@end

NS_ASSUME_NONNULL_END
