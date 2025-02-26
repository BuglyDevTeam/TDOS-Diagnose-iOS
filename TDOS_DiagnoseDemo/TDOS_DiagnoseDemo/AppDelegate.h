//
//  AppDelegate.h
//  TDOS_DiagnoseDemo
//
//  Created by Hongbo Cui on 2025/2/25.
//

#import <UIKit/UIKit.h>

@protocol TDLoggingIMPProtocol;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

/// 设备唯一ID
@property (nonatomic, strong) NSString *deviceId;

/// 日志子实例
@property (nonatomic, strong) id<TDLoggingIMPProtocol> subLogger;

@end

