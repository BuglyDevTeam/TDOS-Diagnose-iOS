//
//  TDLogUtilsTests.m
//  TDOS-Diagnose-Unit-UnitTests
//
//  Created by raycgwang on 2022/2/18.
//  Copyright © 2021 RaftKit Team. All rights reserved.

#import <XCTest/XCTest.h>
#import <OCMock/OCMock.h>
@import TDOS_Diagnose;

@interface TDLogUtilsTests : XCTestCase <TDLogSDKDataSource>

@end

@implementation TDLogUtilsTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testFilePacker {
    TDLogFilePackerImp *filePacker = [[TDLogFilePackerImp alloc] init];
    XCTAssertNotNil(filePacker);
    XCTAssert(filePacker.packDir.length > 0);
    [filePacker setCustomPackDir:NSTemporaryDirectory()];
    XCTAssert([filePacker.packDir isEqualToString:NSTemporaryDirectory()]);
    
    char *buff;
    buff = genRandomString(2000);
    NSString *randomStr = [NSString stringWithUTF8String:buff];
    free(buff);
    NSString *testFile1 = [NSString stringWithFormat:@"%@/unittest1_%d.txt", NSTemporaryDirectory(), arc4random() % 10000];
    NSString *testFile2 = [NSString stringWithFormat:@"%@/unittest2_%d.txt", NSTemporaryDirectory(), arc4random() % 10000];
    [randomStr writeToFile:testFile1 atomically:YES encoding:NSUTF8StringEncoding error:nil];
    [randomStr writeToFile:testFile2 atomically:YES encoding:NSUTF8StringEncoding error:nil];
    
    NSString *zipFilePath = [filePacker packFiles:@[testFile1, testFile2] withZipName:@"unittest_zipfile"];
    XCTAssertNotNil(zipFilePath);
    XCTAssertTrue([[NSFileManager defaultManager] fileExistsAtPath:zipFilePath]);
    XCTAssert([TDIAUtil fileSizeWithPath:zipFilePath] > 0);
    
    [[NSFileManager defaultManager] removeItemAtPath:testFile1 error:nil];
    [[NSFileManager defaultManager] removeItemAtPath:testFile2 error:nil];
    [[NSFileManager defaultManager] removeItemAtPath:zipFilePath error:nil];
}


char* genRandomString(int length) {
    int flag, i;
    char* string;
    srand((unsigned) time(NULL ));
    if ((string = (char*) malloc(length)) == NULL ) {
        return NULL;
    }
                 
    for (i = 0; i < length - 1; i++) {
        flag = rand() % 3;
        switch (flag) {
            case 0:
                string[i] = 'A' + rand() % 26;
                break;
            case 1:
                string[i] = 'a' + rand() % 26;
                break;
        case 2:
                string[i] = '0' + rand() % 10;
                break;
        default:
                string[i] = 'x';
                break;
        }
    }
    string[length - 1] = '\0';
    return string;
}

- (void)testXMLReader {
    NSString *testXML = @"<h1>a</h1>";
    NSError *error;
    NSDictionary *dict = [TDIAXMLReader dictionaryForXMLString:testXML error:&error];
    XCTAssert([[dict objectForKey:@"h1"] isKindOfClass:NSDictionary.class]);
    XCTAssert([[[dict objectForKey:@"h1"] objectForKey:@"text"] isEqualToString:@"a"]);
}

- (void)testStateSync {
    TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig];
    TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:loggerConfig];
    
    id mockKV = OCMProtocolMock(@protocol(RAFTKVStorageFactoryProtocol));
    id mockPacker = OCMProtocolMock(@protocol(TDLogFilePackerProtocol));
    TDIAGDepends *depends = [TDIAGDepends dependsWithLogImp:logger
                                               kvFactoryImp:mockKV
                                           andFilePackerImp:mockPacker];
    TDLogSDKConfig *sdkConfig = [TDLogSDKConfig configWithAppId:@"1"
                                                         appKey:@"2"
                                                     dataSource:self
                                                        depends:depends];
    TDLogStateReportManager *manager = [[TDLogStateReportManager alloc] initWithSDKConfig:sdkConfig];
    XCTAssertNotNil(manager);
}

- (void)testFileNameFilter {
    TDLogUploadFileNameFilter *filter = [[TDLogUploadFileNameFilter alloc] initWithFileNameRegex:@"test.*\.xlog"];
    XCTAssert([filter isMatch:@"test1.xlog"]);
    XCTAssert(![filter isMatch:@"1.xlog"]);
    XCTAssert([filter isMatch:@"test2.xlog"]);
    XCTAssert(![filter isMatch:@"test2.log"]);
    XCTAssert(![filter isMatch:nil]);
}

- (void)testLogUploadRetryStrategy {
    TDLogUploadRetryStrategy *st = [[TDLogUploadRetryStrategy alloc] initWithMaxRetryTimes:3];
    XCTAssert(st.maxRetryTimes == 3);
    TDLogUploadTaskModel *model = [TDLogUploadTaskModel modelWithType:TDLogUploadType_Pull filePath:@"1" andGuid:@"2"];
    model.uploadRetryTimes = 1;
    XCTAssert([st isMatch:model] == YES);
    XCTAssert([st isDeleteTask:model] == NO);
    model.uploadRetryTimes = 3;
    XCTAssert([st isMatch:model] == NO);
    XCTAssert([st isDeleteTask:model] == YES);
}

- (nonnull NSString *)guidForTDLog {
    return @"testGUID1";
}

@end
