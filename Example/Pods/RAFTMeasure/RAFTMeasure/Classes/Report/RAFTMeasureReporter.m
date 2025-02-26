//
//  RAFTMeasureReporter.m
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import "RAFTMeasureReporter.h"
#import "RAFTMeasureDefines.h"
#import "RAFTMeasureLogger.h"
#import "RAFTMeasureVersion.h"
#import "RAFTMeasureUtils.h"

@implementation RAFTMeasureReporter

#pragma mark - 通用参数
- (NSDictionary *)commonParams {
    NSMutableDictionary *commonParams = [NSMutableDictionary dictionary];
    commonParams[RAFTMEASURE_PARAMKEY_ATTA_ID] = RAFTMEASURE_PARAMVAL_ATTA_APP_ID;
    commonParams[RAFTMEASURE_PARAMKEY_TOKEN] = RAFTMEASURE_PARAMVAL_ATTA_TOKEN;
    commonParams[RAFTMEASURE_PARAMKEY_TYPE] = RAFTMEASURE_PARAMVAL_BATCH;
    commonParams[RAFTMEASURE_PARAMKEY_VERSION] = RAFTMEASURE_PARAMVAL_VERSION_DEFAULT;
    commonParams[RAFTMEASURE_PARAMKEY_PLATFORM] = RAFTMEASURE_PARAMVAL_PLATFORM;
    commonParams[RAFTMEASURE_PARAMKEY_SDK_VER] = [RAFTMeasureUtils safeString:[RAFTMeasureVersion sdkVersion]];
    return commonParams;
}

#pragma mark - 发起上报
- (void)report:(id<RAFTMeasureReportParamProtocol>)reportItem {
    NSMutableDictionary *allParams = [NSMutableDictionary dictionary];
    // 添加通用参数
    [allParams addEntriesFromDictionary:[self commonParams]];
    // 添加reportItem里的参数
    if (reportItem && [reportItem respondsToSelector:@selector(reportParams)]) {
        [allParams addEntriesFromDictionary:[reportItem reportParams]];
    }
    [self reqPost:allParams];
}

- (void)reqPost:(NSDictionary *)allParams {
    [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s allParams = %@", __func__, allParams.description]];
    // 创建会话对象
    NSURLSession *session = [NSURLSession sharedSession];
    // 根据会话对象创建task
    NSURL *url = [NSURL URLWithString:RAFTMEASURE_ATTA_URL];
    // 创建可变的请求对象
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    // 修改请求方法为POST
    request.HTTPMethod = RAFTMEASURE_HTTP_METHOD_POST;
    // 设置超时时间
    request.timeoutInterval = RAFTMEASURE_HTTP_TIMEOUT;
    // 设置请求头
    [request setValue:RAFTMEASURE_HTTPVAL_ATTA_TYPE forHTTPHeaderField:RAFTMEASURE_HTTPKEY_BATCH_REPORT];
    [request setValue:RAFTMEASURE_HTTPVAL_TEXT_PLAIN_CHARSET_UTF_8 forHTTPHeaderField:RAFTMEASURE_HTTPKEY_CONTENT_TYPE];
    // 设置请求体
    NSMutableString *bodyString = [NSMutableString string];
    [allParams enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        [bodyString appendFormat:@"&%@=%@", key, obj];
    }];
    request.HTTPBody = [bodyString dataUsingEncoding:NSUTF8StringEncoding];
    // 根据会话对象创建一个Task(发送请求）
    NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:request
                                                completionHandler:^(NSData * _Nullable data,
                                                                    NSURLResponse * _Nullable response,
                                                                    NSError * _Nullable error) {
        if (response) {
            [[RAFTMeasureLogger sharedInstance] raftMeasureDebugLog:[NSString stringWithFormat:@"%s response = %@", __func__, response.description]];
        }
        if (error) {
            [[RAFTMeasureLogger sharedInstance] raftMeasureWarnLog:[NSString stringWithFormat:@"%s error = %@", __func__, error.description]];
        }
    }];
    // 执行任务
    [dataTask resume];    
}

@end
