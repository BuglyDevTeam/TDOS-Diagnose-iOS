//
//  RFKTIOMonitor.h
//  RMonitor
//
//  Created by 张鹏 on 8/30/16.
//  Copyright © 2016 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RFKTResourceCommon.h"

NS_ASSUME_NONNULL_BEGIN

/// IO监控
@interface RFKTIOMonitor : NSObject

/// 流量统计是否排除loopback地址，default NO
@property (nonatomic, assign) BOOL shouldNetMonitorExcludeLoopbackAddr;

- (void)startAsync:(BOOL)isAsync inQueue:(dispatch_queue_t)queue;
- (RFKTIORecord *)getDataSinceLastFetch;
- (RFKTIORecord *)getTotalData;
- (void)clear;

- (RFKTSocketRecord *)getSocketDataSinceLastFetch;
- (RFKTSocketRecord *)getTotalSocketData;
- (RFKTSocketRecord *)getTotalXGData;
- (RFKTSocketRecord *)getTotalWifiData;

- (long)getSocketPackageNumSinceLastFetch;
- (long)getAllSocketPackage;

- (void)getAllSocketDebugData:(void (^)(NSDictionary *))callback;

- (void)setSocketDebugMode:(bool)open;

/// 文件IO map统计开关
/// @param open 是否打开
- (void)setIODebugMode:(bool)open;

- (NSDictionary *)getSocketDebugDataSinceLastFetchWithLimitXg:(unsigned int)xgusage wifi:(unsigned int)wifiusage;

/// 获取文件IO记录map
/// @param iousage io阈值，write_bytes + read_bytes > iousage超过该阈值才算一个
- (NSDictionary *)getIODebugDataSinceLastFetchWithLimit:(unsigned int)iousage;

@end

NS_ASSUME_NONNULL_END
