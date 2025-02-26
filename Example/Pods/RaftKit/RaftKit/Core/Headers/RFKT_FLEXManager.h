//
//  FLEXManager.h
//  Flipboard
//
//  Created by Ryan Olson on 4/4/14.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXExplorerToolbar.h"

#if !RFKT_FLEX_AT_LEAST_IOS13_SDK
@class UIWindowScene;
#endif

NS_ASSUME_NONNULL_BEGIN

@interface RFKT_FLEXManager : NSObject

@property (nonatomic, readonly, class) RFKT_FLEXManager *sharedManager;

@property (nonatomic, readonly) BOOL isHidden;
@property (nonatomic, readonly) RFKT_FLEXExplorerToolbar *toolbar;

- (void)showExplorer;
- (void)hideExplorer;
- (void)toggleExplorer;

- (void)showExplorerDistanceMode;

/// Programmatically dismiss anything presented by RFKT_FLEX, leaving only the toolbar visible.
- (void)dismissAnyPresentedTools:(void (^_Nullable)(void))completion;
/// Programmatically present something on top of the RFKT_FLEX toolbar.
/// This method will automatically dismiss any currently presented tool,
/// so you do not need to call \c dismissAnyPresentedTools: yourself.
- (void)presentTool:(UINavigationController *(^)(void))viewControllerFuture
         completion:(void (^_Nullable)(void))completion;

/// Use this to present the explorer in a specific scene when the one
/// it chooses by default is not the one you wish to display it in.
- (void)showExplorerFromScene:(UIWindowScene *)scene API_AVAILABLE(ios(13.0));

#pragma mark - Misc

/// Default database password is @c nil by default.
/// Set this to the password you want the databases to open with.
@property (copy, nonatomic) NSString *defaultSqliteDatabasePassword;

@end


typedef UIViewController * _Nullable(^RFKT_FLEXCustomContentViewerFuture)(NSData *data);

NS_ASSUME_NONNULL_END
