//
//  RAFTMeasureUtils.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RAFTMeasureUtils : NSObject

// 如果字符串为空，则返回空字符串@""。
+ (NSString *)safeString:(NSString *)str;

// BOOL类型的success转为字符串类型。
//  YES = @"1
//  NO = @"0"
+ (NSString *)successToString:(BOOL)success;

// 随机数：产生一个[0，1)之间的随机数,大于等于0小于1的随机小数。
+ (double)randomNumber0_1;

// 获取当前日期
+ (NSDate *)currDate;

// 判断两个日期是否是同一天
+ (BOOL)isSameDay:(NSDate *)aDate bDate:(NSDate *)bDate;

@end

NS_ASSUME_NONNULL_END
