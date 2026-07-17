//
//  RAFTNetworkProtocol.h
//  RAFTelivery
//
//  Created by jeannieliu(刘锦) on 2021/9/18.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, RAFTNetworkStatus) {
    RAFTNetworkStatusNone = 0,   // 无网络
    RAFTNetworkStatus2G,         // 2G
    RAFTNetworkStatus3G,         // 3G
    RAFTNetworkStatus4G,         // 4G
    RAFTNetworkStatus5G,         // 5G
    RAFTNetworkStatusWIFI = 10   // WIFI
};

typedef void(^RAFTDownloadProgressBlock)(NSInteger receivedSize, NSInteger expectedSize);
typedef void(^RAFTDownloadCompletedBlock)(NSInteger httpStatusCode, NSError * _Nullable error);

@protocol RAFTDownloadTaskProtocol <NSObject>

/// 取消下载
- (BOOL)cancel;

@end

@protocol RAFTDownloadProtocol <NSObject>

/// 获取当前网络状态
- (RAFTNetworkStatus)networkStatus;

/// 文件下载
/// @param urlString 请求地址
/// @param filePath 指定文件下载路径
/// @param progressBlock 进度的回调
/// @param completedBlock 完成的回调
- (nullable id<RAFTDownloadTaskProtocol>)downloadWithUrl:(NSString *)urlString
                                                filePath:(NSString *)filePath
                                                progress:(nullable RAFTDownloadProgressBlock)progressBlock
                                               completed:(nullable RAFTDownloadCompletedBlock)completedBlock;
                          

@end

NS_ASSUME_NONNULL_END
