//
//  RFKTNetworkReachability.h
//  RMonitor
//
//  Created by rosen on 16/7/22.
//  Copyright © 2016年 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <netinet/in.h>

/** 网络状态类型
 */
typedef enum {
    RFKTNetState_NotReachable = 0,   //不可达
    RFKTNetState_ReachableViaWiFi,   //Wifi
    RFKTNetState_ReachableViaWWAN    //XG网络
} RFKTNetworkState;

/** 网络变化通知
 */
FOUNDATION_EXTERN NSString *const RFKTNetworkReachabilityChangedNotification;

/** 网络状态判断
 */
@interface RFKTNetworkReachability : NSObject

/** 判断hostName指定的网络可达行
 */
- (instancetype)initWithHostName:(NSString *)hostName;

/** 开启或关闭通知
 */
- (BOOL)startNotifier;
- (void)stopNotifier;

/** 当前网络状态
 */
- (RFKTNetworkState)currentNetworkState;
- (BOOL)connectionRequired;

/** 根据SCNetworkReachabilityFlags判断网络类型
 */
+ (RFKTNetworkState)networkStateForFlags:(SCNetworkReachabilityFlags)flags;

@end
