//
//  TDLogFilePackerProtocol.h
//  Pods
//
//  Created by raycgwang on 2022/4/15.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#ifndef TDLogFilePackerProtocol_h
#define TDLogFilePackerProtocol_h

/// 压缩组件协议
@protocol TDLogFilePackerProtocol <NSObject>

/// Pack all files to one zip file
/// @param files files (full path)
/// @param zipName zip file's name
- (nullable NSString *)packFiles:(nonnull NSArray<NSString *> *)files
                     withZipName:(nonnull NSString *)zipName;

/// get pack files temp dir, used to clean history temp files
- (nullable NSString *)packFilesTempDir;

/// get pack files expired time, used to clean history temp files
- (long)getPackerLogExpiredTime;

@end


#endif /* TDLogFilePackerProtocol_h */
