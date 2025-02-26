//
//  RAFTLogDef.h
//
//  Created by RAFT on 2021/5/10.
//

#ifndef RAFTLogDef_h
#define RAFTLogDef_h

typedef NS_ENUM(NSInteger, RAFTLogLevel) {
    RAFTLogLevelAll = 0,
    RAFTLogLevelVerbose = 0,
    RAFTLogLevelDebug,
    RAFTLogLevelInfo,
    RAFTLogLevelWarn,
    RAFTLogLevelError,
    RAFTLogLevelFatal,
    RAFTLogLevelNone,
};

#endif
