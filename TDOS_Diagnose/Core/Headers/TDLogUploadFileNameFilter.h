//
//  TDLogUploadFileNameFilter.h
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/18.
//  Copyright © 2021 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TDLogUploadFileFilterProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface TDLogUploadFileNameFilter : NSObject <TDLogUploadFileFilterProtocol>

//筛选文件名的正则表达式
@property (nonatomic, copy) NSString *mFileNameRegex;

/**
初始化VBLogUploadFileNameFilter实例
@param mFileNameRegex 筛选文件名的正则表达式
@return VBLogUploadFileNameFilter实例
*/
- (instancetype)initWithFileNameRegex:(NSString *)mFileNameRegex;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
