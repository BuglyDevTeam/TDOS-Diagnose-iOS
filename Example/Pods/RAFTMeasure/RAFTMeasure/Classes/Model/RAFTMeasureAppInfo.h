//
//  RAFTMeasureAppInfo.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureReportDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
    APP信息
 */
@interface RAFTMeasureAppInfo : NSObject <RAFTMeasureReportParamProtocol>

// APP BundleId
@property (nonatomic, copy) NSString *appId;

// APP名称
@property (nonatomic, copy) NSString *appName;

// APP版本
@property (nonatomic, copy) NSString *appVer;

// APP编译模式
@property (nonatomic, assign) BOOL appDebug;

// 初始化方法
// @param appId APP BundleId
// @param appName APP名称
// @param appVer APP版本
// @param appDebug APP编译模式
- (instancetype)initWithAppId:(NSString *)appId
                      appName:(NSString *)appName
                       appVer:(NSString *)appVer
                     appDebug:(BOOL)appDebug;

// 判断数据是否有效
- (BOOL)isDataValid;

// 获取上报参数
- (NSDictionary *)reportParams;

@end

NS_ASSUME_NONNULL_END
