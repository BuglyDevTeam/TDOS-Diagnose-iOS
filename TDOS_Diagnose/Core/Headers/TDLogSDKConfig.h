//   
//  TDLogSDKConfig.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/30.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDIAGLogMediator.h"
#import "TDIAGDependProtocol.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, TDLogServerHostType) {
    TDLogServerHostTypeDefault = 0,
    TDLogServerHostTypeTest,
    TDLogServerHostTypeOversea,
    TDLogServerHostTypeBuglyPro,
    TDLogServerHostTypeBuglyOversea,
};

/// SDK所需的必要信息
@protocol TDLogSDKDataSource <NSObject>

@required
/// 返回用户唯一ID
///
/// 平台下发命令时填写此ID
- (NSString *)guidForTDLog;

@optional

/// 返回业务 app 版本
/// 若未实现或返回空，则会取 NSBundle 中的 CFBundleShortVersionString
///
- (nullable NSString *)appVersion;

/// 返回业务附带的上报信息，SDK进行捞日志上报时携带
///
/// 注意，字典内容需支持序列化为Json字符串
- (nullable NSDictionary *)extraParamsForTDLogReport;

/// 返回自定义附件路径，SDK进行捞日志上报时将打包上传
///
/// 注意：文件总大小建议不超过300M
- (nullable NSArray<NSString *> *)extraFilesForTDLogReport;

/// 返回自动上报标签白名单
///
/// 白名单中的自动上报将不计算频率/流量消耗等资源管控，避免造成上报失败
/// 推荐返回如“用户主动反馈”场景下的自动上报标签
- (NSArray<NSString *> *)whitelistForAutoUploadTags;

@end


/// 频率控制策略对象，(采用令牌桶算法)
@interface TDLogFrequencyControlStrategy : NSObject

/// 次数
@property (nonatomic, assign) int times;
/// 时间间隔
@property (nonatomic, assign) time_t timeInterval;

@end


/// SDK配置信息
@interface TDLogSDKConfig : NSObject

#pragma mark - 业务信息

/// 日志平台申请的业务AppId
@property (nonatomic, copy, readonly) NSString *appId;

/// 日志平台申请的业务AppKey
@property (nonatomic, copy, readonly) NSString *appKey;

/// 宿主提供的必要信息，如设备ID、用户ID等
@property (nonatomic, weak, readonly) id<TDLogSDKDataSource> hostData;

#pragma mark - 依赖模块

/// 用户注入的原始功能模块实现
@property (nonatomic, strong, readonly) id<TDIAGDependProtocol> depends;

/// 用户注入的日志模块实现, 封装层
@property (nonatomic, strong, readonly) TDIAGLogMediator *logMediator;


#pragma mark - 配置实例创建

/// 生成一SDK配置项，用于初始化SDK
/// @param appId 后台分配的业务Appid，必填
/// @param appKey 后台分配的业务AppKey，必填
/// @param depends SDK依赖的基础注入能力实现
+ (instancetype)configWithAppId:(NSString *)appId
                         appKey:(NSString *)appKey
                     dataSource:(id<TDLogSDKDataSource>)dataSource
                        depends:(id<TDIAGDependProtocol>)depends;


#pragma mark - Frequency & Traffic Limit Related

/// 当前的频率控制策略
@property (nonatomic, strong, nullable, readonly) TDLogFrequencyControlStrategy *currentFrequencyControlStrategy;

/// 设置自动上报频率控制是否开启
/// 本设置可选，默认不限制
/// 该方法要求TDLogSDKDataSource需实现\c whitelistForAutoUploadTags 接口，以免影响必要上报。
///
/// @param isOpen 是否开启
/// @param strategy 频率控制策略，为空采用SDK默认策略(2次/5min)
- (void)setFrequencyLimitStatusForAutoUpload:(BOOL)isOpen
                   withCustomControlStrategy:(nullable TDLogFrequencyControlStrategy *)strategy;


/// 24H总流量配额
@property (nonatomic, assign, readonly) long long totalQuotaFor24h;
/// 24H的XG流量配额
@property (nonatomic, assign, readonly) long long xgQuotaFor24h;


/// 设置自动上报24h的流量配额，超过配额的自动上报将被拦截
/// 本设置可选，默认不限制
/// 该方法要求TDLogSDKDataSource需实现\c whitelistForAutoUploadTags 接口，以免影响必要上报。
///
/// @param totalQuota 总流量（单位：字节，要求 >= [xgQuota]，<0代表不限制）
/// @param xgQuota XG流量（单位：字节，<0代表不限制）
- (void)setTrafficQuota24hLimitForAutoUpload:(long long)totalQuota
                                     xgQuota:(long long)xgQuota;


#pragma mark - Upload Parameter Related

/// 使用分片上传的大小阈值
@property (nonatomic, strong) NSNumber *thresholdForMultiPartUpload;


#pragma mark - Others

/// 设置服务域名类型
@property (nonatomic, assign) TDLogServerHostType serverHostType;

/// 自定义服务器域名
@property (nonatomic, strong) NSString *customServerHost;

@end

NS_ASSUME_NONNULL_END
