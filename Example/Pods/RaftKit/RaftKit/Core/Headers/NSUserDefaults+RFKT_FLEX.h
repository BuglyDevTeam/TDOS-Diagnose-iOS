//
//  NSUserDefaults+RFKT_FLEX.h
//  FLEX
//
//  Created by Tanner on 3/10/20.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>

// Only use these if the getters and setters aren't good enough for whatever reason
extern NSString * const kRFKT_FLEXDefaultsToolbarTopMarginKey;
extern NSString * const kRFKT_FLEXDefaultsiOSPersistentOSLogKey;
extern NSString * const kRFKT_FLEXDefaultsHidePropertyIvarsKey;
extern NSString * const kRFKT_FLEXDefaultsHidePropertyMethodsKey;
extern NSString * const kRFKT_FLEXDefaultsHidePrivateMethodsKey;
extern NSString * const kRFKT_FLEXDefaultsShowMethodOverridesKey;
extern NSString * const kRFKT_FLEXDefaultsHideVariablePreviewsKey;
extern NSString * const kRFKT_FLEXDefaultsNetworkHostBlacklistKey;
extern NSString * const kRFKT_FLEXDefaultsDisableOSLogForceASLKey;
extern NSString * const kRFKT_FLEXDefaultsRegisterJSONExplorerKey;

/// All BOOL preferences are NO by default
@interface NSUserDefaults (RFKT_FLEX)

- (void)rfkt_flex_toggleBoolForKey:(NSString *)key;

@property (nonatomic) double rfkt_flex_toolbarTopMargin;

// Not actually stored in defaults, but written to a file
@property (nonatomic) NSArray<NSString *> *rfkt_flex_networkHostBlacklist;

/// Whether or not to register the object explorer as a JSON viewer on launch
@property (nonatomic) BOOL rfkt_flex_registerDictionaryJSONViewerOnLaunch;

/// Disable os_log and re-enable ASL. May break Console.app output.
@property (nonatomic) BOOL rfkt_flex_disableOSLog;
@property (nonatomic) BOOL rfkt_flex_cacheOSLogMessages;

@property (nonatomic) BOOL rfkt_flex_explorerHidesPropertyIvars;
@property (nonatomic) BOOL rfkt_flex_explorerHidesPropertyMethods;
@property (nonatomic) BOOL rfkt_flex_explorerHidesPrivateMethods;
@property (nonatomic) BOOL rfkt_flex_explorerShowsMethodOverrides;
@property (nonatomic) BOOL rfkt_flex_explorerHidesVariablePreviews;

@end
