//
//  RAFTFileProtocol.h
//  RaftInterface-iOS
//
//  Created by jeannieliu(刘锦) on 2021/7/27.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 文件操作协议
@protocol RAFTFileProtocol <NSObject>

@required

/// 解压缩
/// @param path 压缩包文件路径
/// @param destination 解压目录
/// @param overwrite 是否覆盖
/// @param password 密码
- (NSError *)unzipFileAtPath:(NSString *)path
                 destination:(NSString *)destination
                   overwrite:(BOOL)overwrite
                    password:(nullable NSString *)password;

@end

NS_ASSUME_NONNULL_END
