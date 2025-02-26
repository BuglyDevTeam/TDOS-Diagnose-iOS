//
//  RFKTResourceCommon.h
//  RMonitor
//
//  Created by 张鹏 on 9/1/16.
//  Copyright © 2016 com.tencent. All rights reserved.
//

#ifndef RFKT_RESOURCE_COMMON_H_
#define RFKT_RESOURCE_COMMON_H_

/// 资源监控类型
typedef NS_OPTIONS(NSUInteger, RFKTResourceMonitorType) {
    RFKTResourceMonitorTypeCPU = 1 << 0,                 // CPU
    RFKTResourceMonitorTypeFPS = 1 << 1,                 // FPS
    RFKTResourceMonitorTypeMemory = 1 << 2,              // 内存
    RFKTResourceMonitorTypeIOSoc = 1 << 3,               // I/O, Socket
    RFKTResourceMonitorTypeUI = 1 << 4,                  // UI
    RFKTResourceMonitorTypeScreenBrightness = 1 << 5,    // 屏幕亮度
    //RFKTResourceMonitorTypeLocation = 1 << 6,   // 定位, not in-use
    //RFKTResourceMonitorTypeBattery = 1 << 7,    // 电池, not in-use
};

/// Socket监控网络状态
typedef NS_ENUM(NSUInteger, RFKTSocketType) {
    RFKTSocketTypeUnknown = 0,
    RFKTSocketTypeWWAN,
    RFKTSocketTypeWifi,
};

#define RFKT_RES_CPU @"RFKT_RES_CPU"
#define RFKT_RES_MEM @"RFKT_RES_MEM"
#define RFKT_RES_IO @"RFKT_RES_IO"
#define RFKT_RES_IO_DETAIL @"RFKT_RES_IO_DETAIL"
#define RFKT_RES_FPS @"RFKT_RES_FPS"
#define RFKT_RES_SOC @"RFKT_RES_SOC"
#define RFKT_RES_DRAW @"RFKT_RES_DRAW"
#define RFKT_RES_FPS @"RFKT_RES_FPS"
#define RFKT_RES_LOCATING @"RFKT_RES_LOCATING"
#define RFKT_RES_SCREEN_BRI @"RFKT_RES_SCREEN_BRI"


/// I/O读写记录
@interface RFKTIORecord : NSObject <NSCopying>

/// fd打开次数
@property (nonatomic, assign) unsigned int opened;

/// fd关闭次数
@property (nonatomic, assign) unsigned int closed;

/// fd读byte数
@property (nonatomic, assign) unsigned long read;

/// fd写byte数
@property (nonatomic, assign) unsigned long writed;

/// fd读次数
@property (nonatomic, assign) unsigned long readCount;

/// fd写次数
@property (nonatomic, assign) unsigned long writeCount;

/// fd打开耗时
@property (nonatomic, assign) double openCost;

/// fd关闭耗时
@property (nonatomic, assign) double closeCost;

/// fd读速度
@property (nonatomic, assign) double readSpeed;

/// fd写速度
@property (nonatomic, assign) double writeSpeed;

@end

/// Socket I/O读写记录
@interface RFKTSocketRecord : RFKTIORecord

/// 连接次数
@property (nonatomic, assign) unsigned int connect;

/// 重连次数
@property (nonatomic, assign) unsigned int reconnect;

/// 网络连接类型（WIFI，蜂窝网络）
@property (nonatomic, assign) unsigned char type;

/// 网络是否不佳
@property (nonatomic, assign) bool badNet;
@end

/// 内存记录
@interface RFKTMemoryRecord : NSObject <NSCopying>

/// 可用内存
@property (nonatomic, assign) uint64_t free;

/// App resident内存（包含footprint + 系统库clean内存），单位byte
@property (nonatomic, assign) uint64_t resident;

/// App footprint内存（dirty memory），单位byte
@property (nonatomic, assign) uint64_t footprint;

/// 是否收到内存告警
@property (nonatomic, assign) BOOL warning;

@end

/// CPU使用率记录
@interface RFKTCPURecord : NSObject <NSCopying>

/// CPU使用率
@property (nonatomic, assign) double usage;

/// 线程数
@property (nonatomic, assign) int threadCount;

@end

/// 线程创建记录
@interface RFKTThreadCreateItem : NSObject <NSCopying>

/// 线程创建时的堆栈
@property (nonatomic, retain) NSArray *stack;

/// 创建线程个数
@property (nonatomic, assign) unsigned int count;

/// 线程数和堆栈打包字典
- (NSDictionary *)dictionary;

@end

/// 线程创建记录容器
@interface RFKTThreadCreateRecord : NSObject <NSCopying>

/// 新创建线程个数
@property (nonatomic, assign) int newThreadCount;

/// 记录容器
@property (nonatomic, retain) NSArray *items;

/// 打包数据字典
- (NSDictionary *)dictionary;

@end

#endif  // RFKT_RESOURCE_COMMON_H_
