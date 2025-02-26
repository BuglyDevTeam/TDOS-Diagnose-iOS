//   
//  RFKTLogViewerFilterController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/8/13.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTCommonViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class RFKTLogViewerFilterController;
@protocol RFKTLogViewerFilterDelegate <NSObject>

- (NSArray *)getCurrentRules;

- (void)onLogViewerFilterFinishEdit:(RFKTLogViewerFilterController *)vc;

@end

@interface RFKTLogViewerFilterController : RFKTCommonViewController

/// delegate
@property (nonatomic, weak) id<RFKTLogViewerFilterDelegate> delegate;

/// rules for log filter
@property (nonatomic, strong) NSMutableArray *rules;

@end

NS_ASSUME_NONNULL_END
