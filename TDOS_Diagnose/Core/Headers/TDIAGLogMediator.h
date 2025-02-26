//   
//  TDIAGLogMediator.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/24.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "RAFTLogDef.h"
#import "TDLoggingIMPProtocol.h"

FOUNDATION_EXTERN NSString * _Nonnull const TDiagnoseLogTag;


#define TDIAGLogDebug(sdkSettings, fmt,...) \
[sdkSettings.logMediator log:RAFTLogLevelDebug \
tag:TDiagnoseLogTag file:__FILE_NAME__ func:__func__ line:__LINE__ format:fmt, ##__VA_ARGS__, nil]
#define TDIAGLogInfo(sdkSettings, fmt,...) \
[sdkSettings.logMediator log:RAFTLogLevelInfo \
tag:TDiagnoseLogTag file:__FILE_NAME__ func:__func__ line:__LINE__ format:fmt, ##__VA_ARGS__, nil]
#define TDIAGLogError(sdkSettings, fmt,...) \
[sdkSettings.logMediator log:RAFTLogLevelError \
tag:TDiagnoseLogTag file:__FILE_NAME__ func:__func__ line:__LINE__ format:fmt, ##__VA_ARGS__, nil]
#define TDIAGLogFatal(sdkSettings, fmt,...) \
[sdkSettings.logMediator log:RAFTLogLevelFatal \
tag:TDiagnoseLogTag file:__FILE_NAME__ func:__func__ line:__LINE__ format:fmt, ##__VA_ARGS__, nil]


NS_ASSUME_NONNULL_BEGIN

/// SDK日志中间件
@interface TDIAGLogMediator : NSObject

/// 根据注入初始化中间层
/// @param logImpl 实现了TDLoggingIMPProtocol协议的实例
- (instancetype)initWithImpl:(id<TDLoggingIMPProtocol>)logImpl;

/// 打日志接口（带格式化字符串）
- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
     format:(NSString *)format, ... __attribute__((format(__NSString__, 6, 7))) NS_REQUIRES_NIL_TERMINATION;

@end


NS_ASSUME_NONNULL_END
