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

/// Set custom file packing directory
/// @param tmpPackDir dir full path
- (void)setCustomPackDir:(NSString *)tmpPackDir;

@end

NS_ASSUME_NONNULL_END
