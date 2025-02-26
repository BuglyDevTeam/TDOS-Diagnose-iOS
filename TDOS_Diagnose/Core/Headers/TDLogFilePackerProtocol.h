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

@end


#endif /* TDLogFilePackerProtocol_h */
