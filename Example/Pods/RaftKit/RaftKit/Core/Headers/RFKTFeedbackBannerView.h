//   
//  RFKTFeedbackBannerView.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/29.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// 反馈banner
@interface RFKTFeedbackBannerView : UIView

/// 当前展示的内容
@property (nonatomic, strong, readonly) id currentShowingContent;

/// 滚动文字数组
@property (nonatomic, strong) NSArray *contents;
  
/// 文字停留时长，默认4S
@property (nonatomic, assign) NSTimeInterval timeInterval;
  
/// 文字滚动时长，默认0.3S
@property (nonatomic, assign) NSTimeInterval scrollTimeInterval;

/// 点击后的回调
@property(nonatomic, copy) void (^didClickBlock)(RFKTFeedbackBannerView *banner);

/// 开启定时器
- (void)startTimer;

/// 重置初始状态，释放定时器
- (void)reset;

@end

NS_ASSUME_NONNULL_END
