//
//  RAFTMeasureSLIReportItem.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureDefines.h"
#import "RAFTMeasureReportDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
    RAFTMeasure上报SLI数据
 */
@interface RAFTMeasureSLIReportItem : NSObject <RAFTMeasureReportParamProtocol>

// 组件信息
@property (nonatomic, strong) id<RAFTMeasureReportParamProtocol> comInfo;

// SLI名称
@property (nonatomic, copy) NSString *sliName;

// SLI值
@property (nonatomic, copy) NSString *sliValue;

// SLI类型
@property (nonatomic, copy) RAFTMEASURE_SLI_TYPE sliType;

// APP信息
@property (nonatomic, strong) id<RAFTMeasureReportParamProtocol> appInfo;

// 初始化方法
// @param comInfo 组件信息
// @param sliName SLI名称
// @param sliValue SLI值
// @param sliType SLI类型
// @param appInfo APP信息
- (instancetype)initWithComInfo:(id<RAFTMeasureReportParamProtocol>)comInfo
                        sliName:(NSString *)sliName
                       sliValue:(NSString *)sliValue
                        sliType:(RAFTMEASURE_SLI_TYPE)sliType
                        appInfo:(id<RAFTMeasureReportParamProtocol>)appInfo;

// 获取上报参数
- (NSDictionary *)reportParams;

@end

NS_ASSUME_NONNULL_END
