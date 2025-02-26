//
//  TDIAUserDefaults.h
//  TDOS-Diagnose
//
//  Created by raycgwang on 2022/1/15.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TDIAUserDefaults : NSObject

/// similar to NSUserDefaults's objectForKey: method
+ (nullable id)objectForKey:(NSString *)defaultName;

/// similar to NSUserDefaults's objectForKey: method
+ (nullable id)objectForKey:(NSString *)defaultName ofUserId:(NSString *)uid;

/// similar to NSUserDefaults's setObject: method
+ (void)setObject:(nullable id)value forKey:(NSString *)defaultName;

/// similar to NSUserDefaults's setObject: method
+ (void)setObject:(nullable id)value forKey:(NSString *)defaultName ofUserId:(NSString *)uid;

/// -removeObjectForKey: is equivalent to -[... setObject:nil forKey:defaultName]
+ (void)removeObjectForKey:(NSString *)defaultName;

/// -removeObjectForKey: is equivalent to -[... setObject:nil forKey:defaultName]
+ (void)removeObjectForKey:(NSString *)defaultName ofUserId:(NSString *)uid;

@end

NS_ASSUME_NONNULL_END
