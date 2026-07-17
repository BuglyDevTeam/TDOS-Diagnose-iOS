//
//  TDLogConfigPullTask.h
//  TDOS-Diagnose
//
//  Created by raycgwang on 2022/1/20.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDLogConfigServerModels.h"

NS_ASSUME_NONNULL_BEGIN

@class TDLogConfigPullTask;
/// 拉取配置回包的block
/// @param responseObject 回包数据
/// @param task 请求task，带回一些请求信息用于上报/异常情况处理
/// @param error 错误信息
typedef void(^TDLogGetConfigCompletedBlock)(TDLogConfigResponseInfo * _Nullable responseObject,
                                            TDLogConfigPullTask * _Nullable task,
                                            NSError * _Nullable error);

/// 拉取配置请求的task，记录请求信息
@interface TDLogConfigPullTask : NSObject

/// 拉取配置的回调
@property (nonatomic, copy) TDLogGetConfigCompletedBlock getConfigHandler;

/// 请求的id，用生成请求时的时间戳表示
@property (nonatomic, copy) NSString *requestId;
/// 发起请求时的GUID
@property (nonatomic, copy) NSString *requestGuid;
/// 请求开始时间
@property (nonatomic, assign) NSTimeInterval startTime;
/// 请求上一阶段结束时间
@property (nonatomic, assign) NSTimeInterval stepEndTime;

#pragma mark - 数据上报辅助字段

/// 任务是否为Push触发
@property (nonatomic, assign) BOOL isFromPush;


@end

NS_ASSUME_NONNULL_END
