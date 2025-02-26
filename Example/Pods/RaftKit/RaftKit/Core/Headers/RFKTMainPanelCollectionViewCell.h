//   
//  RFKTMainPanelCollectionViewCell.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>
#import "RFKTLabel.h"

NS_ASSUME_NONNULL_BEGIN

extern const CGFloat RFKTMainPanelCell_DesignedCellWidth;

/// Cell used in main panel
@interface RFKTMainPanelCollectionViewCell : UICollectionViewCell

/// update label's text and icon
/// @param str tool's description
/// @param image tool's icon, At least one must be provided
- (void)updateText:(NSString *)str andIcon:(UIImage *)image;

/// update label's text and icon
/// @param str tool's description
/// @param image tool's icon, At least one must be provided
/// @param detailStr tool's detail description, states or others
- (void)updateText:(nullable NSString *)str andIcon:(nullable UIImage *)image andDetailText:(nullable NSString *)detailStr;

/// show description text below tool's main name
/// @param detailStr tool's detail description, states or others
- (void)setDetailText:(NSString *)detailStr;

/// show description text below tool's main name,
/// same to \c setDetailText , but use AttributedString
/// @param attDetailStr NSAttributedString
- (void)setDetailAttributedText:(NSAttributedString *)attDetailStr;

/// set icon's tint color
/// @param tintColor UIColor object
- (void)setIconTintColor:(UIColor *)tintColor;

@end


extern CGFloat gRFKTMainPanelHeaderHeight;
extern CGFloat gRFKTMainPanelHeaderWithFeedbackHeight;

/// 主面板自定义Header View
@interface RFKTMainPanelSectionHeader : UICollectionReusableView

/// Header label
@property (nonatomic, strong) RFKTLabel *textLabel;

/// Set Banner View visible or not
/// @param isShow BOOL
/// @param block onclick callback
- (void)setFeedbackBannerViewShow:(BOOL)isShow actionBlock:(nullable void (^)(id))block;

@end

NS_ASSUME_NONNULL_END
