//
//  TDMMKVFactoryImpl.m
//  RDelivery
//
//  Created by selmerzhang on 2021/8/19.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDMMKVFactoryImpl.h"
#import "TDMMKVImpl.h"
#import <MMKV/MMKV.h>

@implementation TDMMKVFactoryImpl

/// 获取mmkv存储工厂单例
/// 使用createKVStorageWithName:方法，获取不同的mmkv分组实例
+ (instancetype)sharedInstance {
    static dispatch_once_t onceToken;
    static TDMMKVFactoryImpl *instance = nil;
    dispatch_once(&onceToken, ^{
        instance = [[TDMMKVFactoryImpl alloc] init];
    });
    return instance;
}

/// 创建KV存储实例
/// @param name 存储的分组名，不同的分组隔离存储
- (nonnull id<RAFTKVStorageProtocol>)createKVStorageWithName:(nonnull NSString *)name {
    NSAssert(name.length > 0, @"Invalid storage name!");
    
    if ([NSThread isMainThread]) {
        return [TDMMKVImpl createKVWithName:name];
    } else {
        __block TDMMKVImpl *kv = nil;
        dispatch_sync(dispatch_get_main_queue(), ^{
            kv = [TDMMKVImpl createKVWithName:name];
        });
        return kv;
    }
}

/// 初始化KV组件
/// @param rootDir 默认的存储根路径
- (void)initializeKVStorage:(nullable NSString *)rootDir {
    dispatch_block_t block = ^ {
       [MMKV initializeMMKV:rootDir];
    };
    if ([NSThread isMainThread]) {
        block();
    } else {
        dispatch_sync(dispatch_get_main_queue(),block);
    }
}

@end
