//   
//  TDOSLogger.h
//  TDOS-Diagnose
//  
//  Created by raycgwang on 2022/1/11.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//
//  Derived from RFLLogger

#import <Foundation/Foundation.h>
#import "TDLoggingIMPProtocol.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSString * const TDOSLogColorInfoKey; // 日志染色信息
FOUNDATION_EXTERN NSString * const TDOSLogColorEndTimeKey; // 日志染色结束时间
FOUNDATION_EXTERN NSString * const TDOSLogColorLevelKey; // 日志染色级别

/// 打日志模块配置
@interface TDOSLoggerConfig : NSObject

/// 日志目录, 默认Library/Caches/TDOSLog目录
@property (nonatomic, readonly) NSString *logPath;
/// 默认日志级别，默认RAFTLogLevel_Error
@property (nonatomic, readonly) RAFTLogLevel defaultLogLevel;
/// 加密Key，默认不加密
@property (nonatomic, nullable, readonly) NSString *publicKey;
/// 控制台是否输出，默认关闭
@property (nonatomic, assign) BOOL enableConsoleLog;
/// 日志文件名前缀（可选设置）
@property (nonatomic, copy) NSString *logFilePrefix;
/// "日志文件名前缀"相比之前是否变化（可选设置）
/// 由于修改前缀会导致mmap缓存文件重新生成，该设置项用于告知sdk是否自动更新mmap文件名，
/// 从而避免丢失部分日志信息。
@property (nonatomic, assign) BOOL isLogFilePrefixChanged;

/// 默认配置
+ (instancetype)defaultConfig;

/// 自定义日志设置
/// @param logPath 日志路径
/// @param logPrefix 日志文件名前缀
/// @param level 默认日志级别
/// @param pubKey 加密Key（可选，传空则不加密）
+ (nullable instancetype)configWithLogPath:(NSString *)logPath
                                 logPrefix:(NSString *)logPrefix
                              defaultLevel:(RAFTLogLevel)level
                              andPublicKey:(nullable NSString *)pubKey;

@end


/// 打日志模块实例
@interface TDOSLogger : NSObject <TDLoggingIMPProtocol>

/// 根据配置初始化日志SDK
/// @param config 配置
- (instancetype)initWithConfig:(TDOSLoggerConfig *)config;

/// Use \c initWithConfig: to initialize.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
