//
//  RAFTNetworkProtocol.h
//  RAFTelivery
//
//  Created by jeannieliu(刘锦) on 2021/7/27.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^RAFTRequestCompletedBlock)(NSData * _Nullable responseObject, NSInteger httpStatusCode, NSError * _Nullable error);

/// 网络协议
typedef NSString *RAFTNetworkHttpMethod NS_STRING_ENUM;

static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodOPTIONS = @"OPTIONS";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodHEAD = @"HEAD";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodGET = @"GET";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodPOST = @"POST";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodPUT = @"PUT";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodDELETE = @"DELETE";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodTRACE = @"TRACE";
static RAFTNetworkHttpMethod const RAFTNetworkHttpMethodCONNECT = @"CONNECT";

@protocol RAFTHttpRequestProtocol <NSObject>
/// 请求地址
- (NSString *)requestUrl;

/// method 方法，GET、HEAD、POST、OPTIONS、PUT、DELETE、TRACE、CONNECT
- (RAFTNetworkHttpMethod)requestMethod;

/// 请求的超时时间
- (NSTimeInterval)timeout;

/// 请求的缓存策略
- (NSURLRequestCachePolicy)requestCachePolicy;

/// 请求参数
- (nullable NSDictionary *)parameters;

/// 请求的body体
- (nullable NSData *)httpBody;

/// 请求的header值
- (nullable NSDictionary<NSString *, NSString *> *)headerFields;
@end


/// 网络库
@protocol RAFTNetworkProtocol <NSObject>

/// 发送HTTP请求
/// @param request 请求体
/// @param completedBlock 完成的回调
- (void)sendRequest:(id<RAFTHttpRequestProtocol>)request
          completed:(nullable RAFTRequestCompletedBlock)completedBlock;

@end

NS_ASSUME_NONNULL_END
