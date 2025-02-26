//   
//  RFKTWindow.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/24.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RFKTWindowEventDelegate <NSObject>

/// 是否响应特定位置touch事件
/// @param pointInWindow touch事件坐标
- (BOOL)shouldHandleTouchAtPoint:(CGPoint)pointInWindow;

/// 是否可以成为keyWindow
- (BOOL)canBecomeKeyWindow;

@end

@interface RFKTWindow : UIWindow

/// Window事件代理
@property (nonatomic, weak) id <RFKTWindowEventDelegate> eventDelegate;

/// Tracked so we can restore the key window after dismissing a modal.
/// We need to become key after modal presentation so we can correctly capture input.
/// If we're just showing the toolbar, we want the main app's window to remain key
/// so that we don't interfere with input, status bar, etc.
@property (nonatomic, readonly, nullable, weak) UIWindow *previousKeyWindow;

@end

NS_ASSUME_NONNULL_END
