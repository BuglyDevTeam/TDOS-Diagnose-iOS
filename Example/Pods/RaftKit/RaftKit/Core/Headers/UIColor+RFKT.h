//   
//  UIColor+RFKT.h
//  RaftKit
//  Derived from QMUIKit
//  
//  Created by selmerzhang on 2021/5/14.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (RFKT)

/**
 *  使用HEX命名方式的颜色字符串生成一个UIColor对象
 *
 *  @param hexString 支持以 # 开头和不以 # 开头的 hex 字符串
 *      #RGB        例如#f0f，等同于#ffff00ff，RGBA(255, 0, 255, 1)
 *      #ARGB       例如#0f0f，等同于#00ff00ff，RGBA(255, 0, 255, 0)
 *      #RRGGBB     例如#ff00ff，等同于#ffff00ff，RGBA(255, 0, 255, 1)
 *      #AARRGGBB   例如#00ff00ff，等同于RGBA(255, 0, 255, 0)
 *
 * @return UIColor对象
 */
+ (nullable UIColor *)rfkt_colorWithHexString:(nullable NSString *)hexString;

/**
 *  将当前色值转换为hex字符串，通道排序是AARRGGBB（与Android保持一致）
 *  @return 色值对应的 hex 字符串，以 # 开头，例如 #00ff00ff
 */
- (NSString *)rfkt_hexString;

/**
 *  获取当前 UIColor 对象里的红色色值
 *
 *  @return 红色通道的色值，值范围为0.0-1.0
 */
- (CGFloat)rfkt_red;

/**
 *  获取当前 UIColor 对象里的绿色色值
 *
 *  @return 绿色通道的色值，值范围为0.0-1.0
 */
- (CGFloat)rfkt_green;

/**
 *  获取当前 UIColor 对象里的蓝色色值
 *
 *  @return 蓝色通道的色值，值范围为0.0-1.0
 */
- (CGFloat)rfkt_blue;

/**
 *  获取当前 UIColor 对象里的透明色值
 *
 *  @return 透明通道的色值，值范围为0.0-1.0
 */
- (CGFloat)rfkt_alpha;

@end

NS_ASSUME_NONNULL_END
