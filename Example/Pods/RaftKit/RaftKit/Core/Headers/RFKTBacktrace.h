//
//  RFKTBacktrace.h
//  RaftKit
//
//  Created by raycgwang on 2021/6/30.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//
//  Inspired from:
//
//  RACBacktrace.h
//  ReactiveCocoa
//
//  Created by Justin Spahr-Summers on 2012-08-20.
//  Copyright (c) 2012 GitHub, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

FOUNDATION_EXTERN NSString * const kRFKTBacktraceSwitchKey;

/// Preserves backtraces across asynchronous calls.
///
/// On OS X, you can enable the automatic capturing of asynchronous backtraces
/// (in Debug builds) by setting the `DYLD_INSERT_LIBRARIES` environment variable
/// to `@executable_path/../Frameworks/ReactiveCocoa.framework/ReactiveCocoa` in
/// your scheme's Run action settings.
///
/// On iOS, your project and RAC will automatically use the `rac_` GCD functions
/// (declared above) for asynchronous work. Unfortunately, unlike OS X, it's
/// impossible to capture backtraces inside NSOperationQueue or other code
/// outside of your project.
///
/// Once backtraces are being captured, you can `po [RFKTBacktrace backtrace]` in
/// the debugger to print them out at any time.
/// 
@interface RFKTBacktrace : NSObject

/// The backtrace from any previous thread.
@property (nonatomic, strong, readonly) RFKTBacktrace *previousThreadBacktrace;

/// The call stack of this backtrace's thread.
@property (nonatomic, copy, readonly) NSArray *callStackSymbols;

/// Captures the current thread's backtrace, appending it to any backtrace from
/// a previous thread.
+ (instancetype)backtrace;

/// Same as +backtrace, but omits the specified number of frames at the
/// top of the stack (in addition to this method itself).
+ (instancetype)backtraceIgnoringFrames:(NSUInteger)ignoreCount;

@end


