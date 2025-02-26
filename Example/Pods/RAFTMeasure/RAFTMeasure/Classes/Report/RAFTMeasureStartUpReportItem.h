//
//  RAFTMeasureStartUpReportItem.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureReportDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
    RAFTMeasure上报启动数据
 */
@interface RAFTMeasureStartUpReportItem : NSObject <RAFTMeasureReportParamProtocol>

// 组件信息
@property (nonatomic, strong) id<RAFTMeasureReportParamProtocol> comInfo;

// 抽样率
@property (nonatomic, copy) NSString *samplingRate;

// APP信息
@property (nonatomic, strong) id<RAFTMeasureReportParamProtocol> appInfo;

// 初始化方法
// @param comInfo 组件信息
// @param samplingRate 抽样率
// @param appInfo APP信息
- (instancetype)initWithComInfo:(id<RAFTMeasureReportParamProtocol>)comInfo
                   samplingRate:(NSString *)samplingRate
                        appInfo:(id<RAFTMeasureReportParamProtocol>)appInfo;

// 获取上报参数
- (NSDictionary *)reportParams;

@end

NS_ASSUME_NONNULL_END
