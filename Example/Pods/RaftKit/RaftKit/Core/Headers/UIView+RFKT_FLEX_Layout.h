//
//  UIView+RFKT_FLEX_Layout.h
//  FLEX
//
//  Created by Tanner Bennett on 7/18/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <UIKit/UIKit.h>

#define Padding(p) UIEdgeInsetsMake(p, p, p, p)

@interface UIView (RFKT_FLEX_Layout)

- (void)rfkt_flex_centerInView:(UIView *)view;
- (void)rfkt_flex_pinEdgesTo:(UIView *)view;
- (void)rfkt_flex_pinEdgesTo:(UIView *)view withInsets:(UIEdgeInsets)insets;
- (void)rfkt_flex_pinEdgesToSuperview;
- (void)rfkt_flex_pinEdgesToSuperviewWithInsets:(UIEdgeInsets)insets;
- (void)rfkt_flex_pinEdgesToSuperviewWithInsets:(UIEdgeInsets)insets aboveView:(UIView *)sibling;
- (void)rfkt_flex_pinEdgesToSuperviewWithInsets:(UIEdgeInsets)insets belowView:(UIView *)sibling;

@end
