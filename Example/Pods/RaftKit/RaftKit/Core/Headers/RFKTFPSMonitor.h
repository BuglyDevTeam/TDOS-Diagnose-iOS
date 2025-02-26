//
//  RFKTFPSMonitor.h
//  QAPM
//
//  Created by michaelbi on 2020/9/19.
//  Copyright © 2020 cass. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// FPS记录频率
typedef NS_ENUM(NSUInteger, RFKTFPSMonitorRefreshFrequency) {
    RFKTFPSIndicatorRefreshFrequencyNormal = 1,  // 1s记录一次
    RFKTFPSIndicatorRefreshFrequencyMedium = 3,  // 1/3s记录一次
    RFKTFPSIndicatorRefreshFrequencyHigh = 10    // 1/10s记录一次
};

/// FPS监控统计
@interface RFKTFPSMonitor : NSObject

/// FPS监控频率
@property (nonatomic, assign) RFKTFPSMonitorRefreshFrequency frequency;

/*
 描述:开始FPS监控
*/
- (void)startWithFrequency:(RFKTFPSMonitorRefreshFrequency)frequency;

/*
 描述:关闭FPS监控
*/
- (void)stop;

/*
 描述:获取最近一秒的FPS值
*/
- (int)getLastFPS;

/*
 描述:获取最近一分钟的FPS值
*/
- (NSArray<NSNumber *> *)getFPSLast1Min;

@end

NS_ASSUME_NONNULL_END
