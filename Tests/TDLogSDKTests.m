//
//  TDiagnoseTests.m
//  TDiagnoseTests
//
//  Created by raycgwang on 12/10/2021.
//  Copyright (c) 2021 raycgwang. All rights reserved.
//

@import XCTest;
@import TDOS_Diagnose;
#import <OCMock/OCMock.h>

@interface TDLogSDK (UnitTest)

/// 配置拉取管理
@property (nonatomic, strong) TDLogConfigRequestManager *configPullManager;
/// 文件上传者
@property (nonatomic, strong) TDLogUploadFileUploader *fileUploader;
/// 状态上报(配置拉取、文件上传)
@property (nonatomic, strong) TDLogStateReportManager *stateReportor;
/// 打包上传串行队列
@property (nonatomic, strong) dispatch_queue_t logReportSerialQueue;

/// 获取压缩包文件名
- (NSString *)getZipFileNameWithGuid:(NSString *)guid;

@end

@interface TDLogConfigRequestManager (UnitTest)

/// 内部请求接口
- (void)requestUploadLogConfigFromServer:(NSString *)guid isFromPush:(BOOL)isFromPush;

@end

@interface TDLogSDKTests : XCTestCase <TDLogSDKDataSource>

@end

@implementation TDLogSDKTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testSDKConfig {
    /*CaseAdditionInfo start
        {
            "用例等级=P0",
            "用例类型=4",
            "被测函数= +configWithAppId:"
            "用例描述=测试SDK配置实例可正确初始化"
        }
    CaseAdditionInfo end*/
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig];
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:loggerConfig];
    TDOSLoggerProxy *loggerProxy = [TDOSLoggerProxy defaultProxy];
    [loggerProxy setLogger:logger];
    
    // 初始化捞日志模块
    TDIAGDepends *depends = [TDIAGDepends dependsWithLogImp:loggerProxy
                                               kvFactoryImp:[TDMMKVFactoryImpl sharedInstance]
                                           andFilePackerImp:[TDLogFilePackerImp new]];
    
    TDLogSDKConfig *sdkConfig = [TDLogSDKConfig configWithAppId:@"test1"
                                                         appKey:@"test2"
                                                     dataSource:self
                                                        depends:depends];
    XCTAssertNotNil(sdkConfig);
    XCTAssertNotNil(sdkConfig.depends);
    XCTAssertNotNil(sdkConfig.logMediator);
    XCTAssert([sdkConfig.hostData.guidForTDLog isEqualToString:@"testGUID"]);
    
}

- (NSString *)guidForTDLog {
    return @"testGUID";
}

- (TDLogSDKConfig *)getSdkConfig {
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig];
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:loggerConfig];
    TDOSLoggerProxy *loggerProxy = [TDOSLoggerProxy defaultProxy];
    [loggerProxy setLogger:logger];
    
    // 初始化捞日志模块
    TDIAGDepends *depends = [TDIAGDepends dependsWithLogImp:loggerProxy
                                               kvFactoryImp:[TDMMKVFactoryImpl sharedInstance]
                                           andFilePackerImp:[TDLogFilePackerImp new]];
    
    TDLogSDKConfig *sdkConfig = [TDLogSDKConfig configWithAppId:@"test1"
                                                         appKey:@"test2"
                                                     dataSource:self
                                                        depends:depends];
    return sdkConfig;
}

- (void)testSDKInit {
    /*CaseAdditionInfo start
        {
            "用例等级=P0",
            "用例类型=4",
            "被测函数= -startWithConfig:"
            "用例描述=测试SDK实例可正确初始化"
        }
    CaseAdditionInfo end*/
    TDLogSDKConfig * sdkConfig = [self getSdkConfig];
    TDLogSDK *logSDK = [TDLogSDK sharedInstance];
    XCTAssertNotNil(logSDK);
    [logSDK startWithConfig:sdkConfig];
    XCTAssert(logSDK.sdkConfig == sdkConfig);
}

- (void)testGetZipFileNameWithGuid {
    TDLogSDK *sdk = [TDLogSDK new];
    NSString *fileName = [sdk getZipFileNameWithGuid:@"testGUID"];
    XCTAssert([fileName.pathExtension isEqualToString:@"zip"]);
    XCTAssert([fileName containsString:@"testG"]);
}

- (void)testLazyInitializers {
    TDLogSDK *sdk = [TDLogSDK sharedInstance];
    XCTAssertNotNil(sdk.logReportSerialQueue);
    XCTAssertNotNil(sdk.configPullManager);
    XCTAssertNotNil(sdk.fileUploader);
    XCTAssertNotNil(sdk.stateReportor);
}

- (void)testLogConfigRequestManager {
    id delegate = OCMProtocolMock(@protocol(TDLogConfigRequestDelegate));
    TDLogSDKConfig *sdkConfig = [self getSdkConfig];
    TDLogConfigRequestManager *reqManager = [[TDLogConfigRequestManager alloc] initWithSDKConfig:sdkConfig
                                                                                     andDelegate:delegate];
    XCTAssertNotNil(reqManager);
    XCTAssertNotNil(reqManager.delegate);
    
    id mockManager = OCMPartialMock(reqManager);
    OCMStub([mockManager requestUploadLogConfigFromServer:[OCMArg any] isFromPush:[OCMArg any]]);
    [mockManager requestUploadLogConfigByForce];
    sleep(1);
    OCMVerify([mockManager requestUploadLogConfigFromServer:[OCMArg any] isFromPush:YES]);
    [mockManager stopMocking];
}

- (void)testLogStateReportManager {
    TDLogStateReportManager *stateReportManager = [[TDLogStateReportManager alloc] initWithSDKConfig:[self getSdkConfig]];
    XCTAssertNotNil(stateReportManager);
}

@end

