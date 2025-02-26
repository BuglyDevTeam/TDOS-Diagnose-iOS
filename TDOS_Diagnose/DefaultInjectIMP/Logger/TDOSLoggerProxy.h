//
//  TDOSLoggerProxy.h
//  TDOS-Diagnose
//
//  Created by beckyyao on 2019/11/18.
//  Modified by raycgwang on 2022/1/11.
//
//  Derived from RFLLoggerProxy
//  Copyright © 2021 RaftKit Team. All rights reserved.


#import <Foundation/Foundation.h>
#import "RAFTLogDef.h"
#import "TDLoggingIMPProtocol.h"

NS_ASSUME_NONNULL_BEGIN

#define TDOSLog(level, tag_name, formatStr, ...) \
do { \
    id<TDLoggingIMPProtocol> logger = [[TDOSLoggerProxy defaultProxy] logger]; \
    [logger log:level tag:tag_name file:__FILE__ func:__func__ line:__LINE__ format:formatStr, ##__VA_ARGS__, nil]; \
} while (0)

#define TDLogDebug(tag, format, ...) TDOSLog(RAFTLogLevelDebug, tag, format, ##__VA_ARGS__)
#define TDLogInfo(tag, format, ...) TDOSLog(RAFTLogLevelInfo, tag, format, ##__VA_ARGS__)
#define TDLogWarn(tag, format, ...) TDOSLog(RAFTLogLevelWarn, tag, format, ##__VA_ARGS__)
#define TDLogError(tag, format, ...) TDOSLog(RAFTLogLevelError, tag, format, ##__VA_ARGS__)
#define TDLogFatal(tag, format, ...) TDOSLog(RAFTLogLevelFatal, tag, format, ##__VA_ARGS__)


/// 打日志模块解耦代理（可选集成）
@interface TDOSLoggerProxy : NSProxy <TDLoggingIMPProtocol>

/// 日志实例
@property (nonatomic, readonly) id<TDLoggingIMPProtocol> logger;

/// 默认实例
+ (instancetype)defaultProxy;

/// 设置自定义日志底层实现
/// @param logger 日志实现
- (void)setLogger:(id<TDLoggingIMPProtocol>)logger;

@end

NS_ASSUME_NONNULL_END
