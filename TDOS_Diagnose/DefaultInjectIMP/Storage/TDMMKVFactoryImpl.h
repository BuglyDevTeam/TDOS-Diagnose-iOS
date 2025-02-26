//
//  TDMMKVFactoryImpl.h
//  RDelivery
//
//  Created by selmerzhang on 2021/8/19.
//  Copyright © 2021 Tencent. All rights reserved.
//

#ifndef TDMMKVFactoryImpl_h
#define TDMMKVFactoryImpl_h

#import "RAFTKVStorageFactoryProtocol.h"

NS_ASSUME_NONNULL_BEGIN

/// KV存储工厂实现
@interface TDMMKVFactoryImpl : NSObject <RAFTKVStorageFactoryProtocol>

/// 获取mmkv存储工厂单例
/// 使用createKVStorageWithName:方法，获取不同的mmkv分组实例
+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END

#endif /* TDMMKVFactoryImpl_h */
