//   
//  RFKTLogViewerController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/19.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTWindowRootViewController.h"
#import "RFKTLogViewer.h"

NS_ASSUME_NONNULL_BEGIN

@class RFKTLogViewerController;
@protocol RFKTLogViewerControllerDelegate <NSObject>

@required
/// Called when vc is about to dealloc
/// @param controller log viewer controller
- (void)onLogViewerControllerWillDealloc:(RFKTLogViewerController *)controller;

@end

@interface RFKTLogViewerController : RFKTWindowRootViewController

@property (nonatomic, strong) RFKTLogViewer *logViewer;

/// LogViewerController's delegate
@property (nonatomic, weak) id<RFKTLogViewerControllerDelegate> delegate;

/// Show in new window
///
/// Note: This method displays only one log viewer instance,
/// you can use \c RFKTWindowManager to show multiple instances.
- (void)showInSeparateWindow;

@end

NS_ASSUME_NONNULL_END
