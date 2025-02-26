//
//  RAFTMeasureDefines.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

/** SLI类型枚举值 **/
typedef NSString *RAFTMEASURE_SLI_TYPE NS_STRING_ENUM;
// 成功率上报
FOUNDATION_EXPORT RAFTMEASURE_SLI_TYPE const RAFTMEASURE_SLI_TYPE_SUCCESS;
// 平均值上报
FOUNDATION_EXPORT RAFTMEASURE_SLI_TYPE const RAFTMEASURE_SLI_TYPE_AVG;
// 分布值上报
FOUNDATION_EXPORT RAFTMEASURE_SLI_TYPE const RAFTMEASURE_SLI_TYPE_DISTRIBUTION;
// 启动上报
FOUNDATION_EXPORT RAFTMEASURE_SLI_TYPE const RAFTMEASURE_SLI_TYPE_STARTUP;

/** 日志输出协议 **/
@protocol RAFTMeasureLogProtocol <NSObject>

// 输出debug级别日志
- (void)raftMeasureDebugLog:(NSString *)msg;
// 输出info级别日志
- (void)raftMeasureInfoLog:(NSString *)msg;
// 输出warn级别日志
- (void)raftMeasureWarnLog:(NSString *)msg;
// 输出error级别日志
- (void)raftMeasureErrorLog:(NSString *)msg;

@end

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RAFTMeasureDefines : NSObject

@end

NS_ASSUME_NONNULL_END
