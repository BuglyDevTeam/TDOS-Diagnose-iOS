//
//  RAFTMeasureUtils.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureUtils.h"

@implementation RAFTMeasureUtils

+ (NSString *)safeString:(NSString *)str {
    return str.length > 0 ? str : @"";
}

+ (NSString *)successToString:(BOOL)success {
    return success ? @"1" : @"0";
}

+ (double)randomNumber0_1 {
    double val = ((double)arc4random() / UINT32_MAX);
    return val;
}

+ (NSDate *)currDate {
    NSDate *currDate = [NSDate dateWithTimeIntervalSince1970:[[NSDate date] timeIntervalSince1970]];
    return currDate;
}

+ (BOOL)isSameDay:(NSDate *)aDate bDate:(NSDate *)bDate {
    if (!aDate || !bDate) {
        return NO;
    }
    NSCalendar *currCalendar = [NSCalendar autoupdatingCurrentCalendar];
    unsigned unitFlags = (NSCalendarUnitYear | NSCalendarUnitMonth | NSCalendarUnitDay | NSCalendarUnitWeekOfYear | NSCalendarUnitHour | NSCalendarUnitMinute | NSCalendarUnitSecond | NSCalendarUnitWeekday | NSCalendarUnitWeekdayOrdinal);
    NSDateComponents *aDC1 = [currCalendar components:unitFlags fromDate:aDate];
    NSDateComponents *aDC2 = [currCalendar components:unitFlags fromDate:bDate];
    return ((aDC1.year == aDC2.year) &&
            (aDC1.month == aDC2.month) &&
            (aDC1.day == aDC2.day));
}

@end
