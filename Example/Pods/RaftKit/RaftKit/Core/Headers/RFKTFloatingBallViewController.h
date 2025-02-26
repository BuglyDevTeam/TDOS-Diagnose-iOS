//   
//  RFKTFloatingBallViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/24.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>
#import "RFKTWindowRootViewController.h"

NS_ASSUME_NONNULL_BEGIN

/// Root View Controller of \c RFKTWindow and in charge of the floating ball
@interface RFKTFloatingBallViewController : RFKTWindowRootViewController

/// Show or Hide FloatingBall
/// @param isHidden bool
- (void)setFloatingBallHidden:(BOOL)isHidden;

/// Floating Ball show or not
- (BOOL)isFloatingBallShowing;

/// Show main panel
- (void)showMainPanel;

@end

NS_ASSUME_NONNULL_END
