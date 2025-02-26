//   
//  RFKTMainPanelFeedbackViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/5/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTCommonViewController.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const kRFKTFeedbackNickNameKey;
FOUNDATION_EXPORT NSString *const kRFKTFeedbackContactInfoKey;

@interface RFKTMainPanelFeedbackViewController : RFKTCommonViewController

/// FAQ page or normal feedback page, default NO;
@property (nonatomic, assign) BOOL isFAQPage;

/// new post page, default NO;
@property (nonatomic, assign) BOOL isNewPostPage;;

@end

NS_ASSUME_NONNULL_END
