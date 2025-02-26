//
//  TDLogCOSTests.m
//  TDOS-Diagnose-Unit-UnitTests
//
//  Created by raycgwang on 2022/2/18.
//  Copyright © 2021 RaftKit Team. All rights reserved.

#import <XCTest/XCTest.h>
#import <OCMock/OCMock.h>
@import TDOS_Diagnose;
#import <YYModel/YYModel.h>

@interface TDLogCosTaskKVPersist (UnitTest)

/// KV存储类实例
@property (nonatomic, strong) id<RAFTKVStorageProtocol> mKVService;

@end


@interface TDLogCosUploadManager (UnitTest)

/// COS 上传地址
@property (atomic, copy) NSString *cosUploadUrl;
/// 与服务器时间差，单位s
@property (nonatomic, assign) time_t serverTimeDiff;

/// 获取分片上传XML信息
- (NSString *)getUploadedPartInfosInXML:(NSArray<TDLogCosMultipartInfo *> *)arr;
/// 获取临时文件路径
+ (NSString *)cosTempFilePathWithExtension:(NSString *)extension;
/// 获取文件分片
/// @param cosTask 上传任务
- (NSArray<TDLogCosFileOffsetBody *> *)getFileLocalUploadPartsWithTask:(TDLogCOSUploadTaskInfo *)cosTask;

/// 获取COS鉴权字符串
- (NSString *)cosAuthStringForRequest:(NSMutableURLRequest *)request;

/// 简单上传内部接口
- (void)simpleUploadFileWithPath:(NSString *)filePath
                        taskInfo:(TDLogUploadTaskModel *)uploadInfo
                      completion:(TDLogCosUploadCallBack)completion;

/// 分片上传内部接口
- (void)startMultiPartUploadWithFilePath:(NSString *)filePath
                                taskInfo:(TDLogUploadTaskModel *)uploadInfo
                              completion:(TDLogCosUploadCallBack)completion;

/// 分片上传-初始化
- (void)requestMultiPartUpload_Initiate:(TDLogCOSUploadTaskInfo *)cosUploadTask;
/// 分片上传-上传分片
- (void)requestMultiPartUpload_UploadPart:(TDLogCOSUploadTaskInfo *)cosUploadTask;
/// 分片上传-结束
- (void)requestMultiPartUpload_Complete:(TDLogCOSUploadTaskInfo *)cosUploadTask;

/// 强制更新COS票据（简单上传、分片初始化两个场景必须调用）
- (BOOL)forceUpdateCosUploadUrlAndSecretInfo:(TDLogCOSUploadTaskInfo *)cosUploadTask;

/// 保存并执行任务
- (void)saveAndRunTask:(TDLogCOSUploadTaskInfo *)cosTask;

@end

@interface TDLogCOSTests : XCTestCase

@end

@implementation TDLogCOSTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testCOSAuthCreator {
    TDLogCosAuthV5Creator *creator = [TDLogCosAuthV5Creator new];
    creator.secretID = @"testSecretID";
    creator.secretKey = @"testSecretKey";
    creator.token = @"testToken";
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:@"www.qq.com"]];
    NSString *authStr = [creator signatureForData:request];
    XCTAssert(authStr.length > 0);
}

- (void)testCOSKVPersist {
    id mockObj = OCMProtocolMock(@protocol(RAFTKVStorageFactoryProtocol));
    id<RAFTKVStorageProtocol> mockKVService = OCMProtocolMock(@protocol(RAFTKVStorageProtocol));
    TDLogCosTaskKVPersist *persist = [[TDLogCosTaskKVPersist alloc] initWithKVFactory:mockObj];
    persist.mKVService = mockKVService;
    XCTAssertNotNil(persist);
    
    TDLogCOSUploadTaskInfo *task = [[TDLogCOSUploadTaskInfo alloc] init];
    task.filePath = @"testPath";
    [persist addTaskInfo:task];
    OCMVerify([mockKVService setObject:OCMArg.any forKey:@"testPath"]);
    
    [persist removeTaskInfo:task];
    OCMVerify([mockKVService removeValueForKey:@"testPath"]);
    OCMVerify([mockKVService trim]);
    
    OCMStub([mockKVService allKeys]).andReturn(@[@"1"]);
    OCMStub([mockKVService objectForKey:OCMArg.any withClass:OCMArg.any]).andReturn([task yy_modelToJSONString]);
    NSArray <TDLogCOSUploadTaskInfo *> *tasks = [persist getAllTaskInfos];
    OCMVerify([mockKVService allKeys]);
    OCMVerify([mockKVService objectForKey:@"1" withClass:NSString.class]);
    XCTAssert(tasks.count == 1);
    [mockObj stopMocking];
}

- (void)testCOSUploadManager {
    TDLogCosUploadManager *manager = [TDLogCosUploadManager sharedInstance];
    XCTAssertNotNil(manager);
}

- (void)testGetUploadedPartInfosInXML {
    TDLogCosUploadManager *manager = [TDLogCosUploadManager sharedInstance];
    TDLogCosMultipartInfo *partInfo1 = [TDLogCosMultipartInfo new];
    partInfo1.partNumber = @"1";
    partInfo1.eTag = @"e1";
    TDLogCosMultipartInfo *partInfo2 = [TDLogCosMultipartInfo new];
    partInfo2.partNumber = @"2";
    partInfo2.eTag = @"e2";
    NSString *xml = [manager getUploadedPartInfosInXML:@[]];
    XCTAssert(xml.length == 0);
    
    xml = [manager getUploadedPartInfosInXML:@[@1, @2]];
    XCTAssert(xml.length == 0);
    xml = [manager getUploadedPartInfosInXML:@[partInfo1, partInfo2]];
    XCTAssert(xml.length > 0);
    NSString *xml2 = [manager getUploadedPartInfosInXML:@[partInfo2, partInfo1]];
    XCTAssert(xml2.length > 0);
    XCTAssert([xml isEqualToString:xml2]);
    
}

- (void)testCOSTempFilePath {
    NSString *tmpPath = [TDLogCosUploadManager cosTempFilePathWithExtension:@"1"];
    XCTAssertNotNil(tmpPath);
    XCTAssert([tmpPath.pathExtension isEqualToString:@"1"]);
}

- (void)testUpdateCosUploadUrl {
    NSString *testUrl = @"test";
    XCTAssert([TDLogCosUploadManager.sharedInstance.cosUploadUrl length] == 0);
    [TDLogCosUploadManager.sharedInstance updateCosUploadUrl:testUrl];
    XCTAssert([TDLogCosUploadManager.sharedInstance.cosUploadUrl isEqualToString:testUrl]);
    [TDLogCosUploadManager.sharedInstance updateCosUploadUrl:@""];
    XCTAssert([TDLogCosUploadManager.sharedInstance.cosUploadUrl isEqualToString:testUrl]);
}

- (void)testGetFileLocalUploadParts {
    TDLogCOSUploadTaskInfo *testTask = [TDLogCOSUploadTaskInfo new];
    testTask.filePath = @"1";
    testTask.uploadedSize = 0;
    testTask.sliceSize = 0;
    
    NSArray<TDLogCosFileOffsetBody *> *parts = [TDLogCosUploadManager.sharedInstance getFileLocalUploadPartsWithTask:testTask];
    XCTAssert(parts.count == 1);
}

- (void)testCosAuthStringForRequest {
    TDLogUploadTmpCosSecretInfo *testInfo = [TDLogUploadTmpCosSecretInfo new];
    testInfo.tmpSecretId = @"1";
    testInfo.tmpSecretKey = @"2";
    testInfo.xcosSecurityToken = @"3";
    testInfo.expiredTime = 0;
    [TDLogCosUploadManager.sharedInstance updateTmpSecretInfo:testInfo];
    NSMutableURLRequest *testRequest = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:@"www.qq.com"]];
    NSString *authStr = [TDLogCosUploadManager.sharedInstance cosAuthStringForRequest:testRequest];
    XCTAssert([authStr isEqualToString:@""]);
    
    testInfo.expiredTime = 12345678;
    [TDLogCosUploadManager.sharedInstance updateTmpSecretInfo:testInfo];
    authStr = [TDLogCosUploadManager.sharedInstance cosAuthStringForRequest:testRequest];
    XCTAssert(authStr.length > 0);
}

- (void)testCOSUploadFileWithTaskInfo {
    id cosUploadManager = OCMPartialMock(TDLogCosUploadManager.sharedInstance);
    OCMStub([cosUploadManager forceUpdateCosUploadUrlAndSecretInfo:[OCMArg any]]).andReturn(YES);
    OCMStub([cosUploadManager saveAndRunTask:[OCMArg any]]);
    
    NSString *testPath = @"1";
    TDLogUploadTaskModel *testTask = [TDLogUploadTaskModel modelWithType:TDLogUploadType_Pull
                                                                filePath:testPath
                                                                 andGuid:@"testGUID"];
    void (^compBlock)(BOOL, NSString *, NSString *) = ^(BOOL succeed, NSString * _Nullable cosDownloadUrl,
                                                        NSString * _Nullable errorString){};
    [cosUploadManager uploadFile:testPath taskInfo:testTask completion:compBlock];
    XCTAssert(testTask.isCOSMultiPartUpload == NO);
    OCMVerify([cosUploadManager simpleUploadFileWithPath:testPath taskInfo:testTask completion:[OCMArg any]]);
    NSString *largeFilePath = [self.class prepareATestFileWithSize:21 * 1024 * 1024];
    
    [cosUploadManager uploadFile:largeFilePath taskInfo:testTask completion:compBlock];
    XCTAssert(testTask.isCOSMultiPartUpload == YES);
    OCMVerify([cosUploadManager startMultiPartUploadWithFilePath:largeFilePath taskInfo:testTask completion:[OCMArg any]]);
    
    [cosUploadManager stopMocking];
}


#pragma mark - Utils

+ (NSString *)prepareATestFileWithSize:(long long)fileSize {
    NSString *filePath = [NSTemporaryDirectory() stringByAppendingPathComponent:@"test.txt"];
    FILE *file;
    file = fopen([filePath UTF8String], "wb+");
    fsetpos(file, &fileSize);
    fwrite("", 1, 1, file);
    fclose(file);
    return filePath;
}

@end
