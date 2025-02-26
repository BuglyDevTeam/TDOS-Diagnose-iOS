//
//  RFKTDeviceNetworkState.h
//  RFKTDeviceNetworkState
//
//  Created by Tianwu on 2021/8/19.
//  Copyright © 2021年 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RFKTNetworkReachability.h"

NS_ASSUME_NONNULL_BEGIN

/** 网络类型
 */
typedef NS_ENUM(NSUInteger, RFKTNetworkType) {
    RFKTNetworkTypeNotConneted = 0,
    RFKTNetworkTypeWIFI = 1,
    RFKTNetworkType2G = 2,
    RFKTNetworkType3G = 3,
    RFKTNetworkType4G = 4,
    RFKTNetworkType5G = 5,
    RFKTNetworkTypeUnknown = 999,
};

/** 当前设备网络状态
 */
@interface RFKTDeviceNetworkState : NSObject

/** 当前网络类型
 */
+ (RFKTNetworkType)currentNetworkType;

/** 网络是否可用
 */
+ (BOOL)isReachable;

/** 是否为Wifi网络
 */
+ (BOOL)isReachableViaWiFi;

/// 获得RFKTNetworkType的字符串态
/// @param type 网络类型
+ (NSString *)networkTypeStr:(RFKTNetworkType)type;

@end

NS_ASSUME_NONNULL_END
