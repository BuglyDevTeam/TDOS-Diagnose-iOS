//
//  TDLogUploadFileFilterProtocol.h
//  VBLogUploadiOS
//
//  Created by jerrypsong on 2021/3/16.
//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol TDLogUploadFileFilterProtocol <NSObject>
/**
 filePath的文件是否符合匹配规则
*/
- (BOOL)isMatch:(NSString *)filePath;

@end

NS_ASSUME_NONNULL_END
