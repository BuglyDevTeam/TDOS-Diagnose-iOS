//
//  ViewController.m
//  TDOS_DiagnoseDemo
//
//  Created by Hongbo Cui on 2025/2/25.
//

#import "ViewController.h"
#import <TDOS_Diagnose/TDOS_Diagnose.h>
#import <TDOS_Diagnose/TDOSLoggerProxy.h>
#import <TDOS_Diagnose/TDOSLogger.h>
#import "AppDelegate.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    AppDelegate *appDelegate = [UIApplication sharedApplication].delegate;
    self.guidTextField.text = appDelegate.deviceId;
    [self updateColorLabel];
    
    TDLogDebug(@"TDSTest", @"hello");
    TDLogDebug(@"TDSTest", @"hello", nil);
    TDLogError(@"TDSTest", @"%@", self);
    TDLogError(@"TDSTest", @"%d", YES);
    TDLogError(@"TDSTest", @"%d", NO);
    TDLogDebug(@"TDSTest", @"%d, %@", 1, @"hello");
    TDLogDebug(@"TDSTest", @"%d, %@", 0, @"hello");
    TDLogDebug(@"TDSTest", @"hello %d", YES);
    TDLogDebug(@"TDSTest", @"hello %d", NO);
    // may crash if arguments not satisfy format string, e.g.
    // since %@ will try to access some illegal address
    // TDLogDebug(@"TDSTest", @"test nil1 %d %d %d %d %@ %@ %@ %@");
    TDLogDebug(@"TDSTest", @"test nil1 %d", nil);
    TDLogDebug(@"TDSTest", @"test nil2 %d %@", nil);
    TDLogDebug(@"TDSTest", nil);
    TDLogDebug(@"TDSTest", @"");
    TDLogDebug(@"TDSTest", @"Hello TDSTest", @"fdsaf");
    TDLogDebug(@"TDSTest", @"Hello TDSTest %@, %@, %d", @"fdsafads", @(1), -1);
    TDLogDebug(@"TDSTest", @"Hello TDSTest %@, %@, %d \r\n fdsafd\ndfasf", @"fdsafads", @(1), -1, @(YES), @(2));
    TDLogDebug(@"TDSTest", @"🇨🇳😊😙\xed\xa0\xbd…");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onPullConfigBtnPressed:(id)sender {
    [TDLogSDK.sharedInstance requestLogConfigFromServer];
    
    __weak __typeof(self)weakSelf = self;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [weakSelf updateColorLabel];
    });
}

- (IBAction)onTestTriggerBtnPressed:(id)sender {
    [TDOSLoggerProxy.defaultProxy flushLog:YES];
    time_t currentTime = time(0);

    // New：新增支持限定最大日志量，超过该大小优先丢弃旧文件
    // 使用如下接口获取，如限制最大获取200M（请勿设置过小，以免影响正常上报）：
    NSArray<NSString *> *logFiles = [TDOSLoggerProxy.defaultProxy getPeroidLogFilesWithStartTime:(currentTime - 3600)
                                                                                          endTime:currentTime
                                                                                       sizeLimit:(200 * 1024 * 1024)];
    // 如无需限制最大日志量，可继续使用原接口：
    // 获取最近1小时日志
//    NSArray<NSString *> *logFiles = [TDOSLoggerProxy.defaultProxy getPeroidLogFilesWithStartTime:(currentTime - 3600)
//                                                                                          endTime:currentTime];
    // 示例1：调用诊断SDK上传接口
    [TDLogSDK.sharedInstance uploadFiles:logFiles
                                 withTag:@"L1"
                                 summary:@"my summary"
                           andExtendInfo:@{@"testKey": @"testValue"}
                              completion:^(BOOL result, NSString * _Nullable errMsg) {
        NSLog(@"auto upload result:%d error:%@", result, errMsg);
    }];
    
    
    // 示例2：调用诊断SDK上传接口2
    // 第一步：组装上报的附加信息，主要用于跨系统检索使用
    TDLogExtQueryInfo *queryInfo = [TDLogExtQueryInfo new];
    queryInfo.queryKey = @"--bugly-crash-id--"; // 必填，如可填入bugly crash id，用于从bugly平台直接关联本次上报
    queryInfo.sourcePlatform = @"--bugly--"; // 选填，表示自动上报来自bugly自动触发，仅用于平台统计
    // 第二步：调用上报接口
    [TDLogSDK.sharedInstance uploadFiles:@[] // 测试用，传入空数组将不会执行上报动作
                                 withTag:@"L2"
                                 summary:@"my summary"
                            extQueryInfo:queryInfo
                           andExtendInfo:@{@"testKey": @"testValue"}
                              completion:^(BOOL result, NSString * _Nullable errMsg) {
        NSLog(@"auto upload 2 result:%d error:%@", result, errMsg);
    }];
}

- (IBAction)testWriteLogs:(id)sender {
    for (int i = 0; i < 100; i++) {
        TDLogDebug(@"TDOSLog", @"debug--111---%u", arc4random());
        TDLogInfo(@"TDOSLog", @"info---222---%u", arc4random());
        TDLogWarn(@"TDOSLog", @"warn---333---%u", arc4random());
        TDLogError(@"TDOSLog", @"error---444---%u", arc4random());
        TDLogFatal(@"TDOSLog", @"fatal---555---%u", arc4random());
        dispatch_async(dispatch_queue_create("tdosConcurrentQ", DISPATCH_QUEUE_CONCURRENT), ^{
            TDLogFatal(@"TDOSLog", @"concurrent---666---%u", arc4random());
        });
    }
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        for (int i = 0; i < 100; i++) {
            TDLogDebug(@"TDOSLog", @"debug--111---%u", arc4random());
            TDLogInfo(@"TDOSLog", @"info---222---%u", arc4random());
            TDLogWarn(@"TDOSLog", @"warn---333---%u", arc4random());
            TDLogError(@"TDOSLog", @"error---444---%u", arc4random());
            TDLogFatal(@"TDOSLog", @"fatal---555---%u", arc4random());
            dispatch_async(dispatch_queue_create("tdosConcurrentQ", DISPATCH_QUEUE_CONCURRENT), ^{
                TDLogFatal(@"TDOSLog", @"concurrent---666---%u", arc4random());
            });
        }
    });
}

- (IBAction)testSubLoggerWriteLogs:(id)sender {
    AppDelegate *appDelegate = (AppDelegate *)([UIApplication sharedApplication].delegate);
    [appDelegate.subLogger log:RAFTLogLevelFatal
                           tag:@"TDOSLog"
                          file:__FILE__
                          func:__FUNCTION__
                          line:__LINE__
                        format:@"fatal---sublogger test---%u", arc4random(), nil];
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        for (int i = 0; i < 1000; i++) {
            [appDelegate.subLogger log:RAFTLogLevelFatal
                                   tag:@"TDOSLog"
                                  file:__FILE__
                                  func:__FUNCTION__
                                  line:__LINE__
                                format:@"fatal---sublogger test---%u-%d", arc4random(), i, nil];
        }
    });
}


- (void)updateColorLabel {
    RAFTLogLevel logLevel = RAFTLogLevelError;
    NSDictionary *colorInfo = [[NSUserDefaults standardUserDefaults] objectForKey:TDOSLogColorInfoKey];
    if (colorInfo && [colorInfo isKindOfClass:NSDictionary.class]) {
        long level = [[colorInfo objectForKey:TDOSLogColorLevelKey] longValue];
        long endTime = [[colorInfo objectForKey:TDOSLogColorEndTimeKey] longValue];
        if (endTime > time(0)) {
            logLevel = (RAFTLogLevel)level;
        }
    }
    id<TDLoggingIMPProtocol> logger = [TDOSLoggerProxy defaultProxy].logger;
    self.colorLabel.text = [NSString stringWithFormat:@"染色状态：%d\n级别：%ld", [logger isColorState], (long)logLevel];
}

- (IBAction)onRefreshColorStatePressed:(id)sender {
    [self updateColorLabel];
}

- (IBAction)onUpdateGUIDPressed:(id)sender {
    if (self.guidTextField.text.length <= 0) {
        return;
    }
    AppDelegate *appDelegate = (AppDelegate *)([UIApplication sharedApplication].delegate);
    [appDelegate setDeviceId:self.guidTextField.text];
    
    [self updateColorLabel];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.guidTextField endEditing:YES];
}




@end
