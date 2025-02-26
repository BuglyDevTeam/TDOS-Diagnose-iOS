//
//  UIBarButtonItem+RFKT_FLEX.h
//  FLEX
//
//  Created by Tanner on 2/4/20.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <UIKit/UIKit.h>

#define RFKT_FLEXBarButtonItemSystem(item, tgt, sel) \
    [UIBarButtonItem rfkt_flex_systemItem:UIBarButtonSystemItem##item target:tgt action:sel]

@interface UIBarButtonItem (RFKT_FLEX)

@property (nonatomic, readonly, class) UIBarButtonItem *rfkt_flex_flexibleSpace;
@property (nonatomic, readonly, class) UIBarButtonItem *rfkt_flex_fixedSpace;

+ (instancetype)rfkt_flex_itemWithCustomView:(UIView *)customView;
+ (instancetype)rfkt_flex_backItemWithTitle:(NSString *)title;

+ (instancetype)rfkt_flex_systemItem:(UIBarButtonSystemItem)item target:(id)target action:(SEL)action;

+ (instancetype)rfkt_flex_itemWithTitle:(NSString *)title target:(id)target action:(SEL)action;
+ (instancetype)rfkt_flex_doneStyleitemWithTitle:(NSString *)title target:(id)target action:(SEL)action;

+ (instancetype)rfkt_flex_itemWithImage:(UIImage *)image target:(id)target action:(SEL)action;

+ (instancetype)rfkt_flex_disabledSystemItem:(UIBarButtonSystemItem)item;
+ (instancetype)rfkt_flex_disabledItemWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style;
+ (instancetype)rfkt_flex_disabledItemWithImage:(UIImage *)image;

/// @return the receiver
- (UIBarButtonItem *)rfkt_flex_withTintColor:(UIColor *)tint;

- (void)_setWidth:(CGFloat)width;

@end
