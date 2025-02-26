//
//  RAFTMeasureComInfo.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureReportDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
    组件信息
 */
@interface RAFTMeasureComInfo : NSObject <RAFTMeasureReportParamProtocol>

// 组件名
@property (nonatomic, copy) NSString *comName;

// 组件版本号
@property (nonatomic, copy) NSString *comVer;

// 初始化方法
// @param comName 组件名
// @param comVer 组件版本号
- (instancetype)initWithComName:(NSString *)comName
                         comVer:(NSString *)comVer;

// 判断数据是否有效
- (BOOL)isDataValid;

// 组件唯一key：组件名+版本号
- (NSString *)comUniKey;

// 组件唯一key+上报key：组件名+版本号+上报Key
- (NSString *)comUniKeyWithReportKey:(NSString *)reportKey;

// 获取上报参数
- (NSDictionary *)reportParams;

@end

NS_ASSUME_NONNULL_END
