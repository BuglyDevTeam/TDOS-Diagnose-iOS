//   
//  RFKTPlugin.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/15.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#ifndef RFKTPLUGIN_H
#define RFKTPLUGIN_H

#import <UIKit/UIKit.h>
#import "RFKTConnection.h"

typedef NS_ENUM(NSUInteger, RFKTPluginType) {
    RFKTPluginTypeCustom,
    RFKTPluginTypeCommon,
    RFKTPluginTypePerf,
    RFKTPluginTypeUI,
    RFKTPluginTypePlatform,
    RFKTPluginTypeSimu,
};

typedef NS_ENUM(NSUInteger, RFKTBuiltinPlugin) {
    // Common
    RFKTBuiltinPlugin_AppInfo,
    RFKTBuiltinPlugin_InfoPlist,
    RFKTBuiltinPlugin_UserDefaults,
    RFKTBuiltinPlugin_Sandbox,
    RFKTBuiltinPlugin_HttpCapture,
    RFKTBuiltinPlugin_NSLog,
    RFKTBuiltinPlugin_LogFilter,
    RFKTBuiltinPlugin_DBViewer,
    RFKTBuiltinPlugin_TraceLog,
    RFKTBuiltinPlugin_CallTrace,
    // UI
    RFKTBuiltinPlugin_ColorPicker,
    RFKTBuiltinPlugin_UIChecker,
    RFKTBuiltinPlugin_ViewDistance,
    RFKTBuiltinPlugin_ImagePath,
    RFKTBuiltinPlugin_CurrentVC,
    RFKTBuiltinPlugin_SlowAnimation,
    RFKTBuiltinPlugin_ScreenRecorder,
    // Perf
    RFKTBuiltinPlugin_ResourceMonitor,
    RFKTBuiltinPlugin_StuckMonitor,
    RFKTBuiltinPlugin_MemoryMonitor,
    RFKTBuiltinPlugin_LoadMonitor,
    RFKTBuiltinPlugin_SubthreadUIMonitor,
    RFKTBuiltinPlugin_CrashMonitor,
    RFKTBuiltinPlugin_ThreadCreateMonitor,
    // Simu
    RFKTBuiltinPlugin_SimuLocation,
    RFKTBuiltinPlugin_SimuWeakNet,
    RFKTBuiltinPlugin_SimuPush,
};

NS_ASSUME_NONNULL_BEGIN

@protocol RFKTPlugin

#pragma mark - BasicInfo

/// The plugin's identifier.
- (NSString *)identifier;

/// The plugin's name to display in panel.
- (NSString *)displayName;

/// The plugin's icon,
/// if return null, an image with text in middle will be displayed.
- (nullable UIImage *)iconImg;

/// The plugin's type
- (RFKTPluginType)type;

@optional

#pragma mark - MainPanel
/// Plugin's display priority in section, smallest first
- (NSUInteger)displayPriority;

/// Custom section name of main panel
- (NSString *)customSectionName;

/// Custom section's display priority, biggest first
- (NSUInteger)customSectionPriority;

/// The plugin's detail description to display in panel
- (nullable NSString *)detailText;

/// The plugin's native UI ViewController
- (Class)localUIEntrance;

/// Called when plugin's cell is clicked
- (void)didClickEntranceOnViewController:(UIViewController *)vc;

/// Returns true if the plugin is meant to be run in background too, otherwise it returns false.
- (BOOL)runInBackground;

/// An alternative to \c detailText , used to show functional status.
///  return YES if funtion is running, otherwise NO.
- (BOOL)runningStatus;

#pragma mark - LifeCycle

/// Called when RaftKit init
- (void)pluginDidInstall;

/// Called when app will terminate.
- (void)onAppWillTerminate;

#pragma mark - Remote LifeCycle

/// Called when a connection has been established between this plugin and
/// the corresponding display part on "the remote".
/// We can treat the local UI as a remote! So "connect" means "enter foreground" in this case.
- (void)onRemoteConnect:(id<RFKTConnection>)connection;

/// Called when a plugin has been disconnected.
- (void)onRemoteDisconnect;

@end

NS_ASSUME_NONNULL_END

#endif /* RFKTPLUGIN_H */

