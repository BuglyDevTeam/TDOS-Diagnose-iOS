//   
//  TDIAGDepends.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/23.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "TDIAGDependProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface TDIAGDepends : NSObject <TDIAGDependProtocol>

/// create a depends instance
+ (instancetype)dependsWithLogImp:(id<TDLoggingIMPProtocol>)logImp
                     kvFactoryImp:(id<RAFTKVStorageFactoryProtocol>)kvFactoryImp
                 andFilePackerImp:(id<TDLogFilePackerProtocol>)filePackerImp;


/// Use \c +dependsWithLogImp: to initialize
- (instancetype)init NS_UNAVAILABLE;

/// Use \c +dependsWithLogImp: to initialize
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
