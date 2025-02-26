//
//  NSArray+RFKT_FLEX.h
//  FLEX
//
//  Created by Tanner Bennett on 9/25/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray<T> (Functional)

/// Actually more like flatmap, but it seems like the objc way to allow returning nil to omit objects.
/// So, return nil from the block to omit objects, and return an object to include it in the new array.
/// Unlike flatmap, however, this will not flatten arrays of arrays into a single array.
- (__kindof NSArray *)rfkt_flex_mapped:(id(^)(T obj, NSUInteger idx))mapFunc;
/// Like rfkt_flex_mapped, but expects arrays to be returned, and flattens them into one array.
- (__kindof NSArray *)rfkt_flex_flatmapped:(NSArray *(^)(id, NSUInteger idx))block;
- (instancetype)rfkt_flex_filtered:(BOOL(^)(T obj, NSUInteger idx))filterFunc;
- (void)rfkt_flex_forEach:(void(^)(T obj, NSUInteger idx))block;

/// Unlike \c subArrayWithRange: this will not throw an exception if \c maxLength
/// is greater than the size of the array. If the array has one element and
/// \c maxLength is greater than 1, you get an array with 1 element back.
- (instancetype)rfkt_flex_subArrayUpto:(NSUInteger)maxLength;

+ (instancetype)rfkt_flex_forEachUpTo:(NSUInteger)bound map:(T(^)(NSUInteger i))block;
+ (instancetype)rfkt_flex_mapped:(id<NSFastEnumeration>)collection block:(id(^)(T obj, NSUInteger idx))mapFunc;

- (instancetype)rfkt_flex_sortedUsingSelector:(SEL)selector;

@end

@interface NSMutableArray<T> (Functional)

- (void)rfkt_flex_filter:(BOOL(^)(T obj, NSUInteger idx))filterFunc;

@end
