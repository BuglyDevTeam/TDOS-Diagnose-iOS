//   
//  TDLogCosFileOffsetBody.h
//  TDiagnose
//  
//  Created by raycgwang on 2022/1/5.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface TDLogCosFileOffsetBody : NSObject

/// 文件路径
@property (nonatomic, strong, readonly) NSURL *fileURL;
/// 偏移
@property (nonatomic, assign, readonly) NSUInteger offset;
/// 分片大小
@property (nonatomic, assign, readonly) NSUInteger sliceLength;
/// 分片序号
@property (nonatomic, assign) NSUInteger index;

/// 初始化文件上传分片信息
- (instancetype)initWithFile:(NSURL *)fileURL offset:(NSUInteger)offset slice:(NSUInteger)slice;

@end


NS_ASSUME_NONNULL_END
