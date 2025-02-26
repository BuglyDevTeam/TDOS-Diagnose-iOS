//   
//  RFKTDataProvider.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/16.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#ifndef RFKTDataProvider_h
#define RFKTDataProvider_h

@protocol RFKTDataProviderDelegate <NSObject>

/// 数据源更新协议
/// @param dataSource 数据源
/// @param data 更新数据
- (void)dataSourceDidUpdate:(nonnull id)dataSource withData:(nullable id)data;

@end


/// 支持广播的数据源协议
@protocol RFKTBroadcastSourceProtocol <NSObject>

@required
/// Add a datasource listener
/// @param listener objectType
- (void)addListener:(nonnull id<RFKTDataProviderDelegate>)listener;

/// Remove a datasource listener
/// @param listener objectType
- (void)removeListener:(nonnull id<RFKTDataProviderDelegate>)listener;

@end

#endif /* RFKTDataProvider_h */
