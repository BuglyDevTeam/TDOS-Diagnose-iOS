//   
//  RFKTWindowManager.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/28.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RFKTWindow.h"

NS_ASSUME_NONNULL_BEGIN

/// Manager of plugin created windows
@interface RFKTWindowManager : NSObject

/// Singleton
+ (instancetype)sharedInstance;

/// Change all RFKTWindow's default level
/// @param level UIWindowLevel
- (void)setGlobalRFKTWindowDefaultLevel:(UIWindowLevel)level;

/// Default window level set from external, @(CGFloat)
- (nullable NSNumber *)globalGlobalRFKTWindowDefaultLevel;

/// Get RFKTWindow with specific key
/// @param key key for window
- (nullable RFKTWindow *)windowForKey:(NSString *)key;

/// Show a new window
/// @param rootVC UIViewController *
- (void)showWindowWithRootVC:(UIViewController<RFKTWindowEventDelegate> *)rootVC;
/// Show a new window with specific key
/// @param key NSString *
/// @param rootVC UIViewController *
- (void)showWindowWithKey:(nullable NSString *)key rootVC:(UIViewController<RFKTWindowEventDelegate> *)rootVC;

/// Hide the given window
/// @param window UIWindow
- (void)destoryWindow:(UIWindow *)window;
/// Hide the window with specific key
/// @param key NSString *
- (void)destoryWindowWithKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
