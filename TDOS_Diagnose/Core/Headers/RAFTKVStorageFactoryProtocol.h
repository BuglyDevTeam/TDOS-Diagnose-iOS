//
//  RAFTKVStorageFactoryProtocol.h
//  RDelivery
//
//  Created by selmerzhang on 2021/8/6.
//  Copyright © 2021 Tencent. All rights reserved.
//

#ifndef RAFTKVStorageFactoryProtocol_h
#define RAFTKVStorageFactoryProtocol_h

#import "RAFTKVStorageProtocol.h"

@protocol RAFTKVStorageFactoryProtocol <NSObject>

@required
/// 创建KV存储实例
/// @param name 存储的分组名，不同的分组隔离存储
- (nonnull id<RAFTKVStorageProtocol>)createKVStorageWithName:(nonnull NSString *)name;

@optional
/// 初始化KV组件
/// @param rootDir 默认的存储根路径
- (void)initializeKVStorage:(nullable NSString *)rootDir;

@end

#endif /* RAFTKVStorageFactoryProtocol_h */
