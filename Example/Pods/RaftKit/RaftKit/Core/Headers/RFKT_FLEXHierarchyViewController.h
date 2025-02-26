//
//  FLEXHierarchyViewController.h
//  FLEX
//
//  Created by Tanner Bennett on 1/9/20.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXNavigationController.h"

@protocol RFKT_FLEXHierarchyDelegate <NSObject>
- (void)viewHierarchyDidDismiss:(UIView *)selectedView;
@end

/// A navigation controller which manages two child view controllers:
/// a 3D Reveal-like hierarchy explorer, and a 2D tree-list hierarchy explorer.
@interface RFKT_FLEXHierarchyViewController : RFKT_FLEXNavigationController

+ (instancetype)delegate:(id<RFKT_FLEXHierarchyDelegate>)delegate;
+ (instancetype)delegate:(id<RFKT_FLEXHierarchyDelegate>)delegate
              viewsAtTap:(NSArray<UIView *> *)viewsAtTap
            selectedView:(UIView *)selectedView;

- (void)toggleHierarchyMode;

@end
