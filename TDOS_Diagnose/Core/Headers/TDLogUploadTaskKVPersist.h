//
//  TDLogUploadTaskKVPersist.h
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/25.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDLogUploadTaskModel.h"
#import "RAFTKVStorageFactoryProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@protocol TDLogUploadTaskPersistProtocol <NSObject>

/**
将任务在本地持久化
@param infoModel 任务详细信息模型
@return BOOL 是否持久化成功
*/
- (BOOL)addTaskInfo:(nonnull TDLogUploadTaskModel *)infoModel;

/**
将本地持久化的任务删除
@param infoModel 任务详细信息模型
*/
- (void)removeTaskInfo:(nonnull TDLogUploadTaskModel *)infoModel;

/**
本地持久化的任务进行更新
@param infoModel 任务详细信息模型
@return BOOL 是否更新成功
*/
- (BOOL)updateTaskInfo:(nonnull TDLogUploadTaskModel *)infoModel;

/**
获取本地所有的持久化的任务
@return 所有本地持久化的任务
*/
- (nonnull NSArray <TDLogUploadTaskModel *> *)getAllTaskInfo;

@end


@interface TDLogUploadTaskKVPersist : NSObject <TDLogUploadTaskPersistProtocol>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithKVFactory:(id<RAFTKVStorageFactoryProtocol>)kvFactory;

@end

NS_ASSUME_NONNULL_END
