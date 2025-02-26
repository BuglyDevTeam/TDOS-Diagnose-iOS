//
//  ViewController.m
//  TDiagnoseExampleMac
//
//  Created by raycgwang on 13/3/2023.
//  Copyright (c) 2021 raycgwang. All rights reserved.
//

#import "ViewController.h"
#import "AppDelegate.h"
@import TDOS_Diagnose;

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)onPullConfigBtnPressed:(id)sender {
    [TDLogSDK.sharedInstance requestLogConfigFromServer];
}

- (IBAction)onUploadBtnPressed:(id)sender {
    // test print
    TDLogDebug(@"TDSTest", @"hello");
    TDLogDebug(@"TDSTest", @"hello", nil);
    TDLogError(@"TDSTest", @"%@", self);
    TDLogError(@"TDSTest", @"%d", YES);
    TDLogError(@"TDSTest", @"%d", NO);
    TDLogDebug(@"TDSTest", @"%d, %@", 1, @"hello");
    TDLogDebug(@"TDSTest", @"%d, %@", 0, @"hello");
    TDLogDebug(@"TDSTest", @"hello %d", YES);
    TDLogDebug(@"TDSTest", @"hello %d", NO);

    // 获取日志实例
    id<TDLoggingIMPProtocol> logger = TDOSLoggerProxy.defaultProxy;

    // 注意：一定要flush下日志
    [logger flushLog:YES];

    // New：新增支持限定最大日志量，超过该大小优先丢弃旧文件
    // 使用如下接口获取，如限制最大获取200M（请勿设置过小，以免影响正常上报）：
    time_t currentTime = time(0);
    NSArray<NSString *> *logFiles = [logger getPeroidLogFilesWithStartTime:(currentTime - 3600)
                                                                   endTime:currentTime
                                                                 sizeLimit:(200 * 1024 * 1024)];

    // 第一步：组装上报的附加信息，主要用于跨系统检索使用（queryInfo可选, 无需使用传空即可）
    TDLogExtQueryInfo *queryInfo = [TDLogExtQueryInfo new];
    queryInfo.queryKey = @"1234qwer"; // 必填，如可填入bugly crash id，用于从bugly平台直接关联本次上报
    queryInfo.sourcePlatform = @"bugly"; // 选填，表示自动上报来自bugly自动触发，仅用于平台统计
    // 第二步：调用上报接口
    [TDLogSDK.sharedInstance uploadFiles:logFiles // 测试用，传入空数组将不会执行上报动作
                                 withTag:@"L2"
                                 summary:@"my summary"
                            extQueryInfo:queryInfo
                           andExtendInfo:@{@"testKey": @"testValue"}
                              completion:^(BOOL result, NSString * _Nullable errMsg) {
        NSLog(@"auto upload 2 result:%d error:%@", result, errMsg);
    }];
}

@end
