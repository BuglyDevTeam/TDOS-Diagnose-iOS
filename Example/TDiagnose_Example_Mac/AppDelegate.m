//
//  AppDelegate.m
//  TDiagnoseExampleMac
//
//  Created by raycgwang on 13/3/2023.
//  Copyright (c) 2021 raycgwang. All rights reserved.
//

#import "AppDelegate.h"
@import TDOS_Diagnose;

// appid & appKey, 诊断平台申请
#define TDOSLOG_APPID   @"cd1f7d6505" // mac-demo正式环境
#define TDOSLOG_APPKEY  @"1a65b51e-c0c3-4564-bdd8-727dbd8617b7" // mac-demo正式环境
//#define TDOSLOG_APPID   @"83f746f766" // mac-demo测试环境
//#define TDOSLOG_APPKEY  @"a14404df-ec48-4d4c-b475-597e6c0da06e" // mac-demo测试环境

// 定义加密公钥（联系TDOS诊断平台，分配密钥对，私钥后台保管）
// 传空或nil或格式不正确的公钥，SDK都不加密
#define TDOSLOG_PUBKEY @""

@interface AppDelegate () <TDLogSDKDataSource>


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    // 打日志模块初始化 begin--------------------------
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig]; //可直接使用默认配置
    // 或自定义一些配置
    TDOSLoggerConfig *customConfig = [TDOSLoggerConfig configWithLogPath:loggerConfig.logPath
                                                               logPrefix:@"TDiagnoseLog"
                                                            defaultLevel:RAFTLogLevelAll
                                                            andPublicKey:TDOSLOG_PUBKEY];
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:customConfig];
    [logger setConsoleLogEnabled:YES];// 开启控制台日志（可选，建议仅在调试时开启）
    [logger setMaxLogAliveTime:(7 * 24 * 60 * 60)]; // 设置本地日志最大保留时间（可选，默认保存10天）
    
    // 日志模块解耦层，可选，可替换
    TDOSLoggerProxy *loggerProxy = [TDOSLoggerProxy defaultProxy];
    [loggerProxy setLogger:logger];
    // 打日志模块初始化 end--------------------------
    
    
    // 捞日志模块初始化 begin--------------------------
    // 给捞日志模块传入一些必要依赖，目前需要
    // 1、打日志模块，用于输出捞日志模块内部日志
    // 2、KV存储模块，用于捞日志模块内部持久化任务信息，实现重试等逻辑
    // 3、文件打包模块，用于日志文件打包
    TDIAGDepends *depends = [TDIAGDepends dependsWithLogImp:loggerProxy
                                               kvFactoryImp:[TDMMKVFactoryImpl sharedInstance]
                                           andFilePackerImp:[TDLogFilePackerImp new]];
    
    // appid & appKey, 平台生成
    NSString *appID = TDOSLOG_APPID;
    NSString *appKey = TDOSLOG_APPKEY;
    
    // 生成捞日志模块配置实例，并初始化
    TDLogSDKConfig *config = [TDLogSDKConfig configWithAppId:appID
                                                      appKey:appKey
                                                  dataSource:self
                                                     depends:depends];
    [[TDLogSDK sharedInstance] startWithConfig:config];
    // 捞日志模块初始化 end--------------------------
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


- (nonnull NSString *)guidForTDLog { 
    return @"123456";
}

@end
