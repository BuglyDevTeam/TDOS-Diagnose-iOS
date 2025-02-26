//
//  TDMMKVImpl.m
//  RDelivery
//
//  Created by selmerzhang on 2021/8/19.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDMMKVImpl.h"
#import "TDIAUtil.h"
#import <MMKV/MMKV.h>
#import <TargetConditionals.h>

@interface TDMMKVImpl ()

/// MMKV
@property (nonatomic, strong) MMKV *mmkv;

@end

@implementation TDMMKVImpl


+ (instancetype)createKVWithName:(NSString *)name {
    NSAssert(name.length > 0, @"Invalid name!");
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        NSString *defaultPath = nil; //mmkv default: Documents/mmkv
#if TARGET_OS_OSX
        NSFileManager *fileManager = [NSFileManager defaultManager];
        NSURL *appSupportDirectory = [fileManager URLForDirectory:NSApplicationSupportDirectory
                                                         inDomain:NSUserDomainMask
                                                appropriateForURL:nil create:YES error:nil];

        if (appSupportDirectory) {
            NSString *bundleIdentifier = [TDIAUtil bundleIdentifier];
            NSURL *appSpecificDirectory = [appSupportDirectory URLByAppendingPathComponent:bundleIdentifier];
            NSError *error = nil;
            BOOL success = [fileManager createDirectoryAtURL:appSpecificDirectory
                                 withIntermediateDirectories:YES attributes:nil error:&error];
            if (!success) {
                NSLog(@"Error creating app specific directory: %@", error);
            }
            defaultPath = appSpecificDirectory.path;
        }
#endif
        [MMKV initializeMMKV:defaultPath];
    });
    TDMMKVImpl *impl = [TDMMKVImpl new];
    impl.mmkv = [MMKV mmkvWithID:name];
    return impl;
}

/**
 是否存在key对应的value
 @param key key
 @return 返回结果
 */
- (BOOL)containsKey:(nonnull NSString *)key {
    return [self.mmkv containsKey:key];
}

/**
 * 获取当前实例的所有Key
 */
- (nullable NSArray *)allKeys {
    return [self.mmkv allKeys];
}

/**
 存储NSData类型的值
 @param key key
 @param value value
 @return 返回是否成功
 */
- (BOOL)setData:(nullable NSData *)value forKey:(nonnull NSString *)key {
    return [self.mmkv setData:value forKey:key];
}

/**
 获取NSData类型的值
 @param key key
 @return 返回结果
 */
- (nullable NSData *)dataForKey:(nonnull NSString *)key {
    return [self.mmkv getDataForKey:key];
}

/**
 * 根据Key移除当前的Key-Value
 * @param key 对应的Key,不可以为空
 */
- (void)removeValueForKey:(nonnull NSString *)key {
    [self.mmkv removeValueForKey:key];
}

/**
 * 根据一组Key移除当前的一组Key-Value
 * @param arrKeys 对应的一组Key,不可以为空
 */
- (void)removeValuesForKeys:(nonnull NSArray<NSString *> *)arrKeys {
    [self.mmkv removeValuesForKeys:arrKeys];
}

/**
 存储String类型的value
 @param key key
 @param str value
 @return 返回是否成功
 */
- (BOOL)setString:(nullable NSString *)str forKey:(nonnull NSString *)key {
    return [self.mmkv setString:str forKey:key];
}

/**
 获取String类型的value
 @param key key
 @return 返回value
 */
- (nullable NSString *)stringForKey:(nonnull NSString *)key {
    return [self.mmkv getStringForKey:key];
}

/**
 存储NSNumber类型的value
 @param key key
 @param value value
 @return 返回是否成功
 */
- (BOOL)setNumber:(nullable NSNumber *)value forKey:(nonnull NSString *)key {
    return [self.mmkv setObject:value forKey:key];
}

/**
 获取NSNumber类型的value
 @param key key
 @return 返回value
 */
- (nullable NSNumber *)numberForKey:(nonnull NSString *)key {
    return [self.mmkv getObjectOfClass:NSNumber.class forKey:key];
}

/**
 存储BOOL类型的值
 @param key key
 @param value value
 @return 返回是否成功
 */
- (BOOL)setBool:(BOOL)value forKey:(nonnull NSString *)key {
    return [self.mmkv setBool:value forKey:key];
}

/**
 获取BOOL类型的值
 @param key key
 @return 返回结果
 */
- (BOOL)boolForKey:(nonnull NSString *)key {
    return [self.mmkv getBoolForKey:key];
}

/**
 存储NSObject类型的值
 @param key key
 @return 返回是否成功
 */
- (BOOL)setObject:(nullable NSObject<NSCoding> *)object forKey:(nonnull NSString *)key {
    return [self.mmkv setObject:object forKey:key];
}

/**
 获取NSObject类型的值
 @param key key
 @param cls object对应的Class
 @return 返回结果
 */
- (nullable id)objectForKey:(nonnull NSString *)key withClass:(nonnull Class)cls {
    return [self.mmkv getObjectOfClass:cls forKey:key];
}

/**
 清除所有内容
 */
- (void)clearAll {
    [self.mmkv clearAll];
}

/**
 * 剔除被删掉的Key-Value占据的磁盘空间
 */
- (void)trim {
    [self.mmkv trim];
}

/**
 * 清理内存缓存
 */
- (void)clearMemoryCache {
    [self.mmkv clearMemoryCache];
}

@end
