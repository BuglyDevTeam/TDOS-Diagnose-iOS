//   
//  TDIAGDependProtocol.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/23.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#ifndef RDIAGDependProtocol_h
#define RDIAGDependProtocol_h

#import "TDLoggingIMPProtocol.h"
#import "RAFTKVStorageFactoryProtocol.h"
#import "TDLogFilePackerProtocol.h"

@protocol TDIAGDependProtocol <NSObject>

/// 日志组件实现类
@property (nonatomic, strong) id<TDLoggingIMPProtocol> logImpl;

/// KV存储组件实现类
@property (nonatomic, strong) id<RAFTKVStorageFactoryProtocol> kvFactoryImpl;

/// 文件打包实现
@property (nonatomic, strong) id<TDLogFilePackerProtocol> filePackerImpl;


#pragma mark - 日志多实例支持

/// 注册日志子实例，以支持捞取该实例的日志文件
/// Registers log instances to support retrieving log files for that instance
/// @param subLogger 其他日志实例
- (void)registSubLogger:(id<TDLoggingIMPProtocol>)subLogger;

/// 获取所有的日志实例
- (NSArray<id<TDLoggingIMPProtocol>> *)getAllLoggerInstances;

@end

#endif /* RDIAGDependProtocol_h */
