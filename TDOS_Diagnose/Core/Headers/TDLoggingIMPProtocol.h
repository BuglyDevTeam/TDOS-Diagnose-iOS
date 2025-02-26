//   
//  TDLoggingIMPProtocol.h
//  RaftKit Team
//  
//  Created by raycgwang on 2021/12/23.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#ifndef TDLoggingIMPProtocol_h
#define TDLoggingIMPProtocol_h

#import <Foundation/Foundation.h>
#import "RAFTLogDef.h"

NS_ASSUME_NONNULL_BEGIN

/// 日志底层功能实现协议
@protocol TDLoggingIMPProtocol <NSObject>

@required

/// 打日志接口（不带格式化字符串）
- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
        msg:(NSString *)msg;

/// 打日志接口（带格式化字符串）
- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
     format:(NSString *)format, ... __attribute__((format(__NSString__, 6, 7))) NS_REQUIRES_NIL_TERMINATION;


#pragma mark - 日志级别染色

/// 获取当前是否处于染色状态
- (BOOL)isColorState;

/// 重置染色级别
- (void)resetColorLevel;

/// 设置Log打印级别
/// @param level 日志级别
- (void)setLogLevel:(RAFTLogLevel)level;

/// 设置打印log的特殊级别, 以及特殊级别的过期时间
/// @param level 日志级别
/// @param endtime 结束时间
- (void)setLogLevel:(RAFTLogLevel)level endTimestamp:(time_t)endtime;

#pragma mark - 日志获取

/// 获取日志列表（按小时打印）
/// @param startTime 开始时间戳
/// @param endTime 结束时间戳
- (nullable NSArray<NSString *> *)getPeroidLogFilesWithStartTime:(NSTimeInterval)startTime
                                                         endTime:(NSTimeInterval)endTime;

#pragma mark - 其他

/// 强制写入日志到文件
/// @param isSync 是否同步写入
- (void)flushLog:(BOOL)isSync;

@optional

/// 获取日志列表，支持限定最大日志量
/// （超过大小优先丢弃旧文件）
///
/// @param startTime 开始时间戳
/// @param endTime 结束时间戳
/// @param sizeLimit 最大日志包
- (nullable NSArray<NSString *> *)getPeroidLogFilesWithStartTime:(NSTimeInterval)startTime
                                                         endTime:(NSTimeInterval)endTime
                                                       sizeLimit:(unsigned long long)sizeLimit;

/// 获取日志文件夹路径。
- (NSString *)getLogFolderPath;

/// 获取日志加密公钥
- (nullable NSString *)getLogEncryptPublicKey;

#pragma mark - 其他设置

/// 设置日志最大存留时间
/// @param time 单位s，默认10（10*24*60*60）天
- (void)setMaxLogAliveTime:(long)time;

/// 设置总的日志文件大小，超出即清理（底层限制最小50M）
/// @param maxSize 总文件大小，默认为0不限制
- (void)setMaxTotalLogFileSize:(int64_t)maxSize;

/// 设置控制台log输出
/// @param enabled 是否开启
- (void)setConsoleLogEnabled:(BOOL)enabled;


#pragma mark - 打日志多实例

/// 从打日志主实例中创建新子实例的便捷方法
/// 该实例共享主实例的部分配置，如加密密钥。
/// @param prefix 日志名前缀
/// @param path 日志本地文件夹路径
/// @param level 默认日志输出级别
- (instancetype)createSubLoggerInstanceWithLogPrefix:(NSString *)prefix
                                             logPath:(NSString *)path
                                  andDefaultLogLevel:(RAFTLogLevel)level;

@end

NS_ASSUME_NONNULL_END

#endif /* TDLoggingIMPProtocol_h */
