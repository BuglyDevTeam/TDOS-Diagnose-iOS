//   
//  UIViewController+RFKT.h
//  RaftKit
//  
//  Created by raycgwang on 2021/5/13.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIViewController (RFKT)

/// Return the top view controller of given one
- (UIViewController *)rfkt_frontViewController;

@end

NS_ASSUME_NONNULL_END
