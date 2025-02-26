//   
//  UIImage+RFKT.h
//  RaftKit
//  
//  Created by selmerzhang on 2021/5/18.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (RFKT)

/**
 *  创建一个size为(1, 1)的纯色的UIImage
 *
 *  @param color 图片的颜色
 *
 *  @return 纯色的UIImage
 */
+ (nullable UIImage *)rfkt_imageWithColor:(nullable UIColor *)color;

/// 获取当前屏幕所有显示窗口的截图
+ (UIImage *)rfkt_screenshot;

@end

NS_ASSUME_NONNULL_END
