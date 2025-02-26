//   
//  RFKTDataReport.h
//  RaftKit
//  
//  Created by raycgwang on 2021/5/28.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    RFKTReportPluginAction_EntryClick = 0x201,
    RFKTReportPluginAction_UsedTime = 0x202,
    RFKTReportPluginAction_InUse = 0x203,
    RFKTReportPluginAction_EffectivelyUsed = 0x204,
    RFKTReportPluginAction_Trigger = 0x301,
    RFKTReportPluginAction_Alert = 0x302,
    RFKTReportPluginAction_ClickDetail = 0x303,
    RFKTReportPluginAction_Share = 0x304,
} RFKTReportPluginAction;

/// RaftKit DataReport
@interface RFKTDataReport : NSObject

+ (instancetype)sharedInstance;

/// Report for bugly
+ (void)setupSDKInfoForBuglyReport;

/// SLA Startup Report
/// @param startup_cost 启动耗时（ms）
/// @param startup_result 启动结果（0/1）
+ (void)reportStartupInfoToATTA:(long)startup_cost startup_result:(long)startup_result;


#pragma mark - Other Business Report

/// Report use info to ATTA
/// @param code long
/// @param status long
/// @param cost long
+ (void)reportToATTAWithBizCode:(long)code status:(long)status cost:(long)cost;

/// Build extra params for report
/// @param extra1 long
/// @param extra2 long
/// @param extra3 str
/// @param extra4 str
/// @param params str
+ (NSString *)buildExtraParams:(long)extra1
                        extra2:(long)extra2
                        extra3:(nullable NSString *)extra3
                        extra4:(nullable NSString *)extra4
                     andParams:(nullable NSString *)params;

/// Report use info to ATTA, with full parameters
/// @param code long
/// @param status long
/// @param cost long
/// @param pluginId str
/// @param pluginType int
/// @param extraParams dic, built from \c buildExtraParams method
+ (void)reportToATTAWithBizCode:(long)code status:(long)status cost:(long)cost
                       pluginId:(nullable NSString *)pluginId pluginType:(int)pluginType
                 andExtraParams:(nullable NSString *)extraParams;


#pragma mark - Report with Time Measurement

/// Time measure report begin.
/// @param code business code
/// @param pluginId str
- (void)reportBizCodeBegin:(long)code plugin:(nullable NSString *)pluginId;

/// Time measure report end
- (void)reportBizCodeEnd:(long)code status:(long)status
                pluginId:(nullable NSString *)pluginId
          andExtraParams:(nullable NSString *)extraParams;

/// Plugin Use Time Report Begin
/// @param pluginId str
+ (void)reportPluginUseBegin:(NSString *)pluginId;

/// Plugin Use Time Report End
/// @param pluginId str
/// @param shouldReportEfftUsed bool
+ (void)reportPluginUseEnd:(NSString *)pluginId isEffectivelyUsed:(BOOL)shouldReportEfftUsed;

#pragma mark - Some Report Quick Methods

/// Plugin Click Report
/// @param pluginID str
/// @param pluginType long
/// @param isFromRecentSec from recent use section or not, bool
+ (void)reportPluginClick:(NSString *)pluginID pluginType:(long)pluginType isFromRecentSection:(BOOL)isFromRecentSec;

/// Plugin Effective Usage report
/// @param pluginID str
+ (void)reportPluginEffectiveUse:(NSString *)pluginID;

/// Plugin general action report
/// @param action enum
/// @param pluginID str
+ (void)reportPluginAction:(RFKTReportPluginAction)action identifier:(NSString *)pluginID;

/// Report plugin's in use state,
/// Quick method for \c RFKTReportPluginAction_InUse
/// @param pluginID str
+ (void)reportPluginInUseState:(NSString *)pluginID;

/// Do necessary report after plugin install
+ (void)doAfterPluginsInstallActionsIfNeeded;


@end

NS_ASSUME_NONNULL_END
