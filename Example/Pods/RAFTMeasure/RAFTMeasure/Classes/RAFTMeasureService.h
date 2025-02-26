//
//  RAFTMeasureService.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureDefines.h"
@class RAFTMeasureComInfo;
@class RAFTMeasureAppInfo;

// RAFTMeasure单例简写
#define RAFTMeasure [RAFTMeasureService sharedInstance]

NS_ASSUME_NONNULL_BEGIN

/**
    RAFTMeasure服务单例
 */
@interface RAFTMeasureService : NSObject

+ (instancetype)sharedInstance;

#pragma mark - Crash监控
// 开启Crash监控
//  @param comInfo 组件信息
- (void)enableCrashMonitor:(RAFTMeasureComInfo *)comInfo;

#pragma mark - 成功率上报
// SLI 指标:成功率, 计算公式 成功次数/上报总次数
//  默认抽样率 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE}
//  @param comInfo 组件信息
//  @param key 上报项
//  @param success 成功状态
- (void)reportSuccess:(RAFTMeasureComInfo *)comInfo
                  key:(NSString *)key
              success:(BOOL)success;

// SLI 指标:成功率, 计算公式 成功次数/上报总次数
//  如果业务传入抽样率大于默认抽样率 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE},则抽样率为samplingRate*RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE
//  @param comInfo 组件信息
//  @param key 上报项
//  @param success 成功状态
//  @param samplingRate 抽样率，范围[0 - 100]
- (void)reportSuccess:(RAFTMeasureComInfo *)comInfo
                  key:(NSString *)key
              success:(BOOL)success
         samplingRate:(int)samplingRate;

#pragma mark - 平均值上报
// SLI 指标:耗时统计/覆盖安装包大小/耗时, 计算公式 cost总和/上报总次数
//  默认抽样率 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE}
//  @param comInfo 组件信息
//  @param key 上报项
//  @param value 上报值
- (void)reportAvg:(RAFTMeasureComInfo *)comInfo
              key:(NSString *)key
            value:(long)value;

// SLI 指标:耗时统计/覆盖安装包大小/耗时, 计算公式 cost总和/上报总次数
//  如果业务传入抽样率大于默认抽样率 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE},则抽样率为samplingRate*RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE
//  @param comInfo 组件信息
//  @param key 上报项
//  @param value 上报值
//  @param samplingRate 抽样率，范围[0 - 100]
- (void)reportAvg:(RAFTMeasureComInfo *)comInfo
              key:(NSString *)key
            value:(long)value
     samplingRate:(int)samplingRate;

#pragma mark - 分布值上报
// SLI 指标:分布统计,统计某个SLI指标的值分布, 计算公式:单个分布计算 = 分布值次数/ 上报总次数
//  默认抽样率 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE}
//  @param comInfo 组件信息
//  @param key 上报项
//  @param value 上报值
- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                     value:(long)value;

- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                     sValue:(NSString *)sValue;

// SLI 指标:分布统计,统计某个SLI指标的值分布, 计算公式:单个分布计算 = 分布值次数/ 上报总次数
//  如果业务传入抽样率大于默认抽样率 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE},则抽样率为samplingRate*RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE
//  @param comInfo 组件信息
//  @param key 上报项
//  @param value 上报值
//  @param samplingRate 抽样率，范围[0 - 100]
- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                     value:(long)value
              samplingRate:(int)samplingRate;

- (void)reportDistribution:(RAFTMeasureComInfo *)comInfo
                       key:(NSString *)key
                    sValue:(NSString *)sValue
              samplingRate:(int)samplingRate;

#pragma mark - 宿主APP专用
// 获取从宿主APP中拿到的AppInfo信息
- (RAFTMeasureAppInfo *)appInfo;

// 宿主APP设置日志输出回调
- (void)setLogDelegate:(id<RAFTMeasureLogProtocol>)logDelegate;

// 宿主APP设置是否开启Debug模式
//  说明：在Debug模式下，出现Error日志会同时触发NSAssert。（默认为NO不开启）
- (void)setIsDebug:(BOOL)isDebug;

@end

NS_ASSUME_NONNULL_END
