//
//  RFKTConfigServerJsonModel.h
//  RDelivery
//
//  Created by selmerzhang on 2021/8/26.
//  Copyright © 2021 Tencent. All rights reserved.
//

#ifndef RFKTConfigServerJsonModel_h
#define RFKTConfigServerJsonModel_h

#import "RFKT_JSONModel.h"

/// 拉取类型
typedef NS_ENUM(NSUInteger, RFKTConfigServerPullType) {
    RFKTConfigServerPullTypeUNKNOWN = 0,
    RFKTConfigServerPullTypeAPP = 1, // 按AppID拉取
    RFKTConfigServerPullTypeGROUP = 2,  // 按分组拉取（按sceneid拉取）
    RFKTConfigServerPullTypeCONFIG = 3, // 按单个配置拉取
    RFKTConfigServerPullTypePROJECT = 4, // 按项目拉取
};

/// 平台类型
typedef NS_ENUM(NSUInteger, RFKTConfigServerPlatform) {
    RFKTConfigServerPlatformUnknown = 0,
    RFKTConfigServerPlatformCommon = 1,
    RFKTConfigServerPlatformAndroid = 2,
    RFKTConfigServerPlatformIOS = 3,
    RFKTConfigServerPlatformWeb = 4,
    RFKTConfigServerPlatformServer = 5,
    RFKTConfigServerPlatformMicroApp = 6,
};

/// 状态码
typedef NS_ENUM(NSUInteger, RFKTConfigServerStatusCode) {
    RFKTConfigServerStatusCodeSuccess = 0,
    RFKTConfigServerStatusCodeParamInvalid = 1, // 参数错误
    RFKTConfigServerStatusCodeServerError = 2, // 系统错误
    RFKTConfigServerStatusCodeParanIllegal = 3, // 非法请求，如签名错误
    RFKTConfigServerStatusCodeConfigNotfound = 4, // 配置未找到
    RFKTConfigServerStatusCodeConfigResultEmpty = 5, // 配置计算结果为空
};

/// 操作类型
typedef NS_ENUM(NSUInteger, RFKTConfigServerOpration) {
    RFKTConfigServerOprationNone = 0, // 保持
    RFKTConfigServerOprationUpdate = 1, // 更新
    RFKTConfigServerOprationDelete = 2, // 删除
};


NS_ASSUME_NONNULL_BEGIN

#pragma mark - 请求体

/// 终端必传属性
@interface RFKTConfigServerProperties : RFKT_JSONModel

/// 平台
@property(nonatomic, assign) RFKTConfigServerPlatform platform;

/// 语言
@property(nonatomic, copy) NSString *language;

/// SDK版本号
@property(nonatomic, copy) NSString *sdkVersion;

/// 用户id
@property(nonatomic, copy) NSString *guid;

/// 宿主App版本号
@property(nonatomic, copy) NSString *appVersion;

/// 操作系统版本号
@property(nonatomic, copy) NSString *osVersion;

/// bundleId
@property(nonatomic, copy) NSString *bundleId;

@end


/// 拉取参数
@interface RFKTConfigServerPullParams : RFKT_JSONModel

/// 配置分组，按分组拉取时填写（sceneId）
@property(nonatomic, copy) NSString * groupID;

/// 配置名，按单个配置拉取时填写
@property(nonatomic, copy) NSString *key;

/// 终端必传属性
@property(nonatomic, strong) RFKTConfigServerProperties *properties;

/// 终端自定义属性
@property(nonatomic, copy) NSDictionary *customProperties;

@end


/// Server请求包
@interface RFKTConfigServerPullRequest : RFKT_JSONModel

/// 系统ID
@property(nonatomic, copy) NSString *systemID;

/// 按AppID拉取时填写
@property(nonatomic, copy) NSString *appID;

/// 参数签名，用于校验请求体是否合法，算法参考：https://iwiki.woa.com/pages/viewpage.action?pageId=956353272
@property(nonatomic, copy) NSString *sign;

/// 时间戳（秒），用于签名校验
@property(nonatomic, assign) int64_t timestamp;

/// 拉取类型
@property(nonatomic, assign) RFKTConfigServerPullType pullType;

/// 拉取参数
@property(nonatomic, strong) RFKTConfigServerPullParams *pullParams;

/// 逻辑环境名称
@property(nonatomic, copy) NSString *env;

/// 上下文信息，SDK透传
@property(nonatomic, copy) NSString *context;

@end


#pragma mark - 回包

/// 回包中的配置信息
@interface RFKTServerConfigInfo : RFKT_JSONModel

/// 配置名称
@property(nonatomic, copy) NSString *key;

/// 配置内容
@property(nonatomic, copy) NSString *value;

/// 操作指令：更新/保持/删除
@property(nonatomic, assign) RFKTConfigServerOpration op;

/// 调试信息
@property(nonatomic, copy) NSString *debugInfo;

@end


/// Server回包
@interface RFKTConfigServerPullResponse : RFKT_JSONModel

/// 错误码
@property(nonatomic, assign) RFKTConfigServerStatusCode code;

/// 错误信息
@property(nonatomic, copy) NSString *msg;

/// 下发的配置
@property(nonatomic, copy) NSArray<RFKTServerConfigInfo *> *configs;

/// 上下文信息，SDK透传
@property(nonatomic, copy) NSString *context;

/// 下一次拉取最小时间间隔，0使用SDK自身设置的间隔
@property(nonatomic, assign) uint32_t interval;

@end

#pragma mark - 自定义数据结构

/// main panel tips content
@interface RFKTTipBannerTipsInfo : RFKT_JSONModel

/// the title
@property (nonatomic, strong) NSString *title;
/// url to jump
@property (nonatomic, strong) NSString<Optional> *url;
/// detail description
@property (nonatomic, strong) NSString<Optional> *detail;
/// background image
@property (nonatomic, strong) NSString<Optional> *bgUrl;

@end

/// main panel banner info
@interface RFKTTipBannerInfo : RFKT_JSONModel

/// contents
@property (nonatomic, strong) NSArray<RFKTTipBannerTipsInfo *> *tips;

@end




NS_ASSUME_NONNULL_END

#endif /* RFKTConfigServerJsonModel_h */
