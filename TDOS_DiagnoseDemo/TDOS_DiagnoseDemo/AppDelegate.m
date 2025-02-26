//
//  AppDelegate.m
//  TDOS_DiagnoseDemo
//
//  Created by Hongbo Cui on 2025/2/25.
//

#import "AppDelegate.h"

@import TDOS_Diagnose;
//#import <TDOS_Diagnose/TDOS_Diagnose.h>
//#import <TDOS_Diagnose/TDOSLoggerProxy.h>
//#import <TDOS_Diagnose/TDOSLogger.h>

#define TDOSLOG_APPID   @"a2031e998b"
#define TDOSLOG_APPKEY  @"5f58a9cf-0acc-4c0d-a020-fc8f0bacb3cc"
#define TDOSLOG_HOST @"pro.bugly.qq.com"

// 定义加密公钥（联系TDOS诊断平台，分配密钥对，私钥后台保管）
// 传空或nil或格式不正确的公钥，SDK都不加密
#define TDOSLOG_PUBKEY @""

@interface AppDelegate ()<TDLogSDKDataSource>

@property (nonatomic, strong) NSMutableArray<id<TDLoggingIMPProtocol>> *subLoggers;

@end

@implementation AppDelegate

+ (void)load {
    // 测试pre-main阶段初始化日志
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig]; //可直接使用默认配置
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:loggerConfig];
    [logger log:RAFTLogLevelError tag:@"1" file:__FILE__ func:__func__ line:__LINE__ msg:@"0.6.2版本后Logger支持在+Load"];
    [logger log:RAFTLogLevelError tag:@"2" file:__FILE__ func:__func__ line:__LINE__ msg:@"或constructor函数中初始化🔥"];
    [logger flushLog:YES];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    _subLoggers = [NSMutableArray arrayWithCapacity:10];
    // 初始化一个测试的GUID
    id deviceIdObj = [[NSUserDefaults standardUserDefaults] objectForKey:@"tdiagnose_test_device_guid"];
    self.deviceId = deviceIdObj ?: @"123456";
    
#if __has_include(<RaftKit/RaftKit.h>)
    // 初始化RaftKit调试工具
    [RFKTManager install];
#endif
    
    
    // 打日志模块初始化 begin--------------------------
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig]; //可直接使用默认配置
    // 或自定义一些配置
    TDOSLoggerConfig *customConfig = [TDOSLoggerConfig configWithLogPath:loggerConfig.logPath
                                                               logPrefix:@"TDiagnoseLog"
                                                            defaultLevel:RAFTLogLevelAll
                                                            andPublicKey:TDOSLOG_PUBKEY];
    
    // ⚠️请注意: 一般情况下，上述Config参数中logPrefix建议设置为固定值。
    // 然而，如果logPrefix发生变化，请正确设置如下isLogFilePrefixChanged属性，以确保旧的mmap文件得到更新，避免丢失部分日志。
    // 常见使用场景如将App版本号作为logPrefix，此时logPrefix将跟随版本更新发生变化，可如下设置：
    // customConfig.isLogFilePrefixChanged = [MyApp isFirstLaunchAfterUpgrade];
    
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:customConfig];
    [logger setConsoleLogEnabled:YES];// 开启控制台日志（可选，建议仅在调试时开启）
    [logger setMaxLogAliveTime:(7 * 24 * 60 * 60)]; // 设置本地日志最大保留时间（可选，默认保存10天）
    
    // 日志模块解耦层，可选，可替换
    TDOSLoggerProxy *loggerProxy = [TDOSLoggerProxy defaultProxy];
    [loggerProxy setLogger:logger];
    // 打日志模块初始化 end--------------------------
    
    
    // 打日志多实例测试 begin--------------------------
    // New: 支持创建多个打日志子实例, 实现日志输出与主实例隔离
    // Tips: 子实例创建后，需注册以支持远程捞日志，见下方“registSubLogger:”
    for (int i = 0; i < 10; i++) {
        NSString *subLoggerPath = [NSTemporaryDirectory() stringByAppendingPathComponent:[NSString stringWithFormat:@"SubLogger%d", i]];
        // 创建子实例的方法可以与主实例完全一致，也可以使用-[TDOSLogger createSubLoggerInstanceWithLogPrefix:]的快捷方法。
        // 需要注意的是，若子实例使用了与主实例不同的加密密钥，平台端将无法自动解密子实例日志。
        TDOSLoggerConfig *subLoggerConfig = [TDOSLoggerConfig configWithLogPath:subLoggerPath
                                                                      logPrefix:[NSString stringWithFormat:@"TestLog%d", i]
                                                                   defaultLevel:RAFTLogLevelError
                                                                   andPublicKey:TDOSLOG_PUBKEY];
        id<TDLoggingIMPProtocol> subLogger = [[TDOSLogger alloc] initWithConfig:subLoggerConfig];
        [self.subLoggers addObject:subLogger];
        [logger log:RAFTLogLevelFatal tag:@"SubLogger" file:__FILE__ func:__FUNCTION__ line:__LINE__ format:@"Logger%d初始化", i, nil];
    }
    self.subLogger = self.subLoggers.firstObject;
    // 打日志多实例测试 end--------------------------
    
    
    // 捞日志模块初始化 begin--------------------------
    // 给捞日志模块传入一些必要依赖，目前需要
    // 1、打日志模块，用于输出捞日志模块内部日志
    // 2、KV存储模块，用于捞日志模块内部持久化任务信息，实现重试等逻辑
    // 3、文件打包模块，用于日志文件打包
    TDIAGDepends *depends = [TDIAGDepends dependsWithLogImp:loggerProxy
                                               kvFactoryImp:[TDMMKVFactoryImpl sharedInstance]
                                           andFilePackerImp:[TDLogFilePackerImp new]];
    
    // New: 如有日志子实例，需注册以支持远程捞日志，如无请忽略
    // Tips: 由于平台限制，暂不支持单独捞取子实例日志，子实例日志文件将与主实例文件一同打包上传
    for (id<TDLoggingIMPProtocol> subLogger in self.subLoggers) {
        [depends registSubLogger:subLogger];
    }
    
    // appid & appKey, 平台生成
    NSString *appID = TDOSLOG_APPID;
    NSString *appKey = TDOSLOG_APPKEY;
    
    // 生成捞日志模块配置实例，并初始化
    TDLogSDKConfig *config = [TDLogSDKConfig configWithAppId:appID
                                                      appKey:appKey
                                                  dataSource:self
                                                     depends:depends];
    config.customServerHost = TDOSLOG_HOST;
    // 海外版需额外设置如下参数
    // config.serverHostType = TDLogServerHostTypeOversea;
    
    // ----- new ------ 新增自动上报频率控制及流量控制设置项：
    // 1、开启频率控制（默认不限制），传空表示使用SDK默认频控策略：2次/5min，也可传入自定义策略；被限制后自动上报接口会回调失败。
    //    举例：10min内最多只允许3次上报（采用令牌桶算法）
    //    TDLogFrequencyControlStrategy *strategy = [TDLogFrequencyControlStrategy new];
    //    strategy.times = 3;
    //    strategy.timeInterval = 10 * 60;
    // 注意，该接口要求TDLogSDKDataSource必须实现whitelistForAutoUploadTags协议，提供自动上报tag白名单，避免影响必要上报。
    [config setFrequencyLimitStatusForAutoUpload:YES
                       withCustomControlStrategy:nil]; // 推荐设置，确保不频繁自动上报
    
    // 2、开启流量控制（默认不限制），传0表示禁止上报，传入负值代表不限制，被限制后自动上报接口会回调失败。
    // 注意，该接口要求TDLogSDKDataSource必须实现whitelistForAutoUploadTags协议，提供自动上报tag白名单，避免影响必要上报。
    [config setTrafficQuota24hLimitForAutoUpload:(200 * 1024 * 1024)
                                         xgQuota:(50 * 1024 * 1024)]; // 可选，设置自动上报流量限额
    
    [[TDLogSDK sharedInstance] startWithConfig:config];
    // 捞日志模块初始化 end--------------------------
    
    return YES;
}

#pragma mark - TDLogSDKDataSource

- (NSString *)guidForTDLog {
    // 返回用户ID或设备ID，用于向平台请求捞日志或染色等配置时进行身份匹配
    return self.deviceId;
}

- (NSArray<NSString *> *)extraFilesForTDLogReport {
    // 此接口可选实现，用于返回日志上报时的固定附件全路径，无效地址会被过滤
    return @[ @"testPath1", @"testPath2" ];
}

- (NSArray<NSString *> *)whitelistForAutoUploadTags {
    // 返回自动上报白名单，配合自动上报频率控制/流量控制接口使用
    // 在tag白名单内的自动上报将忽略上述控制策略。
    return @[ @"用户反馈", @"bugly" ];
}

#pragma mark - 其他测试辅助

- (void)setDeviceId:(NSString *)deviceId {
    _deviceId = deviceId;
    [[NSUserDefaults standardUserDefaults] setObject:deviceId forKey:@"tdiagnose_test_device_guid"];
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}


@end
