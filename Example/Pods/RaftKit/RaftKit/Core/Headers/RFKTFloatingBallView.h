//   
//  RFKTFloatingBallView.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/24.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, RFKTFloatingBallType) {
    RFKTFloatingBallTypeCircle,
    RFKTFloatingBallTypeRoundedCorner,
    RFKTFloatingBallTypeUnknown,
};

NS_ASSUME_NONNULL_BEGIN

@protocol RFKTFloatingBallViewProtocol <NSObject>

/// Called when floatingball's center position updated finish by user
/// @param floatingball view
/// @param point center's point
- (void)onFloatingBall:(UIView *)floatingball centerUpdatedByUser:(CGPoint)point;

@end

/// 悬浮球
@interface RFKTFloatingBallView : UIButton

/// Parent VC
@property (nonatomic, weak) UIViewController *parentViewController;
/// FloatingBall's delegate
@property (nonatomic, weak) id<RFKTFloatingBallViewProtocol> delegate;

/// Auto find a correct postion
- (void)autoAdjustPosition;

@end

NS_ASSUME_NONNULL_END
