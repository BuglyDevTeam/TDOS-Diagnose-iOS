//   
//  RFKTCommonDetailViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/1.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTCommonViewController.h"

NS_ASSUME_NONNULL_BEGIN

/// Common detail vc for display strings such as call stacks
@interface RFKTCommonDetailViewController : RFKTCommonViewController

/// the original file path
@property (nonatomic, copy, nullable) NSString *originalFilePath;

/// Initializer
/// @param details detail infos
/// @param titles titles if has
- (instancetype)initWithDetails:(NSArray<NSString *> *)details
                      andTitles:(nullable NSArray<NSString *> *)titles NS_DESIGNATED_INITIALIZER;

/// Unavailable
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil
                         bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
/// Unavailable
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
