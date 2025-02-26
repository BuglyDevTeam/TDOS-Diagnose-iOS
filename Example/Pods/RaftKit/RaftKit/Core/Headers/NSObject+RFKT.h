//
//  NSObject+RFKT.h
//  RaftKit
//
//  Created by raycgwang on 2021/5/19.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

// The MIT License
//
// Copyright (c) 2016 Dariusz Bukowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 `NSObject` category adding helper methods for swizzling.
 */
@interface NSObject (RFKT_Swizzle)

/**
 Exchanges class methods between two selectors using method swizzling.
 
 @param originalSelector The original selector, which is supposed to have its implementation replaced.
 @param swizzledSelector The swizzled selector, providing the new implementation.
 */
+ (void)rfkt_exchangeClassMethodsWithOriginalSelector:(SEL)originalSelector andSwizzledSelector:(SEL)swizzledSelector;

/**
 Exchanges instance methods between two selectors using method swizzling.
 
 @param originalSelector The original selector, which is supposed to have its implementation replaced.
 @param swizzledSelector The swizzled selector, providing the new implementation.
 */
+ (void)rfkt_exchangeInstanceMethodsWithOriginalSelector:(SEL)originalSelector andSwizzledSelector:(SEL)swizzledSelector;

/**
 Replaces instance method implementation with a block.
 
 @param originalSelector The original selector, which is supposed to have its implementation replaced.
 @param block The block containing new implementation.
 */
+ (IMP)rfkt_replaceMethodWithSelector:(SEL)originalSelector block:(id)block;

@end


@interface NSObject (RFKT_KeyValueCoding)

/**
 iOS 13 下系统禁止通过 KVC 访问私有 API，因此提供这种方式在遇到 access prohibited 的异常时可以取代 valueForKey: 使用。
 
 对 iOS 12 及以下的版本，等价于 valueForKey:。
 
 @link https://github.com/Tencent/QMUI_iOS/issues/617
 
 @param key ivar 属性名，支持下划线或不带下划线
 @return key 对应的 value，如果该 key 原本是非对象的值，会被用 NSNumber、NSValue 包裹后返回
 */
- (nullable id)rfkt_valueForKey:(NSString *)key;

/**
 iOS 13 下系统禁止通过 KVC 访问私有 API，因此提供这种方式在遇到 access prohibited 的异常时可以取代 setValue:forKey: 使用。
 
 对 iOS 12 及以下的版本，等价于 setValue:forKey:。
 
 @link https://github.com/Tencent/QMUI_iOS/issues/617
 
 @param key ivar 属性名，支持下划线或不带下划线
 @return key 对应的 value，如果该 key 原本是非对象的值，会被用 NSNumber、NSValue 包裹后返回
 */
- (void)rfkt_setValue:(nullable id)value forKey:(NSString *)key;



@end


NS_ASSUME_NONNULL_END
