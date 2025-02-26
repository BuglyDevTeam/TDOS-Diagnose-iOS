//   
//  TDLogRequestCommon.h
//  TDOS-Diagnose
//  
//  Created by raycgwang on 2022/1/12.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
@class TDLogConfigClientInfo;
@class TDLogSDKConfig;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSString * const TDLogServerHost;
FOUNDATION_EXTERN NSString * const TDLogTestServerHost;
FOUNDATION_EXTERN NSString * const TDLogOverseaServerHost;
FOUNDATION_EXPORT NSString * const TDLogBuglyProServerHost;
FOUNDATION_EXPORT NSString * const TDLogBuglyOverseaServerHost;

FOUNDATION_EXTERN NSString * const TDLogUploadResultNotification;

/// 一些请求的通用逻辑
@interface TDLogRequestCommon : NSObject

/// 请求携带的SDK信息
/// @param guid 用户唯一ID
/// @param sdkConfig sdk配置
+ (TDLogConfigClientInfo *)clientInfoWithGuid:(NSString *)guid sdkConfig:(TDLogSDKConfig *)sdkConfig;

/// 请求头的签名字段
/// @param httpBody body内容
/// @param appKey 平台申请的AppKey
+ (NSString *)headerSignatureWithHttpBody:(NSData *)httpBody appKey:(NSString *)appKey;

@end

NS_ASSUME_NONNULL_END
