//
//  TDLogUploadFileTimeFilter.h
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/17.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDLogUploadFileFilterProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface TDLogUploadFileTimeFilter : NSObject <TDLogUploadFileFilterProtocol>

//筛选的开始日期时间戳
@property (nonatomic, assign) NSTimeInterval startTime;
//筛选的结束日期时间戳
@property (nonatomic, assign) NSTimeInterval endTime;

/**
初始化VBLogUploadFileTimeFilter实例
@param startTime 筛选的开始日期的时间戳
@param endTime 筛选的结束日期的时间戳
@return VBLogUploadFileTimeFilter实例
*/
- (instancetype)initWithStartTime:(NSTimeInterval)startTime endTime:(NSTimeInterval)endTime;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
