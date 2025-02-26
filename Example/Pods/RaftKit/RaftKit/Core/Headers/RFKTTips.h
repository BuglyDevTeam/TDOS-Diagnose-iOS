/**
 * Tencent is pleased to support the open source community by making QMUI_iOS available.
 * Copyright (C) 2016-2020 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
 */

//
//  RFKTTips.h
//  qmui
//
//  Created by QMUI Team on 15/12/25.
//  Modified by RaftKit Team

#import <UIKit/UIKit.h>
#import "RFKTToastView.h"
#import "RFKTUtility.h"

// 自动计算秒数的标志符，在 delay 里面赋值 RFKTTipsAutomaticallyHideToastSeconds 即可通过自动计算 tips 消失的秒数
extern const NSInteger RFKTTipsAutomaticallyHideToastSeconds;

/// 默认的 parentView
#define DefaultTipsParentView ([RFKTUtility appKeyWindowIgoreRFKTWindow:NO])

/**
 * 简单封装了 QMUIToastView，支持弹出纯文本、loading、succeed、error、info 等五种 tips。如果这些接口还满足不了业务的需求，可以通过 RFKTTips 的分类自行添加接口。
 * 注意用类方法显示 tips 的话，会导致父类的 willShowBlock 无法正常工作，具体请查看 willShowBlock 的注释。
 * @warning 使用类方法，除了 showLoading 系列方法不会自动隐藏外，其他方法如果没有 delay 参数，则会自动隐藏
 * @see [QMUIToastView willShowBlock]
 */
@interface RFKTTips : RFKTToastView

NS_ASSUME_NONNULL_BEGIN

/// 实例方法：需要自己addSubview，hide之后不会自动removeFromSuperView

- (void)showLoading;
- (void)showLoading:(nullable NSString *)text;
- (void)showLoadingHideAfterDelay:(NSTimeInterval)delay;
- (void)showLoading:(nullable NSString *)text hideAfterDelay:(NSTimeInterval)delay;
- (void)showLoading:(nullable NSString *)text detailText:(nullable NSString *)detailText;
- (void)showLoading:(nullable NSString *)text detailText:(nullable NSString *)detailText hideAfterDelay:(NSTimeInterval)delay;

- (void)showWithText:(nullable NSString *)text;
- (void)showWithText:(nullable NSString *)text hideAfterDelay:(NSTimeInterval)delay;
- (void)showWithText:(nullable NSString *)text detailText:(nullable NSString *)detailText;
- (void)showWithText:(nullable NSString *)text detailText:(nullable NSString *)detailText hideAfterDelay:(NSTimeInterval)delay;

- (void)showSucceed:(nullable NSString *)text;
- (void)showSucceed:(nullable NSString *)text hideAfterDelay:(NSTimeInterval)delay;
- (void)showSucceed:(nullable NSString *)text detailText:(nullable NSString *)detailText;
- (void)showSucceed:(nullable NSString *)text detailText:(nullable NSString *)detailText hideAfterDelay:(NSTimeInterval)delay;

- (void)showError:(nullable NSString *)text;
- (void)showError:(nullable NSString *)text hideAfterDelay:(NSTimeInterval)delay;
- (void)showError:(nullable NSString *)text detailText:(nullable NSString *)detailText;
- (void)showError:(nullable NSString *)text detailText:(nullable NSString *)detailText hideAfterDelay:(NSTimeInterval)delay;

- (void)showInfo:(nullable NSString *)text;
- (void)showInfo:(nullable NSString *)text hideAfterDelay:(NSTimeInterval)delay;
- (void)showInfo:(nullable NSString *)text detailText:(nullable NSString *)detailText;
- (void)showInfo:(nullable NSString *)text detailText:(nullable NSString *)detailText hideAfterDelay:(NSTimeInterval)delay;

/// 类方法：主要用在局部一次性使用的场景，hide之后会自动removeFromSuperView

+ (RFKTTips *)createTipsToView:(UIView *)view;

+ (RFKTTips *)showLoadingInView:(UIView *)view;
+ (RFKTTips *)showLoading:(nullable NSString *)text inView:(UIView *)view;
+ (RFKTTips *)showLoadingInView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;
+ (RFKTTips *)showLoading:(nullable NSString *)text inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;
+ (RFKTTips *)showLoading:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view;
+ (RFKTTips *)showLoading:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;

+ (RFKTTips *)showWithText:(nullable NSString *)text;
+ (RFKTTips *)showWithText:(nullable NSString *)text detailText:(nullable NSString *)detailText;
+ (RFKTTips *)showWithText:(nullable NSString *)text inView:(UIView *)view;
+ (RFKTTips *)showWithText:(nullable NSString *)text inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;
+ (RFKTTips *)showWithText:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view;
+ (RFKTTips *)showWithText:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;

+ (RFKTTips *)showSucceed:(nullable NSString *)text;
+ (RFKTTips *)showSucceed:(nullable NSString *)text detailText:(nullable NSString *)detailText;
+ (RFKTTips *)showSucceed:(nullable NSString *)text inView:(UIView *)view;
+ (RFKTTips *)showSucceed:(nullable NSString *)text inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;
+ (RFKTTips *)showSucceed:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view;
+ (RFKTTips *)showSucceed:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;

+ (RFKTTips *)showError:(nullable NSString *)text;
+ (RFKTTips *)showError:(nullable NSString *)text detailText:(nullable NSString *)detailText;
+ (RFKTTips *)showError:(nullable NSString *)text inView:(UIView *)view;
+ (RFKTTips *)showError:(nullable NSString *)text inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;
+ (RFKTTips *)showError:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view;
+ (RFKTTips *)showError:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;

+ (RFKTTips *)showInfo:(nullable NSString *)text;
+ (RFKTTips *)showInfo:(nullable NSString *)text detailText:(nullable NSString *)detailText;
+ (RFKTTips *)showInfo:(nullable NSString *)text inView:(UIView *)view;
+ (RFKTTips *)showInfo:(nullable NSString *)text inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;
+ (RFKTTips *)showInfo:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view;
+ (RFKTTips *)showInfo:(nullable NSString *)text detailText:(nullable NSString *)detailText inView:(UIView *)view hideAfterDelay:(NSTimeInterval)delay;

/// 隐藏 tips
+ (void)hideAllTipsInView:(UIView *)view;
+ (void)hideAllTips;

/// 自动隐藏 toast 可以使用这个方法自动计算秒数
+ (NSTimeInterval)smartDelaySecondsForTipsText:(NSString *)text;

NS_ASSUME_NONNULL_END

@end
