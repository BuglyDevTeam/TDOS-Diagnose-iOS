//
//  TDMMKVImpl.h
//  RDelivery
//
//  Created by selmerzhang on 2021/8/19.
//  Copyright © 2021 Tencent. All rights reserved.
//

#ifndef TDMMKVImpl_h
#define TDMMKVImpl_h

#import "RAFTKVStorageProtocol.h"

NS_ASSUME_NONNULL_BEGIN

/// KV存储实现
@interface TDMMKVImpl : NSObject <RAFTKVStorageProtocol>

/// 创建或获取KV存储实例
/// @param name 存储ID
+ (instancetype)createKVWithName:(NSString *)name;

@end

NS_ASSUME_NONNULL_END


#endif /* TDMMKVImpl_h */
