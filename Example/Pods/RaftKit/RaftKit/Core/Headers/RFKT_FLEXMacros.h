//
//  FLEXMacros.h
//  FLEX
//
//  Created by Tanner on 3/12/20.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#ifndef RFKT_FLEXMacros_h
#define RFKT_FLEXMacros_h

#define rfkt_flex_keywordify class NSObject;
#define ctor rfkt_flex_keywordify __attribute__((constructor)) void __rfkt_flex_ctor_##__LINE__()
#define dtor rfkt_flex_keywordify __attribute__((destructor)) void __rfkt_flex_dtor_##__LINE__()

#define weakify(var) __weak __typeof(var) __weak__##var = var;

#define strongify(var) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wshadow\"") \
__strong typeof(var) var = __weak__##var; \
_Pragma("clang diagnostic pop")

// A macro to check if we are running in a test environment
#define RFKT_FLEX_IS_TESTING() (NSClassFromString(@"XCTest") != nil)

/// Whether we want the majority of constructors to run upon load or not.
extern BOOL RFKT_FLEXConstructorsShouldRun(void);

/// A macro to return from the current procedure if we don't want to run constructors
#define RFKT_FLEX_EXIT_IF_NO_CTORS() if (!RFKT_FLEXConstructorsShouldRun()) return;

/// Rounds down to the nearest "point" coordinate
NS_INLINE CGFloat RFKT_FLEXFloor(CGFloat x) {
    return floor(UIScreen.mainScreen.scale * (x)) / UIScreen.mainScreen.scale;
}

/// Returns the given number of points in pixels
NS_INLINE CGFloat RFKT_FLEXPointsToPixels(CGFloat points) {
    return points / UIScreen.mainScreen.scale;
}

/// Creates a CGRect with all members rounded down to the nearest "point" coordinate
NS_INLINE CGRect RFKT_FLEXRectMake(CGFloat x, CGFloat y, CGFloat width, CGFloat height) {
    return CGRectMake(RFKT_FLEXFloor(x), RFKT_FLEXFloor(y), RFKT_FLEXFloor(width), RFKT_FLEXFloor(height));
}

/// Adjusts the origin of an existing rect
NS_INLINE CGRect RFKT_FLEXRectSetOrigin(CGRect r, CGPoint origin) {
    r.origin = origin; return r;
}

/// Adjusts the size of an existing rect
NS_INLINE CGRect RFKT_FLEXRectSetSize(CGRect r, CGSize size) {
    r.size = size; return r;
}

/// Adjusts the origin.x of an existing rect
NS_INLINE CGRect RFKT_FLEXRectSetX(CGRect r, CGFloat x) {
    r.origin.x = x; return r;
}

/// Adjusts the origin.y of an existing rect
NS_INLINE CGRect RFKT_FLEXRectSetY(CGRect r, CGFloat y) {
    r.origin.y = y ; return r;
}

/// Adjusts the size.width of an existing rect
NS_INLINE CGRect RFKT_FLEXRectSetWidth(CGRect r, CGFloat width) {
    r.size.width = width; return r;
}

/// Adjusts the size.height of an existing rect
NS_INLINE CGRect RFKT_FLEXRectSetHeight(CGRect r, CGFloat height) {
    r.size.height = height; return r;
}

#ifdef __IPHONE_13_0
#define RFKT_FLEX_AT_LEAST_IOS13_SDK (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_13_0)
#else
#define RFKT_FLEX_AT_LEAST_IOS13_SDK NO
#endif

#define RFKT_FLEXPluralString(count, plural, singular) [NSString \
    stringWithFormat:@"%@ %@", @(count), (count == 1 ? singular : plural) \
]

#define RFKT_FLEXPluralFormatString(count, pluralFormat, singularFormat) [NSString \
    stringWithFormat:(count == 1 ? singularFormat : pluralFormat), @(count)  \
]

#define rfkt_flex_dispatch_after(nSeconds, onQueue, block) \
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, \
    (int64_t)(nSeconds * NSEC_PER_SEC)), onQueue, block)

#endif /* RFKT_FLEXMacros_h */
