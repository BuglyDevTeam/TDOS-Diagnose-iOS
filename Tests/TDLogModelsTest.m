//
//  TDLogModelsTest.m
//  TDOS-Diagnose-Unit-UnitTests
//
//  Created by raycgwang on 2022/2/16.
//  Copyright © 2021 RaftKit Team. All rights reserved.

#import <XCTest/XCTest.h>
#import <YYModel/YYModel.h>
@import TDOS_Diagnose;

@interface TDLogModelsTest : XCTestCase

@end

@implementation TDLogModelsTest

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testConfigModels {
    
    TDLogConfigClientInfo *clientInfo = [TDLogRequestCommon clientInfoWithGuid:@"testGUID"];
    TDLogConfigRequestInfo *requestInfo = [TDLogConfigRequestInfo new];
    requestInfo.clientInfo = clientInfo;
    requestInfo.version = @"1";
    NSString *reqJsonStr = [requestInfo yy_modelToJSONString];
    NSString *clientJsonStr = [clientInfo yy_modelToJSONString];
    XCTAssertNotNil(reqJsonStr);
    XCTAssertNotNil(clientJsonStr);
    
    XCTAssert([clientInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    XCTAssert([requestInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    NSDictionary<NSString *, id> *mapperDict = [TDLogConfigRequestInfo performSelector:@selector(modelCustomPropertyMapper)];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([reqJsonStr containsString:value]);
    }
    
    // 1
    TDLogConfigColorCmdDetail *colorDetail = [TDLogConfigColorCmdDetail new];
    XCTAssert([colorDetail.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogConfigColorCmdDetail performSelector:@selector(modelCustomPropertyMapper)];
    NSString *colorDetailJsonStr = [colorDetail yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([colorDetailJsonStr containsString:value]);
    }
    
    TDLogConfigColorStateLongTerm *longTerm = [TDLogConfigColorStateLongTerm new];
    XCTAssert([longTerm.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogConfigColorStateLongTerm performSelector:@selector(modelCustomPropertyMapper)];
    NSString *longTermJsonStr = [longTerm yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([longTermJsonStr containsString:value]);
    }
    
    // 2
    TDLogConfigColorInfo *colorInfo = [TDLogConfigColorInfo new];
    colorInfo.colorDetail = colorDetail;
    colorInfo.colorStateLongTerm = longTerm;
    XCTAssert([colorInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogConfigColorInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *colorInfoJsonStr = [colorInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([colorInfoJsonStr containsString:value]);
    }
    
    // 3
    TDLogConfigPullLogCmdDetailInfo *pullDetail = [TDLogConfigPullLogCmdDetailInfo new];
    pullDetail.specificPaths = @[@"1", @"2"];
    XCTAssert([pullDetail.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogConfigPullLogCmdDetailInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *pullDetailJsonStr = [pullDetail yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([pullDetailJsonStr containsString:value]);
    }
    
    // 4
    TDLogConfigPullLogInfo *pullLogInfo = [TDLogConfigPullLogInfo new];
    pullLogInfo.pullCmdInfos = @[pullDetail];
    XCTAssert([pullLogInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogConfigPullLogInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *pullLogInfoJsonStr = [pullLogInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([pullLogInfoJsonStr containsString:value]);
    }
    
    TDLogConfigResponseInfo *responseInfo = [TDLogConfigResponseInfo new];
    responseInfo.colorInfo = colorInfo;
    responseInfo.pullLogInfo = pullLogInfo;
    responseInfo.version = @"1";
    responseInfo.retMsg = @"test";
    
    XCTAssert([responseInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogConfigResponseInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *rspInfoJsonStr = [responseInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([rspInfoJsonStr containsString:value]);
    }
    
}

- (void)testConfigStatusSyncModels {
    TDLogConfigPullLogCmdDetailInfo *pullDetail = [TDLogConfigPullLogCmdDetailInfo new];
    pullDetail.specificPaths = @[@"1", @"2"];
    TDLogStatusPullLogCmdInfo *pullCmdInfo = [TDLogStatusPullLogCmdInfo infoFromPullLogDetailInfo:pullDetail];
    XCTAssertNil([TDLogStatusPullLogCmdInfo infoFromPullLogDetailInfo:nil]);
    
    TDLogConfigColorInfo *colorInfo = [TDLogConfigColorInfo new];
    TDLogConfigColorCmdDetail *colorDetail = [TDLogConfigColorCmdDetail new];
    colorInfo.colorDetail = colorDetail;
    TDLogStatusColorLogCmdInfo *colorCmdInfo = [TDLogStatusColorLogCmdInfo infoFromColorConfigInfo:colorInfo];
    XCTAssertNil([TDLogStatusColorLogCmdInfo infoFromColorConfigInfo:nil]);
    
    TDLogUpdateConfigStatusRequestInfo *reqInfo = [TDLogUpdateConfigStatusRequestInfo new];
    reqInfo.clientInfo = [TDLogRequestCommon clientInfoWithGuid:@"testGUID"];
    reqInfo.pullLogCmdInfos = @[pullCmdInfo];
    reqInfo.colorLogCmdInfo = colorCmdInfo;
    XCTAssert([reqInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    NSDictionary *mapperDict = [TDLogUpdateConfigStatusRequestInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *jsonStr = [reqInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([jsonStr containsString:value]);
    }
    
    TDLogUpdateConfigStatusResponseInfo *rspInfo = [TDLogUpdateConfigStatusResponseInfo new];
    rspInfo.retMsg = @"test";
    XCTAssert([rspInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogUpdateConfigStatusResponseInfo performSelector:@selector(modelCustomPropertyMapper)];
    jsonStr = [rspInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([jsonStr containsString:value]);
    }
}

- (void)testUploadStatusSyncModels {
    TDLogUploadStatusRequestInfo *reqInfo = [TDLogUploadStatusRequestInfo new];
    reqInfo.clientInfo = [TDLogRequestCommon clientInfoWithGuid:@"testGUID"];
    
    TDLogStatusPullLogCmdInfo *pullCmdInfo = [TDLogStatusPullLogCmdInfo new];
    reqInfo.pullLogCmdInfo = pullCmdInfo;
    
    TDLogUploadStatusAutoLogInfo *autoInfo = [TDLogUploadStatusAutoLogInfo new];
    autoInfo.label = @"testLabel";
    reqInfo.autoLogInfo = autoInfo;
    
    reqInfo.pubKeyMd5 = @"testMd5";
    reqInfo.cosUrl = @"testUrl";
    reqInfo.failReason = @"test";
    reqInfo.extInfo = @"testExt";
    
    XCTAssert([reqInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    NSDictionary *mapperDict = [TDLogUploadStatusRequestInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *jsonStr = [reqInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([jsonStr containsString:value]);
    }
    
    TDLogUploadTmpCosSecretInfo *cosInfo = [TDLogUploadTmpCosSecretInfo new];
    cosInfo.tmpSecretId = @"tmpID";
    XCTAssertFalse(cosInfo.isValid);
    cosInfo.tmpSecretKey = @"key";
    XCTAssertFalse(cosInfo.isValid);
    cosInfo.xcosSecurityToken = @"token";
    XCTAssertFalse(cosInfo.isValid);
    cosInfo.expiredTime = (uint32_t)time(0) + 1800;
    XCTAssertTrue(cosInfo.isValid);
    
    TDLogUploadStatusResponseInfo *rsp = [TDLogUploadStatusResponseInfo new];
    rsp.retMsg = @"1";
    rsp.cosUploadUrl = @"2";
    rsp.cosSecretInfo = cosInfo;
    
    XCTAssert([rsp.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    NSDictionary *rspMapperDict = [TDLogUploadStatusResponseInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *rspJsonStr = [rsp yy_modelToJSONString];
    for (NSString *value in rspMapperDict.allValues) {
        XCTAssertTrue([rspJsonStr containsString:value]);
    }
}

- (void)testCOSUploadModels {
    TDLogCOSUploadTaskInfo *cosUploadModel = [TDLogCOSUploadTaskInfo new];
    XCTAssert([cosUploadModel.class respondsToSelector:@selector(modelContainerPropertyGenericClass)]);
    NSDictionary *mapperDict = [TDLogCOSUploadTaskInfo performSelector:@selector(modelContainerPropertyGenericClass)];
    NSString *cosUploadJsonStr = [cosUploadModel yy_modelToJSONString];
    for (NSString *value in mapperDict.allKeys) {
        XCTAssertTrue([cosUploadJsonStr containsString:value]);
    }
    
    TDLogCosMultipartInfo *partInfo = [TDLogCosMultipartInfo new];
    partInfo.partNumber = @"1";
    partInfo.eTag = @"test";
    XCTAssert([partInfo.class respondsToSelector:@selector(modelCustomPropertyMapper)]);
    mapperDict = [TDLogCosMultipartInfo performSelector:@selector(modelCustomPropertyMapper)];
    NSString *partInfoJsonStr = [partInfo yy_modelToJSONString];
    for (NSString *value in mapperDict.allValues) {
        XCTAssertTrue([partInfoJsonStr containsString:value]);
    }
    
    [cosUploadModel.uploadedPartInfos addObject:partInfo];
    NSString *cosUploadModelJson = [cosUploadModel yy_modelToJSONString];
    XCTAssert(cosUploadModelJson.length > 0);
    
    TDLogCOSUploadTaskInfo *info2 = [TDLogCOSUploadTaskInfo yy_modelWithJSON:cosUploadModelJson];
    XCTAssert([info2.uploadedPartInfos isKindOfClass:NSMutableArray.class]);
    XCTAssert(info2.uploadedPartInfos.count == 1);
    XCTAssert([info2.uploadedPartInfos.firstObject isKindOfClass:TDLogCosMultipartInfo.class]);
    XCTAssert([info2.uploadedPartInfos.firstObject.partNumber isEqualToString:partInfo.partNumber]);
    
    TDLogCosFileOffsetBody *offset = [[TDLogCosFileOffsetBody alloc] initWithFile:[NSURL URLWithString:@"1"]
                                                                           offset:2 slice:3];
    XCTAssertNotNil(offset);
    XCTAssert([offset.fileURL.absoluteString isEqualToString:@"1"]);
    XCTAssert(offset.offset == 2);
    XCTAssert(offset.sliceLength == 3);
}

- (void)testConfigPullTask {
    TDLogConfigPullTask *pullTask = [TDLogConfigPullTask new];
    pullTask.requestId = @"test1";
    pullTask.requestGuid = @"testGUID";
    XCTAssert([pullTask.description containsString:pullTask.requestId]);
}

- (void)testUploadTaskModel {
    NSString *testRelativePath = @"/tmp/test1.txt";
    NSString *testFilePath = [NSHomeDirectory() stringByAppendingPathComponent:testRelativePath];
    NSString *testGuid = @"testGUID";
    TDLogUploadTaskModel *taskModel = [TDLogUploadTaskModel modelWithType:TDLogUploadType_Auto
                                                                 filePath:testFilePath
                                                                  andGuid:testGuid];
    XCTAssert(![taskModel.filePath containsString:NSHomeDirectory()]);
    XCTAssert([taskModel.filePath isEqualToString:testRelativePath]);
    
    TDLogUploadTaskModel *taskModel2 = [TDLogUploadTaskModel modelWithType:TDLogUploadType_Pull
                                                                 filePath:testRelativePath
                                                                  andGuid:testGuid];
    XCTAssert([taskModel2.filePath isEqualToString:testRelativePath]);
    
    XCTAssert([taskModel.description containsString:testRelativePath]);
    XCTAssert(taskModel.state == TDLogUploadTaskState_Init);
    XCTAssert(taskModel.startTime > 0);
    XCTAssert(taskModel.stepEndTime > 0);
    XCTAssert([taskModel.guid isEqualToString:testGuid]);
    XCTAssert(taskModel.uploadType == TDLogUploadType_Auto);
    XCTAssert(taskModel2.uploadType == TDLogUploadType_Pull);
}


@end
