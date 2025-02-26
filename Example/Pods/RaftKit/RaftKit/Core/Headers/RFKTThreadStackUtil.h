//   
//  RFKTThreadStackUtil.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/30.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RFKTThreadStackUtil : NSObject

/// Current stacks array, no symbolic
+ (NSArray<NSString *> *)getCurrentThreadStack;

/// All stacks array, no symbolic
+ (NSArray<NSString *> *)getAllThreadStack;


#pragma mark - symbolicate stack

/// symbolicate origin stack
/// @param stacks is the array of stacks
/// the format of each stack in the array is "line module baseAddress offsetAddress"
/// e.g. "5 UIKitCore 0x18941a000 0x18989d7cc"
+ (NSString *)symbolicatedStrWithStackStrings:(NSArray *)stacks;

@end

NS_ASSUME_NONNULL_END
