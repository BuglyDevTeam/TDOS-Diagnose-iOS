//
//  RFKTResourceUsage.h
//  RMonitor
//
//  Created by 张鹏 on 9/1/16.
//  Copyright © 2016 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RFKTResourceCommon.h"
#import "RFKTCpuMonitor.h"
#import "RFKTIOMonitor.h"
#import "RFKTFPSMonitor.h"
#import "RFKTThreadCreateMonitor.h"

NS_ASSUME_NONNULL_BEGIN

@protocol RFKTResourceUsageDelegate <NSObject>

/// return queue for IO and Network hook, default is global queue
- (dispatch_queue_t)queueForRaftKitIOAndNetworkHook;

@end

/// 设备资源使用数据集合
@interface RFKTResourceUsage : NSObject

/// CPU Monitor
@property (nonatomic, strong) RFKTCpuMonitor *cpuMonitor;

/// FPS Monitor
@property (nonatomic, strong) RFKTFPSMonitor *fpsMonitor;

/// Thread Monitor
@property (nonatomic, strong) RFKTThreadCreateMonitor *threadMonitor;

/// IO Monitor
@property (nonatomic, strong) RFKTIOMonitor *ioMonitor;

/// Config delegate for resource usage
@property (nonatomic, weak) id<RFKTResourceUsageDelegate> delegate;


/// Singleton
+ (instancetype)getInstance;

- (NSArray *)getCpuUsage1Min;
- (NSArray *)getCpuUsage3Min;

- (NSArray *)getIOData1Min;
- (NSArray *)getIOData3Min;

- (NSArray *)getMemData1Min;
- (NSArray *)getMemData3Min;

- (NSArray *)getSocketData1Min;
- (NSArray *)getSocketData3Min;

- (NSArray *)getDrawCount1Min;
- (NSArray *)getDrawCount3Min;

- (double)getTotalCpuUsage;
- (RFKTIORecord *)getTotalIOData;
- (RFKTSocketRecord *)getTotalSocketData;
- (RFKTSocketRecord *)getTotalXGData;
- (RFKTSocketRecord *)getTotalWifiData;

- (void)startWithType:(unsigned int)type;
- (void)stop;
- (void)clearAll;
- (BOOL)started;

- (void)setNetworkReconnect;

/// 针对对象添加observer，不需要手动removeObserver
/// @param observer 观察者，类似NotificationCenter用法
/// @param block 回调
- (void)addObserver:(id)observer usingBlock:(void (^)(NSDictionary *dic))block;

- (void)enableCpuStackRecord:(BOOL)enable;
- (void)getAllSocketDebugData:(void (^)(NSDictionary *))callback;
- (void)setStageFetcher:(NSString * (^)(void))fetcher;
- (void)setAppStateFetcher:(NSString * (^)(void))fetcher;

- (void)setSocketDebugMode:(bool)open;
- (void)setIODebugMode:(bool)open;

- (NSDictionary *)getThreadStacksWithAccLimit:(unsigned int)usage;
- (NSDictionary *)getSocketDebugDataSinceLastFetchWithLimitXg:(unsigned int)xgusage wifi:(unsigned int)wifiusage;
- (NSDictionary *)getIODebugDataSinceLastFetchWithLimit:(unsigned int)iousage;

- (void)enableThreadCreateMonitor;
- (void)onThreadCreate:(pthread_t _Nullable *_Nullable)pthread stack:(NSArray *)stack;
- (RFKTThreadCreateRecord *)getThreadCreateRecord;

@end

NS_ASSUME_NONNULL_END
