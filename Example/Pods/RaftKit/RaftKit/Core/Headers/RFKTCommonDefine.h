//
//  RFKTCommonDefine.h
//  RFKT
//
//  Created by selmerzhang on 2021/3/22.
//  Copyright © 2021 RaftKit Team. All rights reserved.

#ifndef RFKTCommonDefine_h
#define RFKTCommonDefine_h

#import "RFKTUtility.h"
#import <TargetConditionals.h>

#ifndef RFKT_ENABLE_REMOTECONNECTION
#define RFKT_ENABLE_REMOTECONNECTION    1
#endif /* RFKT_ENABLE_REMOTECONNECTION */

#ifndef RFKT_ENABLE_LOADMONITOR_PLUGIN
#define RFKT_ENABLE_LOADMONITOR_PLUGIN    1
#endif /* RFKT_ENABLE_LOADMONITOR_PLUGIN */

#pragma mark - Plugin Regist

#ifndef RFKT_PLUGINNAME_SECTION
#define RFKT_PLUGINNAME_SECTION "__rfkt_plgns"
#endif

#include <mach-o/loader.h>
#define RFKT_REGIST_PLUGIN(PLUGIN_NAME) \
__attribute((used, section("" SEG_DATA "," RFKT_PLUGINNAME_SECTION " "), no_sanitize("address"))) \
static char * kRFKT_PLUGIN_##PLUGIN_NAME = ""#PLUGIN_NAME"";


#define rfkt_plugin_imp(RFKT_PLUGIN) \
implementation RFKT_PLUGIN \
RFKT_REGIST_PLUGIN(RFKT_PLUGIN)


#pragma mark -  i18n

__attribute__((annotate("returns_localized_nsstring")))
static inline NSString *rfktL10nNotNeeded(NSString *s) { return s;}

#define RFKTLocalized(string) [RFKTUtility localizedString:string]
#define RFKTNNLocalized(string) rfktL10nNotNeeded(string)


#pragma mark - Clang Warnings

#define RFKT_ArgumentToString(macro) #macro
#define RFKT_ClangWarningConcat(warning_name) RFKT_ArgumentToString(clang diagnostic ignored warning_name)

/// warning list ref:https://clang.llvm.org/docs/DiagnosticsReference.html
#define RFKT_IGNORE_WARNING_BEGIN(warningName) _Pragma("clang diagnostic push") _Pragma(RFKT_ClangWarningConcat(#warningName))
#define RFKT_IGNORE_WARNING_END _Pragma("clang diagnostic pop")

#define RFKTBeginIgnorePerformSelectorLeaksWarning RFKT_IGNORE_WARNING_BEGIN(-Warc-performSelector-leaks)
#define RFKTEndIgnorePerformSelectorLeaksWarning RFKT_IGNORE_WARNING_END


#endif /* RFKTCommonDefine_h */
