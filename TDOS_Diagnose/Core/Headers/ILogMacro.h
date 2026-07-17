//
//  ILogMacro.h
//  RaftDemo
//
//  Created by RAFT on 2021/4/14.
//  Copyright © 2021 Tencent. All rights reserved.
//

/*===========这里接口会耦合RAFT，后续这里调整增加特别说明。先屏蔽这部分代码===========
#import <RAFT/RAFT.h>

#ifndef ILogMacro_h
#define ILogMacro_h


#define ILog(level, tag_name, format, ...) \
    do { \
        id<ILogProtocol> logger = [RAServiceManager.shared serviceForKey:@protocol(ILogProtocol)]; \
        [logger log:level tag:tag_name file:__FILE__ func:__func__ line:__LINE__ msg:format, ##__VA_ARGS__, nil]; \
    } while (0)


#define ILogError(tag, format, ...) ILog(ILogLevel_Error, tag, format, ##__VA_ARGS__)
#define ILogWarn(tag, format, ...) ILog(ILogLevel_Warn, tag, format, ##__VA_ARGS__)
#define ILogInfo(tag, format, ...) ILog(ILogLevel_Info, tag, format, ##__VA_ARGS__)
#define ILogDebug(tag, format, ...) ILog(ILogLevel_Debug, tag, format, ##__VA_ARGS__)
#define ILogFatal(tag, format, ...) ILog(ILogLevel_Fatal, tag, format, ##__VA_ARGS__)


#endif /* ILogMacro_h */
