//
//  AppDelegate.m
//  TDOS_DiagnoseDemo
//
//  Created by Hongbo Cui on 2025/2/25.
//

#import "AppDelegate.h"

@import TDOS_Diagnose;

//#define TDOSLOG_APPID   @"a2031e998b"
//#define TDOSLOG_APPKEY  @"5f58a9cf-0acc-4c0d-a020-fc8f0bacb3cc"
#define TDOSLOG_APPID   @"b550e9bebd"
#define TDOSLOG_APPKEY  @"a9ecbb72-5f7f-473a-8e38-e4e77d439450"
#define TDOSLOG_HOST @"pro.bugly.qq.com"

// 定义加密公钥,传空或nil或格式不正确的公钥，SDK都不加密
#define TDOSLOG_PUBKEY @""

@interface AppDelegate ()<TDLogSDKDataSource>

@property (nonatomic, strong) NSMutableArray<id<TDLoggingIMPProtocol>> *subLoggers;

@end

@implementation AppDelegate

+ (void)load {
    // 测试pre-main阶段初始化日志
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig];
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:loggerConfig];
    [logger log:RAFTLogLevelError tag:@"test" file:__FILE__ func:__func__ line:__LINE__ msg:@"测试在pre-main阶段打印日志"];
    [logger flushLog:YES];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    _subLoggers = [NSMutableArray arrayWithCapacity:10];
    // 初始化一个测试的GUID
    id deviceIdObj = [[NSUserDefaults standardUserDefaults] objectForKey:@"tdiagnose_test_device_guid"];
    self.deviceId = deviceIdObj ?: @"123456";
    
    
    
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig]; //可直接使用默认配置
    
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
 
    // 捞日志模块初始化 begin--------------------------
    // 给捞日志模块传入一些必要依赖
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
    config.serverHostType = TDLogServerHostTypeBuglyPro;
    
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
