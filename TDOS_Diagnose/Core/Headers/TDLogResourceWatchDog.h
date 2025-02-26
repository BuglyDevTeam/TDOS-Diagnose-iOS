//
//  TDLogResourceWatchDog.h
//  TDOS_Diagnose
//
//  Created by raycgwang on 2022/4/26.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#import <Foundation/Foundation.h>
@class TDLogSDKConfig;

NS_ASSUME_NONNULL_BEGIN

/// Resource WatchDog
@interface TDLogResourceWatchDog : NSObject

/// Init method
/// @param sdkConfig SDK配置项
- (instancetype)initWithSDKConfig:(TDLogSDKConfig *)sdkConfig;

/// 是否通过频率限制检查
/// 时机：文件打包前，当前仅对自动上报执行
///
/// @param tag 自动上报标签
/// @param errorMsg 错误信息
/// @param guid 用户ID
- (BOOL)canPassFrequencyLimitWithTag:(NSString *)tag
                                guid:(NSString *)guid
                            errorMsg:(NSString *_Nullable *_Nullable)errorMsg;

/// 是否通过流量限制检查
/// 时机：打包后，当前仅对自动上报执行
///
/// @param fileSize 文件大小
/// @param tag 自动上报标签
/// @param errorMsg 错误信息
/// @param guid 用户ID
- (BOOL)canPassTrafficLimitWithFileSize:(NSUInteger)fileSize
                                   guid:(NSString *)guid
                                    tag:(NSString *)tag
                               errorMsg:(NSString *_Nullable *_Nullable)errorMsg;

@end

NS_ASSUME_NONNULL_END
