//
//  RAFTMeasureReportSampling.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureReportDefines.h"
@class RAFTMeasureComInfo;

NS_ASSUME_NONNULL_BEGIN

/**
    RAFTMeasure上报抽样逻辑
 */
@interface RAFTMeasureReportSampling : NSObject

#pragma mark - SLI上报抽样逻辑
// 获取SLI上报的抽样结果
//  @param comInfo 组件信息
//  @param key 上报项
//  @param samplingRate 抽样率，范围[0 - 100]
- (RAFTMEASURE_SAMPLING_RESULT)sliSamplingResult:(RAFTMeasureComInfo *)comInfo
                                             key:(NSString *)key
                                    samplingRate:(int)samplingRate;

#pragma mark - StartUp上报抽样逻辑
// 获取StartUp上报的抽样结果
//  @param comInfo 组件信息
//  @param samplingRate 抽样率，范围[0 - 100]
- (RAFTMEASURE_SAMPLING_RESULT)startUpSamplingResult:(RAFTMeasureComInfo *)comInfo
                                        samplingRate:(int)samplingRate;

@end

NS_ASSUME_NONNULL_END
