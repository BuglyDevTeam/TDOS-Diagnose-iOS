//
//  RAFTMeasureLogger.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/22.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
    RAFTMeasure日志记录器
 */
@interface RAFTMeasureLogger : NSObject

+ (instancetype)sharedInstance;

#pragma mark - 宿主APP配置
// 宿主APP设置日志输出回调
- (void)setLogDelegate:(id<RAFTMeasureLogProtocol>)logDelegate;

// 宿主APP设置是否开启Debug模式
//  说明：在Debug模式下，出现Error日志会同时触发NSAssert。（默认为NO不开启）
- (void)setIsDebug:(BOOL)isDebug;

#pragma mark - 打印日志
// 输出debug级别日志
- (void)raftMeasureDebugLog:(NSString *)msg;

// 输出info级别日志
- (void)raftMeasureInfoLog:(NSString *)msg;

// 输出warn级别日志
- (void)raftMeasureWarnLog:(NSString *)msg;

// 输出error级别日志
- (void)raftMeasureErrorLog:(NSString *)msg;

@end

NS_ASSUME_NONNULL_END
