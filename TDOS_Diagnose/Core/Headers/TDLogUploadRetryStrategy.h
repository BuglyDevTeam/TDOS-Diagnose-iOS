//
//  TDLogUploadRetryStrategy.h
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/25.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDLogUploadTaskModel.h"

NS_ASSUME_NONNULL_BEGIN

@protocol TDLogUploadRetryStrategyProtocol <NSObject>

/**
是否关闭重试，如果返回YES的话，isMatch始终返回NO
@return BOOL 返回YES则会关闭重试
*/
- (BOOL)isCloseTry;

/**
是否重试
@param infoModel 任务详细信息模型
@return 返回YES说明需要重试，返回NO说明不需要重试
*/
- (BOOL)isMatch:(nonnull TDLogUploadTaskModel *)infoModel;

/**
是否删除任务
@param infoModel 任务详细信息模型
@return 返回YES说明需要删除，返回NO说明不需要删除
*/
- (BOOL)isDeleteTask:(nonnull TDLogUploadTaskModel *)infoModel;

@end


@interface TDLogUploadRetryStrategy : NSObject <TDLogUploadRetryStrategyProtocol>

/// 最大重试次数。达到此次数后，就会删除任务
@property (nonatomic, assign, readonly) NSInteger maxRetryTimes;

/// 初始化TDLogUploadRetryStrategy实例
/// @param maxRetryTimes 最大重试次数（注意，调整分片上传重试次数为该值 * 2）
- (instancetype)initWithMaxRetryTimes:(NSInteger)maxRetryTimes;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
