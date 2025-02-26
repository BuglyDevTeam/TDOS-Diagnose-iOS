//
//  TDIAGAppDelegate.h
//  TDiagnose
//
//  Created by raycgwang on 12/10/2021.
//  Copyright (c) 2021 raycgwang. All rights reserved.
//

@protocol TDLoggingIMPProtocol;

@interface TDIAGAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

/// 设备唯一ID
@property (nonatomic, strong) NSString *deviceId;

/// 日志子实例
@property (nonatomic, strong) id<TDLoggingIMPProtocol> subLogger;

@end
