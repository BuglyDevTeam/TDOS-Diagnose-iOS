//   
//  RFKTManager+MainPanel.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/19.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTManager.h"
#import "RFKTMainPanelSection.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKTManager (MainPanel)

#pragma mark - MainPanel DataSource

/// Main panel's sections, sort by section's \c sectiionType and \c displayPriority property
- (NSArray<RFKTMainPanelSection *> *)getSortedMainPanelSections;

/// Get the Visible Plugins Array in section
/// @param index the index of the section in main panel
- (NSArray *)getVisiblePluginsInSectionIndex:(NSInteger)index;

/// Get the Visible Plugins with given indexpath
/// @param indexPath section,row
- (NSObject <RFKTPlugin> *)getVisiblePluginWithIndexPath:(NSIndexPath *)indexPath;

/// The top section of MainPanel, include set-tops and recent-used
- (NSArray<NSObject<RFKTPlugin> *> *)getTopShowSectionPlugins;

/// Add to Top-Show Section
/// @param plugin plugin to be added.
- (void)addPluginToRecentListIfNecessary:(NSObject<RFKTPlugin> *)plugin;

/// Save custom data of MainPanel
- (void)saveMainPanelUserDefinedData;

/// Restore custom data of MainPanel
- (void)restoreMainPanelUserDefinedData;

#pragma mark - Other

/// Gets the corresponding tint color based on the type
/// @param type plugin'type
- (UIColor *)tintColorWithPluginType:(RFKTPluginType)type;

@end

NS_ASSUME_NONNULL_END
