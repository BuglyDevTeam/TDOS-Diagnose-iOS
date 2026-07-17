//   
//  TDLogSDK.h
//  TDiagnose
//
//  Created by raycgwang on 2021/12/23.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogSDKConfig.h"

NS_ASSUME_NONNULL_BEGIN

@class TDLogExtQueryInfo;
@interface TDLogSDK : NSObject

/// SDK配置字段
@property (atomic, readonly) TDLogSDKConfig *sdkConfig;

/// 获取对象单例
+ (instancetype)sharedInstance;


#pragma mark - SDK启动

/// 启动日志 SDK
/// @param config 日志SDK需要的配置, 通过\c +configWithAppId:... 接口生成配置实例。
- (BOOL)startWithConfig:(TDLogSDKConfig *)config;


#pragma mark - 自动上报

/// 主动上报日志
/// @param files 日志文件列表
/// @param tag 标签，必填，长度不超过64bytes
/// @param summary 摘要信息（支持搜索），选填，长度不超过256bytes
/// @param extendInfoDict 扩展信息，选填，需支持序列化，长度不超过1K
/// @param completionBlock 上传结果回调，首次上传失败后自动重试后不再回调
- (void)uploadFiles:(nonnull NSArray <NSString *> *)files
            withTag:(NSString *)tag
            summary:(nullable NSString *)summary
      andExtendInfo:(nullable NSDictionary *)extendInfoDict
         completion:(void (^)(BOOL result, NSString *_Nullable errMsg))completionBlock;

/// 主动上报日志接口2，用法同上，增加queryInfo字段
/// @param files 日志文件列表
/// @param tag 标签，必填，长度不超过64bytes
/// @param summary 摘要信息（支持搜索），选填，长度不超过256bytes
/// @param queryInfo 检索信息，选填，用于平台互通（跨系统检索）
/// @param extendInfoDict 扩展信息，选填，需支持序列化，长度不超过1K
/// @param completionBlock 上传结果回调，首次上传失败后自动重试后不再回调
- (void)uploadFiles:(nonnull NSArray <NSString *> *)files
            withTag:(NSString *)tag
            summary:(nullable NSString *)summary
       extQueryInfo:(nullable TDLogExtQueryInfo *)queryInfo
      andExtendInfo:(nullable NSDictionary *)extendInfoDict
         completion:(void (^)(BOOL result, NSString *_Nullable errMsg))completionBlock;

/// 主动上报日志接口3，用法同上，增加 progress callback, fileSize callback
/// @param files 日志文件列表
/// @param tag 标签，必填，长度不超过64bytes
/// @param summary 摘要信息（支持搜索），选填，长度不超过256bytes
/// @param queryInfo 检索信息，选填，用于平台互通（跨系统检索）
/// @param extendInfoDict 扩展信息，选填，需支持序列化，长度不超过1K
/// @param progressBlock 上传进度回调，按照总大小和分片大小回调，每完成一个分片回调一次
/// @param fileSizeBlock 文件大小回调，压缩文件大小确定后回调一次，单位为byte
/// @param completionBlock 上传结果回调，首次上传失败后自动重试后不再回调
- (void)uploadFiles:(nonnull NSArray <NSString *> *)files
            withTag:(NSString *)tag
            summary:(nullable NSString *)summary
       extQueryInfo:(nullable TDLogExtQueryInfo *)queryInfo
      andExtendInfo:(nullable NSDictionary *)extendInfoDict
           progress:(nullable void (^)(NSUInteger index, NSUInteger successParts, NSUInteger totalParts))progressBlock
           fileSize:(nullable void (^)(NSUInteger fileSize))fileSizeBlock
         completion:(void (^)(BOOL result, NSString *_Nullable errMsg))completionBlock;


#pragma mark - 其他能力

/// 主动拉取捞日志命令
///
/// 调用场景：如收到Push消息时
- (void)requestLogConfigFromServer;


@end


#pragma mark - Others

/// 自动上报扩展检索信息，主要用于跨系统查询。
/// 可选设置
@interface TDLogExtQueryInfo : NSObject

/// `检索Key`，用于平台互通检索上报信息
@property (nonatomic, strong) NSString *queryKey;

/// `来源`，用于平台互通记录上报来源
@property (nonatomic, strong) NSString *sourcePlatform;

@end

NS_ASSUME_NONNULL_END
