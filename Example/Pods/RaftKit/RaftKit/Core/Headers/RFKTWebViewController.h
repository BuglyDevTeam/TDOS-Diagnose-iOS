//   
//  RFKTWebViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2022/7/21.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RFKTWebViewController : UIViewController

/// URL to load
@property (nonatomic, strong) NSURL *requestURL;

@end

NS_ASSUME_NONNULL_END
