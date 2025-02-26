//
//  TDLogRequestCommonTest.m
//  TDOS-Diagnose-Unit-UnitTests
//
//  Created by raycgwang on 2022/2/16.
//  Copyright © 2021 RaftKit Team. All rights reserved.

#import <XCTest/XCTest.h>
@import TDOS_Diagnose;

@interface TDLogRequestCommonTest : XCTestCase

@end

@implementation TDLogRequestCommonTest

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testClientInfo {
    /*CaseAdditionInfo start
        {
            "用例等级=P0",
            "用例类型=4",
            "被测函数= +clientInfoWithGuid:"
            "用例描述=测试组装ClientInfo"
        }
    CaseAdditionInfo end*/
    TDLogConfigClientInfo *clientInfo = [TDLogRequestCommon clientInfoWithGuid:@"testGUID"];
    XCTAssertTrue([clientInfo.guid isEqualToString:@"testGUID"]);
#if TARGET_OS_OSX
    XCTAssertTrue(clientInfo.platform == TDLOG_CONFIG_PULL_PLATFORM_MAC);
#else
    XCTAssertTrue(clientInfo.platform == TDLOG_CONFIG_PULL_PLATFORM_IOS);
#endif
    XCTAssertNotNil(clientInfo.sdkVersion);
    XCTAssertNotNil(clientInfo.appVersion);
    XCTAssertNotNil(clientInfo.appVersion);
    XCTAssertNotNil(clientInfo.osVersion);
    XCTAssertNotNil(clientInfo.deviceId);
    XCTAssertNotNil(clientInfo.bundleId);
}

- (void)testRequestHeaderSignature {
    /*CaseAdditionInfo start
        {
            "用例等级=P0",
            "用例类型=4",
            "被测函数= +headerSignatureWithHttpBody:"
            "用例描述=测试计算请求签名"
        }
    CaseAdditionInfo end*/
    NSString *testStr = @"this is the test string for header signature";
    NSData *testData = [testStr dataUsingEncoding:NSUTF8StringEncoding];
    NSString *testKey = @"testKey";
    NSString *signature = [TDLogRequestCommon headerSignatureWithHttpBody:testData
                                                                   appKey:testKey];
    NSString *expStr = [TDIAUtil hmacSHA256WithContent:testStr secret:testKey];
    XCTAssertTrue([signature isEqualToString:expStr]);
    signature = [TDLogRequestCommon headerSignatureWithHttpBody:[NSData data] appKey:testKey];
    XCTAssertTrue(signature.length == 0);
}

@end
