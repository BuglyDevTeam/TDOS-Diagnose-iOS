//
//  TDLogUploadFileFinder.h
//  文件搜索类
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/16.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDLogUploadFileFilterProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface TDLogUploadFileFinder : NSObject

/**
在files中找出满足过滤条件的file
@param filter 过滤条件
@param files 文件数组
@return 符合条件的文件数组
*/
+ (nullable NSArray <NSString *> *)searchFile:(nonnull id<TDLogUploadFileFilterProtocol>)filter
                                        files:(nonnull NSArray <NSString *> *)files;

/**
在某个文件夹下找出满足过滤条件的file
@param filter 过滤条件
@param directoryPath 文件夹目录
@return 符合条件的文件数组
*/
+ (nullable NSArray <NSString *> *)searchFile:(nonnull id<TDLogUploadFileFilterProtocol>)filter
                                directoryPath:(nonnull NSString *)directoryPath;
/**
递归查找在某个文件夹的全部文件
@param directoryPath 文件夹目录
@return 此文件夹下面的全部文件
*/
+ (NSArray <NSString *> *)getFilesWithDirectoryPath:(nonnull NSString *)directoryPath;

@end

NS_ASSUME_NONNULL_END
