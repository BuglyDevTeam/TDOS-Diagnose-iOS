//
//  RFKTResourceMonitorPlugin.h
//  RaftKit
//
//  Created by selmerzhang on 2021/4/6.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#ifndef RFKTResourceMonitorPlugin_h
#define RFKTResourceMonitorPlugin_h

#import "RFKTPlugin.h"

/// 资源浮窗自定义数据的通知，object参数中添加的自定义字符串，将展示在资源浮窗中。
FOUNDATION_EXTERN NSString * const kRFKTCustomResourceDataUpdate;

/// 资源监控插件
@interface RFKTResourceMonitorPlugin : NSObject <RFKTPlugin>

@end


#endif /* RFKTResourceMonitorPlugin_h */
