//   
//  RFKTManager.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/22.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "RFKTPlugin.h"
#import "RFKTShakeTrigger.h"
#import "RFKTTapTrigger.h"
#import "RFKTLongPressTrigger.h"

@class UIWindowScene;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSString * const kRFKTFloatingBallSwitchKey;


@interface RFKTManager : NSObject

/// Run RaftKit!
/// 根据key=\c kRFKTFloatingBallSwitchKey 的NSUserDefaults配置来决定是否展示悬浮球，默认打开。
///
/// 注意：为避免手动隐藏悬浮球后无法显示入口，请使用\c setupWithTriggers: 自定义配置入口触发方式，
/// 或主动调用\c showFloatingBall ，此接口将显示悬浮球并保存此设置项。
///
+ (void)install;

/// Same to \c +install, but provided default value;
/// @param isOpen default open or not
+ (void)installWithDefault:(BOOL)isOpen;

#pragma mark -

/// The shared singleton RFKTManager instance
@property (nonatomic, readonly, class) RFKTManager * sharedInstance;

/// show raftkit's floating ball
- (void)showFloatingBallIfNeeded:(BOOL)isOpenForDefault;

/// show raftkit's floating ball, and store switch value
- (void)showFloatingBall;

/// hide raftkit's floating ball, and store switch value
- (void)hideFloatingBall;

/// floating ball status
- (BOOL)isFloatingBallShowing;

/// present the main panel
- (void)showMainPanel;

/// present the main panel in a specific scene
/// @param scene the scene you wish to display the panel
- (void)showMainPanelFromScene:(nullable UIWindowScene *)scene API_AVAILABLE(ios(13.0));

/// setup entry trigger, there are 3 types of trigger: RFKTShakeTrigger, RFKTTapTrigger, RFKTLongPressTrigger
- (void)setupWithTriggers:(NSArray<id<RFKTEntryTrigger>> *)triggers;

/// get current entry triggers
- (nullable NSArray<id <RFKTEntryTrigger>> *)getFloatingBallTriggers;

#pragma mark - Plugins Manager

/// Add Custom Plugin
/// @param plugin RFKTPlugin object
- (void)addPlugin:(NSObject <RFKTPlugin> *)plugin;

/// Remove Custom Plugin
/// @param pluginID RFKTPlugin identifier
- (void)removePluginWithIdentifier:(NSString *)pluginID;

/// All plugins
- (NSArray<NSObject <RFKTPlugin> *> *)allPlugins;

/// All plugins with given type
- (NSArray<NSObject <RFKTPlugin> *> *)allPluginsWithType:(RFKTPluginType)type;

/// Get Plugin with identifier
/// @param identifier plugin's identifier
- (nullable NSObject <RFKTPlugin> *)pluginWithIdentifier:(NSString *)identifier;


#pragma mark - Statistical analysis

/// Set a custom user ID to distinguish users
/// @param uid A unique ID, such as QMEI,uin,etc
///
/// Only valid in real device, unavailable in simulator.
- (void)setUniqueUserID:(NSString *)uid;

@end

NS_ASSUME_NONNULL_END
