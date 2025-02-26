//   
//  RFKTCommonViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/4/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>
#import "UIView+RFKT.h"
#import "UIBarButtonItem+RFKT.h"
#import "RFKTCommonDefine.h"
#import "RFKTEmptyView.h"
#import "RFKTWindow.h"
#import "RFKTPlugin.h"
#import "RFKTDataReport.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKTCommonViewController : UIViewController <RFKTWindowEventDelegate>

/// Get/Set the corresponding plugin id for data report
@property (nonatomic, copy, nullable) NSString *rfktPluginID;

/// Called when nav bar close btn clicked
/// @param sender obj
- (void)onNavBarCloseBtnPressed:(id)sender NS_REQUIRES_SUPER;

/// Convenient method for creating a right navigation bar button
/// @param title button's title
/// @param target callback target
/// @param action callback action
- (void)showRightNavBarButtonWithTitle:(NSString *)title target:(id)target action:(SEL)action;


#pragma mark - EmptyView

/**
 *  空列表控件，支持显示提示文字、loading、操作按钮，该属性懒加载
 */
@property(nullable, nonatomic, strong) RFKTEmptyView *emptyView;

/// 当前self.emptyView是否显示
@property(nonatomic, assign, readonly, getter = isEmptyViewShowing) BOOL emptyViewShowing;

/**
 *  显示emptyView
 *  emptyView 的以下系列接口可以按需进行重写
 *
 *  @see RFKTEmptyView
 */
- (void)showEmptyView;

/**
 *  显示loading的emptyView
 */
- (void)showEmptyViewWithLoading;

/**
 *  显示带text、detailText、button的emptyView
 */
- (void)showEmptyViewWithText:(nullable NSString *)text
                   detailText:(nullable NSString *)detailText
                  buttonTitle:(nullable NSString *)buttonTitle
                 buttonAction:(nullable SEL)action;

/**
 *  显示带image、text、detailText、button的emptyView
 */
- (void)showEmptyViewWithImage:(nullable UIImage *)image
                          text:(nullable NSString *)text
                    detailText:(nullable NSString *)detailText
                   buttonTitle:(nullable NSString *)buttonTitle
                  buttonAction:(nullable SEL)action;

/**
 *  显示带loading、image、text、detailText、button的emptyView
 */
- (void)showEmptyViewWithLoading:(BOOL)showLoading
                           image:(nullable UIImage *)image
                            text:(nullable NSString *)text
                      detailText:(nullable NSString *)detailText
                     buttonTitle:(nullable NSString *)buttonTitle
                    buttonAction:(nullable SEL)action;

/**
 *  隐藏emptyView
 */
- (void)hideEmptyView;



@end

NS_ASSUME_NONNULL_END
