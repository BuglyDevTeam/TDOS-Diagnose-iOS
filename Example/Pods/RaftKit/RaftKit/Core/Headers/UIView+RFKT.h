//   
//  UIView+RFKT.h
//  RaftKit
//  derived from QMUI
//  Created by selmerzhang on 2021/5/14.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (RFKT_Layout)

/// placeholder value for tmp use
@property (nonatomic, strong) id rfktTmpValue;

/// 将要设置的 frame 用 CGRectApplyAffineTransformWithAnchorPoint 处理后再设置
@property(nonatomic, assign) CGRect rfkt_frameApplyTransform;

/// SafeAreaInsets without warning
- (UIEdgeInsets)rfkt_safeAreaInsets;

/// 等价于 CGRectGetMinY(frame)
@property(nonatomic, assign) CGFloat rfkt_top;

/// 等价于 CGRectGetMinX(frame)
@property(nonatomic, assign) CGFloat rfkt_left;

/// 等价于 CGRectGetMaxY(frame)
@property(nonatomic, assign) CGFloat rfkt_bottom;

/// 等价于 CGRectGetMaxX(frame)
@property(nonatomic, assign) CGFloat rfkt_right;

/// 等价于 CGRectGetWidth(frame)
@property(nonatomic, assign) CGFloat rfkt_width;

/// 等价于 CGRectGetHeight(frame)
@property(nonatomic, assign) CGFloat rfkt_height;

/// 保持其他三个边缘的位置不变的情况下，将顶边缘拓展到某个指定的位置，注意高度会跟随变化。
@property(nonatomic, assign) CGFloat rfkt_extendToTop;

/// 保持其他三个边缘的位置不变的情况下，将左边缘拓展到某个指定的位置，注意宽度会跟随变化。
@property(nonatomic, assign) CGFloat rfkt_extendToLeft;

/// 保持其他三个边缘的位置不变的情况下，将底边缘拓展到某个指定的位置，注意高度会跟随变化。
@property(nonatomic, assign) CGFloat rfkt_extendToBottom;

/// 保持其他三个边缘的位置不变的情况下，将右边缘拓展到某个指定的位置，注意宽度会跟随变化。
@property(nonatomic, assign) CGFloat rfkt_extendToRight;

@property(nonatomic, assign) CGFloat rfkt_centerX;

@property(nonatomic, assign) CGFloat rfkt_centerY;

@end

NS_ASSUME_NONNULL_END
