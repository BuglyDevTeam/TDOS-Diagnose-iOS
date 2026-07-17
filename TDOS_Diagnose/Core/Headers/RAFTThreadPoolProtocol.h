//
//  RAFTThreadPoolProtocol.h
//  RaftInterface-iOS
//
//  Created by jeannieliu(刘锦) on 2021/7/27.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 线程池管理协议
@protocol RAFTThreadPoolProtocol <NSObject>

/// 用于执行一些短平快的简单任务
/// @param task 执行的任务
- (void)execSimpleTask:(dispatch_block_t)task;

/// 用于执行一些可能需要花点时间的任务，比如下载
/// @param task 执行的任务
- (void)execUtilityTask:(dispatch_block_t)task;

/// 用于执行IO操作类型的任务
/// @param task 执行的任务
- (void)execIOTask:(dispatch_block_t)task;

@end

NS_ASSUME_NONNULL_END
