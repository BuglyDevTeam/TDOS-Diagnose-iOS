//   
//  RFKTSandboxViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/4/1.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTCommonViewController.h"


typedef enum : NSUInteger {
    RFKTSandboxVCMode_Normal,
    RFKTSandboxVCMode_SelectFile,
    RFKTSandboxVCMode_SelectFolder,
} RFKTSandboxVCMode;

typedef NS_ENUM(NSUInteger, RFKTSandboxSortType) {
    RFKTSandboxSortTypeNameAZ,
    RFKTSandboxSortTypeNameZA,
    RFKTSandboxSortTypeSizeAZ,
    RFKTSandboxSortTypeSizeZA,
};

NS_ASSUME_NONNULL_BEGIN
@class RFKTSandboxViewController;
@protocol RFKTSandboxViewControllerSelectDelegate <NSObject>

/// file/folder selection's callback
- (void)onSandboxVC:(RFKTSandboxViewController *)vc didSelectPath:(NSString *)selectedPath;

@end

/// Sandbox Viewer
@interface RFKTSandboxViewController : RFKTCommonViewController

/// Path to the directory
@property (nonatomic, copy) NSString *path;

/// List sort type, default by name A-Z
@property (nonatomic, assign) RFKTSandboxSortType sortType;

/// Init with specific mode
/// @param mode RFKTSandboxVCMode
/// @param delegate callback delegate
- (instancetype)initWithMode:(RFKTSandboxVCMode)mode
                 andDelegate:(nullable id<RFKTSandboxViewControllerSelectDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
