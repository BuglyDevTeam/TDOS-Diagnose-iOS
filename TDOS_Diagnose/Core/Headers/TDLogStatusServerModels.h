//   
//  TDLogStatusServerModels.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/30.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogConfigServerModels.h"

NS_ASSUME_NONNULL_BEGIN

/// 配置拉取状态
typedef NS_ENUM(NSUInteger, TDLogConfigStatus) {
    TDLogConfigStatus_Unknown,
    TDLogConfigStatus_Success,
    TDLogConfigStatus_Failed,
};

/// 上报类型
typedef NS_ENUM(NSUInteger, TDLogUploadType) {
    TDLogUploadType_Unknown,
    TDLogUploadType_Pull,   // 日志捞取
    TDLogUploadType_Pick,   // 日志采集
    TDLogUploadType_Auto,   // 自动上报（crash、反馈等）
};

/// 上报状态
typedef NS_ENUM(NSUInteger, TDLogUploadStatus) {
    TDLogUploadStatus_Unknown,
    TDLogUploadStatus_Start,    // 开始上报
    TDLogUploadStatus_Success,  // 上报成功
    TDLogUploadStatus_Failed,   // 上报失败
};

/// 失败原因
typedef NS_ENUM(NSUInteger, TDLogUploadFailReason) {
    TDLogUploadFailReason_Unknown = 0,
    TDLogUploadFailReason_Net = 1,          // 网络问题
    TDLogUploadFailReason_FileTooLarge = 2, // 文件大小超过阈值
    TDLogUploadFailReason_Zip = 3,          // 压缩失败
    TDLogUploadFailReason_COSError = 4,     // COS服务异常
    TDLogUploadFailReason_NoLog = 5,        // 本地没有日志
    TDLogUploadFailReason_Other = 10,       // 其他
};


#pragma mark - 配置拉取状态的上报

@class TDLogConfigClientInfo;
@class TDLogStatusPullLogCmdInfo;
@class TDLogStatusColorLogCmdInfo;
/// 更新后台配置状态的请求包
@interface TDLogUpdateConfigStatusRequestInfo : NSObject

/// SDK端信息
@property (nonatomic, strong) TDLogConfigClientInfo *clientInfo;
/// 捞取命令的相关信息, 数组
@property (nonatomic, strong) NSArray<TDLogStatusPullLogCmdInfo *> *pullLogCmdInfos;
/// 染色命令的相关信息
@property (nonatomic, strong) TDLogStatusColorLogCmdInfo *colorLogCmdInfo;
/// 请求sequence, 主要用于调试定位用
@property (nonatomic, assign) uint32_t seq;
/// 时间戳（秒）
@property (nonatomic, assign) uint32_t timestamp;

@end

/// 捞日志命令相关信息
@interface TDLogStatusPullLogCmdInfo : NSObject

/// 捞日志任务ID
@property (nonatomic, assign) uint32_t pullTaskId;

/// 从拉取配置详情model生成实例
/// @param pullDetailInfo 拉取详情model
+ (nullable instancetype)infoFromPullLogDetailInfo:(nullable TDLogConfigPullLogCmdDetailInfo *)pullDetailInfo;

@end

/// 染色命令相关信息
@interface TDLogStatusColorLogCmdInfo : NSObject

/// 染色任务ID
@property (nonatomic, assign) uint32_t colorTaskId;

/// 从染色配置model生成实例
/// @param configInfo 染色配置model
+ (nullable instancetype)infoFromColorConfigInfo:(nullable TDLogConfigColorInfo *)configInfo;

@end

/// 更新后台配置状态的回包
@interface TDLogUpdateConfigStatusResponseInfo : NSObject

/// 错误码
@property (nonatomic, assign) int32_t retCode;
/// 错误信息
@property (nonatomic, copy) NSString *retMsg;

@end


#pragma mark - 文件上传状态的相关上报

@class TDLogUploadStatusAutoLogInfo;
/// 上传状态的请求包
@interface TDLogUploadStatusRequestInfo : NSObject

/// SDK端信息
@property (nonatomic, strong) TDLogConfigClientInfo *clientInfo;
/// 上传类型
@property (nonatomic, assign) TDLogUploadType uploadType;
/// 上传状态
@property (nonatomic, assign) TDLogUploadStatus uploadStatus;
/// 捞取命令的相关信息
@property (nonatomic, strong) TDLogStatusPullLogCmdInfo *pullLogCmdInfo;
/// 自动上报日志相关信息
@property (nonatomic, strong) TDLogUploadStatusAutoLogInfo *autoLogInfo;
/// 日志加密公钥的MD5
@property (nonatomic, copy) NSString *pubKeyMd5;
/// cos资源路径，上报成功时带上
@property (nonatomic, copy) NSString *cosUrl;
/// 上传失败的原因类型
@property (nonatomic, assign) TDLogUploadFailReason failReasonType;
/// 上传失败的原因详情
@property (nonatomic, copy) NSString *failReason;
/// 扩展信息
@property (nonatomic, copy) NSString *extInfo;
/// 请求sequence, 主要用于调试定位用
@property (nonatomic, assign) uint32_t seq;
/// 时间戳（秒）
@property (nonatomic, assign) uint32_t timestamp;

@end


/// 自动上报携带的检索信息
@interface TDLogUploadIndexMapInfo : NSObject

/// 自动上报自定义检索Key
@property (nonatomic, copy) NSString *queryKey;
/// 调用方来源，如bugly，dcl
@property (nonatomic, copy) NSString *source;
/// 跳转URL
@property (nonatomic, copy) NSString *jumpUrl;
/// 扩展信息
@property (nonatomic, copy) NSString *extInfo;

@end


/// 自动上报日志相关信息
@interface TDLogUploadStatusAutoLogInfo : NSObject

/// 自动上报的标签, 最大长度64
@property (nonatomic, copy) NSString *label;
/// 自动上报的摘要信息，方便搜索，最大长度256
@property (nonatomic, copy) NSString *summary;
/// 自动上报携带的检索信息
@property (nonatomic, strong) NSArray<TDLogUploadIndexMapInfo *> *indexMapInfos;

@end


@class TDLogUploadTmpCosSecretInfo;
/// 上传状态回包
@interface TDLogUploadStatusResponseInfo : NSObject

/// 错误码
@property (nonatomic, assign) int32_t retCode;
/// 错误信息
@property (nonatomic, copy) NSString *retMsg;
/// COS上传的地址
@property (nonatomic, copy) NSString *cosUploadUrl;
/// 临时密钥信息，开始上传时返回
@property (nonatomic, strong) TDLogUploadTmpCosSecretInfo *cosSecretInfo;
/// 服务器时间，单位s
@property (nonatomic, assign) uint32_t serverTime;

@end


/// 文件上传临时密钥信息
@interface TDLogUploadTmpCosSecretInfo : NSObject

/// cos secret id
@property (nonatomic, copy) NSString *tmpSecretId;
/// cos secret key
@property (nonatomic, copy) NSString *tmpSecretKey;
/// cos security token
@property (nonatomic, copy) NSString *xcosSecurityToken;
/// 临时密钥过期时间，单位s
@property (nonatomic, assign) uint32_t expiredTime;

/// 当前密钥是否有效
/// 
/// 注意，有效时间仅判断大于当前时间
- (BOOL)isValid;

@end

NS_ASSUME_NONNULL_END
