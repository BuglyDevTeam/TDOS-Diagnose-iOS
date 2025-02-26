//
//  RFKTCpuMonitor.h
//  RMonitor
//
//  Created by 张鹏 on 9/29/15.
//  Copyright © 2015 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define RM_TOTAL_CPU_USAGE_KEY @"TotalUsage"
#define RM_CPU_STACKS_KEY @"Stacks"

typedef void (^RFKTCPUMonitorCallback)(double cpuusage, NSDictionary *threadUsageDic);

/// 设备CPU使用监控
@interface RFKTCpuMonitor : NSObject

/// 是否开启堆栈记录
@property (nonatomic, assign) BOOL enableStackRecord;

- (void)startWithThreadCpulimit:(unsigned int)usage;
- (void)stop;
- (void)clearCache;
- (void)setObserver:(nullable RFKTCPUMonitorCallback)observer;
- (NSDictionary *)getThreadStacksWithAccLimit:(unsigned int)usage;

@end

NS_ASSUME_NONNULL_END
