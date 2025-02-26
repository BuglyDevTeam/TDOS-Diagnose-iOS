//
//  TDOSLoggerProxy.m
//  TDOS-Diagnose
//
//  Created by beckyyao on 2019/11/18.
//  Copyright © 2019 RaftLog. All rights reserved.
//
//  Derived from RFLLoggerProxy
//  Copyright © 2021 RaftKit Team. All rights reserved.

#import "TDOSLoggerProxy.h"

@implementation TDOSLoggerProxy {
    id _logger;
}

+ (instancetype)defaultProxy {
    static dispatch_once_t onceToken;
    static TDOSLoggerProxy *instance = nil;
    dispatch_once(&onceToken, ^{
        instance = [[TDOSLoggerProxy alloc] init];
    });
    return instance;
}

- (instancetype)init {
    return self;
}

- (id<TDLoggingIMPProtocol>)logger {
    return _logger;
}

- (void)setLogger:(id<TDLoggingIMPProtocol>)logger {
    if (_logger == logger)
        return;
    _logger = logger;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel {
    return [_logger methodSignatureForSelector:sel];
}

- (void)forwardInvocation:(NSInvocation *)invocation {
    if ([_logger respondsToSelector:invocation.selector]) {
        [invocation invokeWithTarget:_logger];
    } else {
        [super forwardInvocation:invocation];
    }
}

- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
     format:(NSString *)format, ... NS_REQUIRES_NIL_TERMINATION {
    // NSInvocation 不能转发可变参数消息，单独实现日志接口
    if (format) {
        va_list args;
        va_start(args, format);
        NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
        va_end(args);
        [_logger log:level tag:tag file:file func:func line:line msg:message];
    }
}

@end
