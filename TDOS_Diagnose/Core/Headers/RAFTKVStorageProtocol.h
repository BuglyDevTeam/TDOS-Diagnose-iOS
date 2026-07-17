//
//  RAFTKVStorageProtocol.h
//  RDelivery
//
//  Created by selmerzhang on 2021/8/6.
//  Copyright © 2021 Tencent. All rights reserved.
//

#ifndef RAFTKVStorageProtocol_h
#define RAFTKVStorageProtocol_h

@protocol RAFTKVStorageProtocol <NSObject>

@required

/**
 是否存在key对应的value
 @param key key
 @return 返回结果
 */
- (BOOL)containsKey:(nonnull NSString *)key;

/**
 * 获取当前实例的所有Key
 */
- (nullable NSArray *)allKeys;

/**
 存储NSData类型的值
 @param key key
 @param value value
 @return 返回是否成功
 */
- (BOOL)setData:(nullable NSData *)value forKey:(nonnull NSString *)key;
/**
 获取NSData类型的值
 @param key key
 @return 返回结果
 */
- (nullable NSData *)dataForKey:(nonnull NSString *)key;

/**
 * 根据Key移除当前的Key-Value
 * @param key 对应的Key,不可以为空
 */
- (void)removeValueForKey:(nonnull NSString *)key;

/**
 * 根据一组Key移除当前的一组Key-Value
 * @param arrKeys 对应的一组Key,不可以为空
 */
- (void)removeValuesForKeys:(nonnull NSArray<NSString *> *)arrKeys;

/**
 存储String类型的value
 @param key key
 @param str value
 @return 返回是否成功
 */
- (BOOL)setString:(nullable NSString *)str forKey:(nonnull NSString *)key;

/**
 获取String类型的value
 @param key key
 @return 返回value
 */
- (nullable NSString *)stringForKey:(nonnull NSString *)key;

/**
 存储NSNumber类型的value
 @param key key
 @param value value
 @return 返回是否成功
 */
- (BOOL)setNumber:(nullable NSNumber *)value forKey:(nonnull NSString *)key;

/**
 获取NSNumber类型的value
 @param key key
 @return 返回value
 */
- (nullable NSNumber *)numberForKey:(nonnull NSString *)key;

/**
 存储BOOL类型的值
 @param key key
 @param value value
 @return 返回是否成功
 */
- (BOOL)setBool:(BOOL)value forKey:(nonnull NSString *)key;

/**
 获取BOOL类型的值
 @param key key
 @return 返回结果
 */
- (BOOL)boolForKey:(nonnull NSString *)key;

/**
 存储NSObject类型的值
 @param key key
 @return 返回是否成功
 */
- (BOOL)setObject:(nullable NSObject<NSCoding> *)object forKey:(nonnull NSString *)key;

/**
 获取NSObject类型的值
 @param key key
 @param cls object对应的Class
 @return 返回结果
 */
- (nullable id)objectForKey:(nonnull NSString *)key withClass:(nonnull Class)cls;

@optional
/**
 清除所有内容
 */
- (void)clearAll;

/**
 * 剔除被删掉的Key-Value占据的磁盘空间
 */
- (void)trim;

/**
 * 清理内存缓存
 */
- (void)clearMemoryCache;


@end

#endif /* RAFTKVStorageProtocol_h */
