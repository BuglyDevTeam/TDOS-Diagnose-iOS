//
//  RFKTThreadCreateMonitor.h
//  RMonitor
//
//  Created by 张鹏 on 2017/4/6.
//  Copyright © 2017年 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RFKTResourceCommon.h"
#import <pthread.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*rm_thread_monitor_hook)(pthread_t _Nullable *_Nullable pthread, NSArray *stacks);

/// 注册线程monitor hook
/// @param hook hook函数
extern bool rfkt_thread_monitor_hook_install(_Nullable rm_thread_monitor_hook hook);

#ifdef __cplusplus
}  // extern "C"
#endif

@interface RFKTThreadCreateMonitor : NSObject

+ (void)start;

/// 统计创建线程数据
/// @param pthread 线程id
/// @param stack 堆栈
- (void)onThreadCreate:(pthread_t _Nullable *_Nullable)pthread stack:(NSArray *)stack;

/// 获取线程监控数据
- (RFKTThreadCreateRecord *)getRecordSinceLastFetch;

@end

NS_ASSUME_NONNULL_END
