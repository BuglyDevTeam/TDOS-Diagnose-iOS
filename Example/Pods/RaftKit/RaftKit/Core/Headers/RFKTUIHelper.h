//
//  RFKTUIHelper.h
//  RaftKit
//
//  Created by selmerzhang on 2021/3/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#ifndef RFKTUIHelper_h
#define RFKTUIHelper_h

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RFKTUIHelper : NSObject

/// is iPad device
+ (BOOL)isIPad;

/// 获取 RaftKit.framework Images.xcassets 内的图片资源
/// @param name 图片名
+ (nullable UIImage *)imageWithName:(NSString *_Nonnull)name;

/// Gen image from given text and color
/// @param color backgroundColor
/// @param size image size
/// @param text text in center
/// @param textAttributes text's attributes
/// @param isCircular round or not
+ (nullable UIImage *)textImageWithColor:(UIColor *)color
                                    size:(CGSize)size
                                    text:(NSString *)text
                          textAttributes:(nullable NSDictionary *)textAttributes
                                circular:(BOOL)isCircular;

#pragma mark - Other

/// Return one pixel base on screen scale
+ (CGFloat)pixelOne;


#define STACK_FIXED(w, h) [RFKTUIHelper stackFixedView:w :h]
/// Fixed placeholder view for UIStackView, 固定大小
+ (UIView *)stackFixedView:(CGFloat)width :(CGFloat)height;

#define STACK_SPRING(axis) [RFKTUIHelper stackSpringView:axis]
/// Spring View for UIStackView, 弹簧
/// @param axis Horizontal or Vertical
+ (UIView *)stackSpringView:(UILayoutConstraintAxis)axis;

@end


#pragma mark - UI Layout Helpers

//------------------------------------------------------------
#define IS_IPAD                         [RFKTUIHelper isIPad]

#define PIXEL_ONE                       [RFKTUIHelper pixelOne]

//------------------------------------------------------------
#define DEVICE_SCREEN_WIDTH             rfkt_deviceScreenWidth()       // 物理设备的屏幕尺寸短边，注意，一般UI布局请勿使用！适合于获取设备信息类场景
#define DEVICE_SCREEN_HEIGHT            rfkt_deviceScreenHeight()      // 物理设备的屏幕尺寸长边，注意，一般UI布局请勿使用！适用于获取设备信息类场景
#define APPLICATION_FRAME_WIDTH         rfkt_applicationFrameWidth()   // 注意，返回window.bounds.width，该值会由于屏幕旋转等变化！适用部分UI初始化场景
#define APPLICATION_FRAME_HEIGHT        rfkt_applicationFrameHeight()  // 注意，返回window.bounds.height，该值会由于屏幕旋转等变化！适用部分UI初始化场景
//------------------------------------------------------------

#define RFKT_SCREEN_BOUND_SIZE          ([[UIScreen mainScreen] bounds].size)
#define RFKT_SCREEN_NATIVE_BOUND_SIZE   ([[UIScreen mainScreen] nativeBounds].size)
#define RFKT_SCREEN_SCALE               ([[UIScreen mainScreen] scale])
#define RFKT_SCREEN_NATIVE_SCALE        ([[UIScreen mainScreen] nativeScale])

//------------------------------------------------------------
#define RFKT_HOME_INDICATOR_HEIHT        rfkt_homeIndicatorHeight()
#define RFKT_SAFE_AREA_INSET_TOP         rfkt_safeAreaInsetsTop()      // 安全区域top inset(横竖屏不一样)
#define RFKT_SAFE_AREA_INSET_LEFT        rfkt_safeAreaInsetsLeft()     // 安全区域left inset
#define RFKT_SAFE_AREA_INSET_RIGHT       rfkt_safeAreaInsetsRight()    // 安全区域right inset

#define RFKT_HAS_TOP_NOTCH               rfkt_hasTopNotch()            // 顶部是否存在刘海
#define RFKT_HAS_BOTTOM_SAFEAREA_INSET   rfkt_hasBottomSafeAreaInset() // 底部是否存在安全区域
//-------------------------------------------------------------

FOUNDATION_STATIC_INLINE  UIWindow * _Nullable rfktAppRootWindow() {
    UIWindow *window = nil;
    if ([[UIApplication sharedApplication].delegate respondsToSelector:@selector(window)]) {
        window = [UIApplication sharedApplication].delegate.window;
    }
    if (!window) {
        window = [UIApplication sharedApplication].keyWindow;
    }
    if (!window) {
        [[UIApplication sharedApplication].windows firstObject];
    }
    return window;
}

FOUNDATION_EXTERN int rfkt_deviceScreenWidth(void);
FOUNDATION_EXTERN int rfkt_deviceScreenHeight(void);
FOUNDATION_EXTERN int rfkt_applicationFrameWidth(void);
FOUNDATION_EXTERN int rfkt_applicationFrameHeight(void);
FOUNDATION_EXTERN BOOL rfkt_hasTopNotch(void);
FOUNDATION_EXTERN BOOL rfkt_hasBottomSafeAreaInset(void);
FOUNDATION_EXTERN CGFloat rfkt_safeAreaInsetsTop(void);
FOUNDATION_EXTERN CGFloat rfkt_safeAreaInsetsLeft(void);
FOUNDATION_EXTERN CGFloat rfkt_safeAreaInsetsRight(void);
FOUNDATION_EXTERN CGFloat rfkt_homeIndicatorHeight(void);

#pragma mark - UIColor
/// 日间模式为白色，夜间模式为黑色
#define RFKT_THEME_WHITECOLOR \
[UIColor colorWithDynamicProvider:^UIColor * _Nonnull(UITraitCollection * _Nonnull trainCollection) { \
    if ([trainCollection userInterfaceStyle] == UIUserInterfaceStyleLight) { return [UIColor whiteColor]; } \
    else { return [UIColor blackColor]; } \
}]

/// 日间模式为黑色，夜间模式为白色
#define RFKT_THEME_BLACKCOLOR \
[UIColor colorWithDynamicProvider:^UIColor * _Nonnull(UITraitCollection * _Nonnull trainCollection) { \
    if ([trainCollection userInterfaceStyle] == UIUserInterfaceStyleLight) { return [UIColor blackColor]; } \
    else { return [UIColor whiteColor]; } \
}]

#pragma mark - CGFloat

/**
 *  某些地方可能会将 CGFLOAT_MIN 作为一个数值参与计算（但其实 CGFLOAT_MIN 更应该被视为一个标志位而不是数值），
 *  可能导致一些精度问题，所以提供这个方法快速将 CGFLOAT_MIN 转换为 0
 *  issue: https://github.com/Tencent/QMUI_iOS/issues/203
 */
CG_INLINE CGFloat rfkt_removeFloatMin(CGFloat floatValue) {
    return floatValue == CGFLOAT_MIN ? 0 : floatValue;
}

/**
 *  基于指定的倍数，对传进来的 floatValue 进行像素取整。若指定倍数为0，则表示以当前设备的屏幕倍数为准。
 *  例如传进来 “2.1”，在 2x 倍数下会返回 2.5（0.5pt 对应 1px），在 3x 倍数下会返回 2.333（0.333pt 对应 1px）。
 */
CG_INLINE CGFloat rfkt_flatSpecificScale(CGFloat floatValue, CGFloat scale) {
    floatValue = rfkt_removeFloatMin(floatValue);
    scale = scale ?: RFKT_SCREEN_SCALE;
    CGFloat flattedValue = ceil(floatValue * scale) / scale;
    return flattedValue;
}

/**
 *  基于当前设备的屏幕倍数，对传进来的 floatValue 进行像素取整。
 *  注意如果在 Core Graphic 绘图里使用时，要注意当前画布的倍数是否和设备屏幕倍数一致，若不一致，不可使用 rfkt_flat() 函数，而应该用 rfkt_flatSpecificScale
 */
CG_INLINE CGFloat rfkt_flat(CGFloat floatValue) {
    return rfkt_flatSpecificScale(floatValue, 0);
}

/**
 *  类似rfkt_flat()，只不过 flat 是向上取整，而 rfkt_floorInPixel 是向下取整
 */
CG_INLINE CGFloat rfkt_floorInPixel(CGFloat floatValue) {
    floatValue = rfkt_removeFloatMin(floatValue);
    CGFloat resultValue = floor(floatValue * RFKT_SCREEN_SCALE) / RFKT_SCREEN_SCALE;
    return resultValue;
}

CG_INLINE BOOL rfkt_between(CGFloat minimumValue, CGFloat value, CGFloat maximumValue) {
    return minimumValue < value && value < maximumValue;
}

CG_INLINE BOOL rfkt_betweenOrEqual(CGFloat minimumValue, CGFloat value, CGFloat maximumValue) {
    return minimumValue <= value && value <= maximumValue;
}

/**
 *  调整给定的某个 CGFloat 值的小数点精度，超过精度的部分按四舍五入处理。
 *
 *  例如 rfkt_CGFloatToFixed(0.3333, 2) 会返回 0.33，而 rfkt_CGFloatToFixed(0.6666, 2) 会返回 0.67
 *
 *  @warning 参数类型为 CGFloat，也即意味着不管传进来的是 float 还是 double 最终都会被强制转换成 CGFloat 再做计算
 *  @warning 该方法无法解决浮点数精度运算的问题，如需做浮点数的 == 判断，可用下方的 rfkt_CGFloatEqualToFloat()
 */
CG_INLINE CGFloat rfkt_CGFloatToFixed(CGFloat value, NSUInteger precision) {
    NSString *formatString = [NSString stringWithFormat:@"%%.%@f", @(precision)];
    NSString *toString = [NSString stringWithFormat:formatString, value];
    #if CGFLOAT_IS_DOUBLE
    CGFloat result = [toString doubleValue];
    #else
    CGFloat result = [toString floatValue];
    #endif
    return result;
}

/**
 将给定的两个 CGFloat 进行等值比较，并通过参数 precision 指定要考虑的小数点后的精度，内部会将浮点数转成整型，从而避免浮点数精度导致的 == 判断错误。
 例如 rfkt_CGFloatEqualToFloatWithPrecision(1.000, 0.999, 0) 会返回 YES，但 1.000 == 0.999 会得到 NO。
 */
CG_INLINE BOOL rfkt_CGFloatEqualToFloatWithPrecision(CGFloat value1, CGFloat value2, NSUInteger precision) {
    NSInteger a = ((NSInteger)round(value1) * pow(10, precision));
    NSInteger b = ((NSInteger)round(value2) * pow(10, precision));
    return a == b;
}

/**
 将给定的两个 CGFloat 进行等值比较，不考虑小数点后的数值。
 例如 rfkt_CGFloatEqualToFloat(1.000, 0.999) 会返回 YES，但 1.000 == 0.999 会得到 NO。
 */
CG_INLINE BOOL rfkt_CGFloatEqualToFloat(CGFloat value1, CGFloat value2) {
    return rfkt_CGFloatEqualToFloatWithPrecision(value1, value2, 0);
}

/// 用于居中运算
CG_INLINE CGFloat rfkt_CGFloatGetCenter(CGFloat parent, CGFloat child) {
    return rfkt_flat((parent - child) / 2.0);
}

/// 检测某个数值如果为 NaN 则将其转换为 0，避免布局中出现 crash
CG_INLINE CGFloat rfkt_CGFloatSafeValue(CGFloat value) {
    return isnan(value) ? 0 : value;
}

#pragma mark - CGPoint

/// 两个point相加
CG_INLINE CGPoint rfkt_CGPointUnion(CGPoint point1, CGPoint point2) {
    return CGPointMake(rfkt_flat(point1.x + point2.x), rfkt_flat(point1.y + point2.y));
}

/// 获取rect的center，包括rect本身的x/y偏移
CG_INLINE CGPoint rfkt_CGPointGetCenterWithRect(CGRect rect) {
    return CGPointMake(rfkt_flat(CGRectGetMidX(rect)), rfkt_flat(CGRectGetMidY(rect)));
}

CG_INLINE CGPoint rfkt_CGPointGetCenterWithSize(CGSize size) {
    return CGPointMake(rfkt_flat(size.width / 2.0), rfkt_flat(size.height / 2.0));
}

CG_INLINE CGPoint rfkt_CGPointToFixed(CGPoint point, NSUInteger precision) {
    CGPoint result = CGPointMake(rfkt_CGFloatToFixed(point.x, precision), rfkt_CGFloatToFixed(point.y, precision));
    return result;
}

CG_INLINE CGPoint rfkt_CGPointRemoveFloatMin(CGPoint point) {
    CGPoint result = CGPointMake(rfkt_removeFloatMin(point.x), rfkt_removeFloatMin(point.y));
    return result;
}

#pragma mark - UIEdgeInsets

/// 获取UIEdgeInsets在水平方向上的值
CG_INLINE CGFloat rfkt_UIEdgeInsetsGetHorizontalValue(UIEdgeInsets insets) {
    return insets.left + insets.right;
}

/// 获取UIEdgeInsets在垂直方向上的值
CG_INLINE CGFloat rfkt_UIEdgeInsetsGetVerticalValue(UIEdgeInsets insets) {
    return insets.top + insets.bottom;
}

/// 将两个UIEdgeInsets合并为一个
CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsConcat(UIEdgeInsets insets1, UIEdgeInsets insets2) {
    insets1.top += insets2.top;
    insets1.left += insets2.left;
    insets1.bottom += insets2.bottom;
    insets1.right += insets2.right;
    return insets1;
}

CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsSetTop(UIEdgeInsets insets, CGFloat top) {
    insets.top = rfkt_flat(top);
    return insets;
}

CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsSetLeft(UIEdgeInsets insets, CGFloat left) {
    insets.left = rfkt_flat(left);
    return insets;
}
CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsSetBottom(UIEdgeInsets insets, CGFloat bottom) {
    insets.bottom = rfkt_flat(bottom);
    return insets;
}

CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsSetRight(UIEdgeInsets insets, CGFloat right) {
    insets.right = rfkt_flat(right);
    return insets;
}

CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsToFixed(UIEdgeInsets insets, NSUInteger precision) {
    UIEdgeInsets result = UIEdgeInsetsMake(rfkt_CGFloatToFixed(insets.top, precision), rfkt_CGFloatToFixed(insets.left, precision),
                                           rfkt_CGFloatToFixed(insets.bottom, precision), rfkt_CGFloatToFixed(insets.right, precision));
    return result;
}

CG_INLINE UIEdgeInsets rfkt_UIEdgeInsetsRemoveFloatMin(UIEdgeInsets insets) {
    UIEdgeInsets result = UIEdgeInsetsMake(rfkt_removeFloatMin(insets.top), rfkt_removeFloatMin(insets.left),
                                           rfkt_removeFloatMin(insets.bottom), rfkt_removeFloatMin(insets.right));
    return result;
}

#pragma mark - CGSize

/// 判断一个 CGSize 是否存在 NaN
CG_INLINE BOOL rfkt_CGSizeIsNaN(CGSize size) {
    return isnan(size.width) || isnan(size.height);
}

/// 判断一个 CGSize 是否存在 infinite
CG_INLINE BOOL rfkt_CGSizeIsInf(CGSize size) {
    return isinf(size.width) || isinf(size.height);
}

/// 判断一个 CGSize 是否为空（宽或高为0）
CG_INLINE BOOL rfkt_CGSizeIsEmpty(CGSize size) {
    return size.width <= 0 || size.height <= 0;
}

/// 判断一个 CGSize 是否合法（例如不带无穷大的值、不带非法数字）
CG_INLINE BOOL rfkt_CGSizeIsValidated(CGSize size) {
    return !rfkt_CGSizeIsEmpty(size) && !rfkt_CGSizeIsInf(size) && !rfkt_CGSizeIsNaN(size);
}

/// 将一个 CGSize 像素对齐
CG_INLINE CGSize rfkt_CGSizeFlatted(CGSize size) {
    return CGSizeMake(rfkt_flat(size.width), rfkt_flat(size.height));
}

/// 将一个 CGSize 以 pt 为单位向上取整
CG_INLINE CGSize rfkt_CGSizeCeil(CGSize size) {
    return CGSizeMake(ceil(size.width), ceil(size.height));
}

/// 将一个 CGSize 以 pt 为单位向下取整
CG_INLINE CGSize rfkt_CGSizeFloor(CGSize size) {
    return CGSizeMake(floor(size.width), floor(size.height));
}

CG_INLINE CGSize rfkt_CGSizeToFixed(CGSize size, NSUInteger precision) {
    CGSize result = CGSizeMake(rfkt_CGFloatToFixed(size.width, precision), rfkt_CGFloatToFixed(size.height, precision));
    return result;
}

CG_INLINE CGSize rfkt_CGSizeRemoveFloatMin(CGSize size) {
    CGSize result = CGSizeMake(rfkt_removeFloatMin(size.width), rfkt_removeFloatMin(size.height));
    return result;
}


#pragma mark - CGRect

CG_INLINE CGRect rfkt_CGRectSetX(CGRect rect, CGFloat x) {
    rect.origin.x = (x);
    return rect;
}

CG_INLINE CGRect rfkt_CGRectSetY(CGRect rect, CGFloat y) {
    rect.origin.y = (y);
    return rect;
}

CG_INLINE CGRect rfkt_CGRectSetXY(CGRect rect, CGFloat x, CGFloat y) {
    rect.origin.x = (x);
    rect.origin.y = (y);
    return rect;
}

CG_INLINE CGRect rfkt_CGRectSetWidth(CGRect rect, CGFloat width) {
    if (width < 0) {
        return rect;
    }
    rect.size.width = (width);
    return rect;
}

CG_INLINE CGRect rfkt_CGRectSetHeight(CGRect rect, CGFloat height) {
    if (height < 0) {
        return rect;
    }
    rect.size.height = (height);
    return rect;
}

CG_INLINE CGRect rfkt_CGRectSetSize(CGRect rect, CGSize size) {
    rect.size = (size);
    return rect;
}

/// 判断一个 CGRect 是否存在 NaN
CG_INLINE BOOL rfkt_CGRectIsNaN(CGRect rect) {
    return isnan(rect.origin.x) || isnan(rect.origin.y) || isnan(rect.size.width) || isnan(rect.size.height);
}

/// 系统提供的 CGRectIsInfinite 接口只能判断 CGRectInfinite 的情况，而该接口可以用于判断 INFINITY 的值
CG_INLINE BOOL rfkt_CGRectIsInf(CGRect rect) {
    return isinf(rect.origin.x) || isinf(rect.origin.y) || isinf(rect.size.width) || isinf(rect.size.height);
}

/// 判断一个 CGRect 是否合法（例如不带无穷大的值、不带非法数字）
CG_INLINE BOOL rfkt_CGRectIsValidated(CGRect rect) {
    return !CGRectIsNull(rect) && !CGRectIsInfinite(rect) && !rfkt_CGRectIsNaN(rect) && !rfkt_CGRectIsInf(rect);
}

/// 检测某个 CGRect 如果存在数值为 NaN 的则将其转换为 0，避免布局中出现 crash
CG_INLINE CGRect rfkt_CGRectSafeValue(CGRect rect) {
    return CGRectMake(rfkt_CGFloatSafeValue(CGRectGetMinX(rect)), rfkt_CGFloatSafeValue(CGRectGetMinY(rect)),
                      rfkt_CGFloatSafeValue(CGRectGetWidth(rect)), rfkt_CGFloatSafeValue(CGRectGetHeight(rect)));
}

/// 创建一个像素对齐的CGRect
CG_INLINE CGRect rfkt_CGRectFlatMake(CGFloat x, CGFloat y, CGFloat width, CGFloat height) {
    return CGRectMake(rfkt_flat(x), rfkt_flat(y), rfkt_flat(width), rfkt_flat(height));
}

/// 对CGRect的x/y、width/height都调用一次flat，以保证像素对齐
CG_INLINE CGRect rfkt_CGRectFlatted(CGRect rect) {
    return CGRectMake(rfkt_flat(rect.origin.x), rfkt_flat(rect.origin.y), rfkt_flat(rect.size.width), rfkt_flat(rect.size.height));
}

/// 计算目标点 targetPoint 围绕坐标点 coordinatePoint 通过 transform 之后此点的坐标
CG_INLINE CGPoint rfkt_CGPointApplyAffineTransformWithCoordinatePoint(CGPoint coordinatePoint, CGPoint targetPoint, CGAffineTransform t) {
    CGPoint p;
    p.x = (targetPoint.x - coordinatePoint.x) * t.a + (targetPoint.y - coordinatePoint.y) * t.c + coordinatePoint.x;
    p.y = (targetPoint.x - coordinatePoint.x) * t.b + (targetPoint.y - coordinatePoint.y) * t.d + coordinatePoint.y;
    p.x += t.tx;
    p.y += t.ty;
    return p;
}

/// 系统的 CGRectApplyAffineTransform 只会按照 anchorPoint 为 (0, 0) 的方式去计算，但通常情况下我们面对的是 UIView/CALayer，它们默认的 anchorPoint 为 (.5, .5)，所以增加这个函数，在计算 transform 时可以考虑上 anchorPoint 的影响
CG_INLINE CGRect rfkt_CGRectApplyAffineTransformWithAnchorPoint(CGRect rect, CGAffineTransform t, CGPoint anchorPoint) {
    CGFloat width = CGRectGetWidth(rect);
    CGFloat height = CGRectGetHeight(rect);
    CGPoint oPoint = CGPointMake(rect.origin.x + width * anchorPoint.x, rect.origin.y + height * anchorPoint.y);
    CGPoint top_left = rfkt_CGPointApplyAffineTransformWithCoordinatePoint(oPoint, CGPointMake(rect.origin.x, rect.origin.y), t);
    CGPoint bottom_left = rfkt_CGPointApplyAffineTransformWithCoordinatePoint(oPoint, CGPointMake(rect.origin.x, rect.origin.y + height), t);
    CGPoint top_right = rfkt_CGPointApplyAffineTransformWithCoordinatePoint(oPoint, CGPointMake(rect.origin.x + width, rect.origin.y), t);
    CGPoint bottom_right = rfkt_CGPointApplyAffineTransformWithCoordinatePoint(oPoint, CGPointMake(rect.origin.x + width, rect.origin.y + height), t);
    CGFloat minX = MIN(MIN(MIN(top_left.x, bottom_left.x), top_right.x), bottom_right.x);
    CGFloat maxX = MAX(MAX(MAX(top_left.x, bottom_left.x), top_right.x), bottom_right.x);
    CGFloat minY = MIN(MIN(MIN(top_left.y, bottom_left.y), top_right.y), bottom_right.y);
    CGFloat maxY = MAX(MAX(MAX(top_left.y, bottom_left.y), top_right.y), bottom_right.y);
    CGFloat newWidth = maxX - minX;
    CGFloat newHeight = maxY - minY;
    CGRect result = CGRectMake(minX, minY, newWidth, newHeight);
    return result;
}

/// 为一个CGRect叠加scale计算
CG_INLINE CGRect rfkt_CGRectApplyScale(CGRect rect, CGFloat scale) {
    return rfkt_CGRectFlatted(CGRectMake(CGRectGetMinX(rect) * scale, CGRectGetMinY(rect) * scale,
                                    CGRectGetWidth(rect) * scale, CGRectGetHeight(rect) * scale));
}


/// 计算view的水平居中，传入父view和子view的frame，返回子view在水平居中时的x值
CG_INLINE CGFloat rfkt_CGRectGetMinXHorizontallyCenterInParentRect(CGRect parentRect, CGRect childRect) {
    return rfkt_flat((CGRectGetWidth(parentRect) - CGRectGetWidth(childRect)) / 2.0);
}

/// 计算view的垂直居中，传入父view和子view的frame，返回子view在垂直居中时的y值
CG_INLINE CGFloat rfkt_CGRectGetMinYVerticallyCenterInParentRect(CGRect parentRect, CGRect childRect) {
    return rfkt_flat((CGRectGetHeight(parentRect) - CGRectGetHeight(childRect)) / 2.0);
}

/// 返回值：同一个坐标系内，想要layoutingRect和已布局完成的referenceRect保持垂直居中时，layoutingRect的originY
CG_INLINE CGFloat rfkt_CGRectGetMinYVerticallyCenter(CGRect referenceRect, CGRect layoutingRect) {
    return CGRectGetMinY(referenceRect) + rfkt_CGRectGetMinYVerticallyCenterInParentRect(referenceRect, layoutingRect);
}

/// 返回值：同一个坐标系内，想要layoutingRect和已布局完成的referenceRect保持水平居中时，layoutingRect的originX
CG_INLINE CGFloat rfkt_CGRectGetMinXHorizontallyCenter(CGRect referenceRect, CGRect layoutingRect) {
    return CGRectGetMinX(referenceRect) + rfkt_CGRectGetMinXHorizontallyCenterInParentRect(referenceRect, layoutingRect);
}


NS_ASSUME_NONNULL_END

#endif /* RFKTUIHelper_h */
