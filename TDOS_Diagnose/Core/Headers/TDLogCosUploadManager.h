//   
//  TDLogUploadCosUploader.h
//  TDiagnose
//  
//  Created by raycgwang on 2022/1/5.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogStatusServerModels.h"
#import "TDLogUploadTaskModel.h"
#import "TDLogCosUploadModels.h"

NS_ASSUME_NONNULL_BEGIN


@protocol TDLogCosUploadManagerDelegate <NSObject>

/// 需更新COS临时密钥
/// @param info 上传任务
/// @return 更新结果
- (BOOL)onNeedUpdateCosSecret:(TDLogUploadTaskModel *)info;

@end


/// COS 文件上传管理模块
@interface TDLogCosUploadManager : NSObject

/// COS上传任务代理
@property (nonatomic, weak) id<TDLogCosUploadManagerDelegate> delegate;

/// Singleton
+ (instancetype)sharedInstance;

/// 更新COS上传地址
/// @param url 上传路径
- (void)updateCosUploadUrl:(NSString *)url;

/// 更新临时密钥
/// @param secretInfo 临时密钥对象
- (void)updateTmpSecretInfo:(TDLogUploadTmpCosSecretInfo *)secretInfo;

/// 更新服务器时间与本地时间差
/// @param timeDiff 时间差
- (void)updateServerTimeDiff:(time_t)timeDiff;


#pragma mark -

/// 调用COS上传文件
/// @param filePath 文件路径
/// @param completion 结果回调
- (void)uploadFile:(NSString *)filePath
          taskInfo:(TDLogUploadTaskModel *)uploadInfo
        completion:(TDLogCosUploadCallBack)completion;

@end

NS_ASSUME_NONNULL_END
