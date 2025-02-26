//
//  TDLogCosTaskKVPersist.h
//  TDOS-Diagnose
//
//  Created by raycgwang on 2022/1/14.
//  Copyright © 2021 XMLReader. All rights reserved.

#import <Foundation/Foundation.h>
#import "RAFTKVStorageFactoryProtocol.h"
#import "TDLogCosUploadModels.h"

NS_ASSUME_NONNULL_BEGIN

@interface TDLogCosTaskKVPersist : NSObject

/// 初始化方法
/// @param kvFactory KV工厂
- (instancetype)initWithKVFactory:(id<RAFTKVStorageFactoryProtocol>)kvFactory;

/// 增加或更新一个上传任务
/// @param infoModel 任务对象
- (BOOL)addTaskInfo:(nonnull TDLogCOSUploadTaskInfo *)infoModel;

/// 删除一个上传任务
/// @param infoModel 任务对象
- (void)removeTaskInfo:(nonnull TDLogCOSUploadTaskInfo *)infoModel;

/// 获取全部COS上传任务
- (nonnull NSArray <TDLogCOSUploadTaskInfo *> *)getAllTaskInfos;

#pragma mark -

/// Use \c initWithKVFactory: to initialize
+ (instancetype)new NS_UNAVAILABLE;
/// Use \c initWithKVFactory: to initialize
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
