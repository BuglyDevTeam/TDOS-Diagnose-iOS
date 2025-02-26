//   
//  TDLogConfigServerModels.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/29.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//
//  定义参见：https://git.woa.com/trpcprotocol/rconfig/blob/master/log_task_svr/log_task_svr.proto

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// SDK自身错误码
typedef NS_ENUM(NSUInteger, TDLogConfigReqErrorCode) {
    TDLogConfigReqErrorNone = 0,                     //无错误
    TDLogConfigReqErrorHttpRequestException = 1,     //HTTP请求错误
    TDLogConfigReqErrorHttpErrorStatusCode = 2,      //HTTP状态码错误
    TDLogConfigReqErrorHttpErrorOther = 3,           //其他HTTP错误
    TDLogConfigReqErrorServerError = 10,             //后台返回了错误码
    TDLogConfigReqErrorPackError = 20,               //组包失败
    TDLogConfigReqErrorParseError = 21,              //解包失败
    TDLogConfigReqErrorOther = 90,                   //其他错误
};

/// Server端返回的状态码
typedef NS_ENUM(NSUInteger, TDLogTaskServerRetCode) {
    TDLogTaskServerRetCode_Success = 0, // 0=成功
    TDLogTaskServerRetCode_SvrDecodeErr = 100, //后台解码失败
    TDLogTaskServerRetCode_AutoLogAboveLimit = 1000, // 自动上报超过上限
};

/// LogColorLevel 染色级别
typedef NS_ENUM(NSUInteger, TDLogServerDefColorLevel) {
    TDLogServerDefColorLevel_UNKNOWN = 0,
    TDLogServerDefColorLevel_VERBOSE = 1,
    TDLogServerDefColorLevel_DEBUG = 2,
    TDLogServerDefColorLevel_INFO = 3,
    TDLogServerDefColorLevel_WARN = 4,
    TDLogServerDefColorLevel_ERROR = 5,
    TDLogServerDefColorLevel_FATAL = 6,
    TDLogServerDefColorLevel_NONE = 7,
};


#pragma mark - 请求包

@class TDLogConfigClientInfo;
/// Server请求包
@interface TDLogConfigRequestInfo : NSObject

/// SDK端信息
@property (nonatomic, strong) TDLogConfigClientInfo *clientInfo;
/// 当前是否染色状态
@property (nonatomic, assign) bool isColorState;
/// 请求sequence, 主要用于调试定位用
@property (nonatomic, assign) uint32_t seq;
/// 时间戳（秒）
@property (nonatomic, assign) uint32_t timestamp;
/// 配置版本号，做增量更新
@property (nonatomic, copy) NSString *version;

@end

/// 请求包携带的SDK信息
@interface TDLogConfigClientInfo : NSObject

#define TDLOG_CONFIG_PULL_PLATFORM_IOS 2 // 定义请求平台，iOS=2
#define TDLOG_CONFIG_PULL_PLATFORM_MAC 3 // 定义请求平台，Mac=3
/// 平台, PLATFORM_IOS = 2
@property (nonatomic, assign) short platform;
/// SDK版本号
@property (nonatomic, copy) NSString *sdkVersion;
/// 用户ID
@property (nonatomic, copy) NSString *guid;
/// 宿主App版本号
@property (nonatomic, copy) NSString *appVersion;
/// 操作系统版本号
@property (nonatomic, copy) NSString *osVersion;
/// bundleId
@property (nonatomic, copy) NSString *bundleId;
/// 设备型号
@property (nonatomic, copy) NSString *model;
/// 设备ID
@property (nonatomic, copy) NSString *deviceId;

@end


#pragma mark - 回包
@class TDLogConfigColorInfo;
@class TDLogConfigColorCmdDetail;
@class TDLogConfigPullLogInfo;
@class TDLogConfigPullLogCmdDetailInfo;
@class TDLogConfigColorStateLongTerm;

/// Server回包
@interface TDLogConfigResponseInfo : NSObject

/// 错误码
@property (nonatomic, assign) int32_t retCode;
/// 错误信息
@property (nonatomic, copy) NSString *retMsg;
/// 染色信息
@property (nonatomic, strong) TDLogConfigColorInfo *colorInfo;
/// 捞取信息
@property (nonatomic, strong) TDLogConfigPullLogInfo *pullLogInfo;
/// 配置版本号
@property (nonatomic, copy) NSString *version;
/// 拉配置的时间间隔，单位秒（s）
@property (nonatomic, assign) int32_t cfgTimeInterval;
/// 服务器时间，单位s
@property (nonatomic, assign) uint32_t serverTime;

@end

/// 服务器返回的染色信息
@interface TDLogConfigColorInfo : NSObject

/// 是否需要重置染色标识
@property (nonatomic, assign) bool needResetColorLevel;
/// 染色详情
@property (nonatomic, strong) TDLogConfigColorCmdDetail *colorDetail;
/// 长期染色状态
@property (nonatomic, strong) TDLogConfigColorStateLongTerm *colorStateLongTerm;

@end

/// 服务器返回的染色详情信息
@interface TDLogConfigColorCmdDetail : NSObject

/// 染色级别
@property (nonatomic, assign) TDLogServerDefColorLevel colorLevel;
/// 染色结束时间戳，秒
@property (nonatomic, assign) uint32_t colorEndStamp;
/// 染色任务ID
@property (nonatomic, assign) uint32_t colorTaskId;

@end

/// 服务器返回的长期染色状态信息
@interface TDLogConfigColorStateLongTerm : NSObject

/// 是否长期染色号码
@property (nonatomic, assign) bool isColorGuidLongTerm;
/// 染色级别
@property (nonatomic, assign) TDLogServerDefColorLevel colorLevel;

@end

/// 服务器返回的日志捞取信息
@interface TDLogConfigPullLogInfo : NSObject

/// 捞取命令的时间段信息
@property (nonatomic, strong) NSArray<TDLogConfigPullLogCmdDetailInfo *> *pullCmdInfos;

@end

/// 服务器返回的日志捞取命令信息
@interface TDLogConfigPullLogCmdDetailInfo : NSObject

/// 捞取日志的开始时间戳，秒
@property (nonatomic, assign) uint32_t pullStartStamp;
/// 捞取日志的结束时间戳，秒
@property (nonatomic, assign) uint32_t pullEndStamp;
/// 捞取任务ID
@property (nonatomic, assign) uint32_t pullTaskId;
/// 捞取的特定文件路径
@property (nonatomic, strong) NSArray<NSString *> *specificPaths;

@end

NS_ASSUME_NONNULL_END
