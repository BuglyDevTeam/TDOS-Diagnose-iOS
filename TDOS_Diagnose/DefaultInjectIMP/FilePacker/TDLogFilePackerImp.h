//
//  TDLogFilePackerImp.h
//  TDOS_Diagnose
//
//  Created by raycgwang on 2022/4/15.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDLogFilePackerProtocol.h"

NS_ASSUME_NONNULL_BEGIN

/// 默认的打包实现
@interface TDLogFilePackerImp : NSObject <TDLogFilePackerProtocol>

/// Tmp directory for packing,
/// default is '/tmp/TDOSLog/'
@property (nonatomic, strong, readonly) NSString *packDir;

@property (nonatomic, readonly) long packerLogExpiredTime;

/// Set custom file packing directory
/// @param tmpPackDir dir full path
- (void)setCustomPackDir:(NSString *)tmpPackDir;

/// 设置packer日志最大存留时间
/// @param time 单位s，默认7（7*24*60*60）天
- (void)setPackerLogExpiredTime:(long)time;

@end

NS_ASSUME_NONNULL_END
