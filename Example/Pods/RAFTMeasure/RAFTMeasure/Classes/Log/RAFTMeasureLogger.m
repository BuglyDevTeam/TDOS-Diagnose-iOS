//
//  RAFTMeasureLogger.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/22.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureLogger.h"

@interface RAFTMeasureLogger ()

// 日志回调
@property (nonatomic, weak) id<RAFTMeasureLogProtocol> logDelegate;
// Debug模式
@property (nonatomic, assign) BOOL isDebug;

@end

@implementation RAFTMeasureLogger

+ (instancetype)sharedInstance {
    static dispatch_once_t once;
    static RAFTMeasureLogger *logger;
    dispatch_once(&once, ^{
        logger = [[RAFTMeasureLogger alloc] init];
    });
    return logger;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        // 默认不开启Debug模式
        _isDebug = NO;
    }
    return self;
}

#pragma mark - 宿主APP配置
- (void)setLogDelegate:(id<RAFTMeasureLogProtocol>)logDelegate {
    _logDelegate = logDelegate;
}

- (void)setIsDebug:(BOOL)isDebug {
    _isDebug = isDebug;
}

#pragma mark - 打印日志
- (void)raftMeasureDebugLog:(NSString *)msg {
    [self printNSLog:msg];
    [self.logDelegate raftMeasureDebugLog:msg];
}

- (void)raftMeasureInfoLog:(NSString *)msg {
    [self printNSLog:msg];
    [self.logDelegate raftMeasureInfoLog:msg];
}

- (void)raftMeasureWarnLog:(NSString *)msg {
    [self printNSLog:msg];
    [self.logDelegate raftMeasureWarnLog:msg];
}

- (void)raftMeasureErrorLog:(NSString *)msg {
    [self printNSLog:msg];
    [self.logDelegate raftMeasureErrorLog:msg];
#if DEBUG
    if (self.isDebug) {
        NSAssert(NO, msg);
    }
#endif
}

#pragma mark - 模拟器日志打印
- (void)printNSLog:(NSString *)msg {
#if DEBUG
    NSLog(@"%@", msg);
#endif
}

@end
