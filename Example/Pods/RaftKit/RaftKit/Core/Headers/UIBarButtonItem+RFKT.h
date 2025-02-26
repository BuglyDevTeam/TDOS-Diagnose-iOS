//   
//  UIBarButtonItem+RFKT.h
//  RaftKit
//  
//  Created by raycgwang on 2021/5/18.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIBarButtonItem (RFKT)

/// convenient method for creating a UIBarButtonItem item with close icon
/// @param target id
/// @param action SEL
+ (instancetype)rfkt_closeItemWithTarget:(nullable id)target action:(nullable SEL)action;

/// convenient method for creating a UIBarButtonItem item
/// @param title NSString *
/// @param target id
/// @param action SEL
+ (instancetype)rfkt_itemWithTitle:(nullable NSString *)title target:(nullable id)target action:(nullable SEL)action;

/// convenient method for creating a UIBarButtonSystemItemFixedSpace item
/// @param width CGFloat value
+ (instancetype)rfkt_fixedSpaceItemWithWidth:(CGFloat)width;

/// convenient method for creating a UIBarButtonSystemItemFlexibleSpace item
+ (instancetype)rfkt_flexibleSpaceItem;

@end

NS_ASSUME_NONNULL_END
