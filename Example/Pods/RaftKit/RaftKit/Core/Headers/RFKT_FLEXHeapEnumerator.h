//
//  FLEXHeapEnumerator.h
//  Flipboard
//
//  Created by Ryan Olson on 5/28/14.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^rfkt_flex_object_enumeration_block_t)(__unsafe_unretained id object, __unsafe_unretained Class actualClass);

@interface RFKT_FLEXHeapEnumerator : NSObject

+ (void)enumerateLiveObjectsUsingBlock:(rfkt_flex_object_enumeration_block_t)block;

@end
