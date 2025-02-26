//   
//  RFKTConfigRequestManager.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/11/19.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "RFKTConfigServerJsonModel.h"

NS_ASSUME_NONNULL_BEGIN

@class RFKTPullConfigTask;
/// 拉取配置回包的block
/// @param responseObject 回包数据
/// @param task 请求task，带回一些请求信息用于上报/异常情况处理
/// @param error 错误信息
typedef void(^RFKTGetConfigCompletedBlock)(RFKTConfigServerPullResponse * _Nullable responseObject,
                                           RFKTPullConfigTask * _Nullable task,
                                           NSError * _Nullable error);

@interface RFKTConfigRequestManager : NSObject

/// 向Server发起配置请求
/// @param getConfigHandler 回调Block
- (void)requestConfigsWithCompleteHandler:(RFKTGetConfigCompletedBlock)getConfigHandler;

@end

NS_ASSUME_NONNULL_END
