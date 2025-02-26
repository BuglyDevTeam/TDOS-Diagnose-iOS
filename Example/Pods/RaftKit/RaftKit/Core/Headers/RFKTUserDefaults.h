//   
//  RFKTUserDefaults.h
//  RaftKit
//  
//  Created by raycgwang on 2021/5/18.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RFKTUserDefaults : NSObject

/// similar to NSUserDefaults's objectForKey: method
+ (nullable id)objectForKey:(NSString *)defaultName;

/// similar to NSUserDefaults's setObject: method
+ (void)setObject:(nullable id)value forKey:(NSString *)defaultName;

/// -removeObjectForKey: is equivalent to -[... setObject:nil forKey:defaultName]
+ (void)removeObjectForKey:(NSString *)defaultName;

@end

NS_ASSUME_NONNULL_END
