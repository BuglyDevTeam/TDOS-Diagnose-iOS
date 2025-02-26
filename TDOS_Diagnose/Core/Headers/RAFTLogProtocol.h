//
//  RAFTLogProtocol.h
//
//  Created by RAFT on 2021/5/10.
//

#ifndef RAFTLogProtocol_h
#define RAFTLogProtocol_h

#import "RAFTLogDef.h"

@protocol RAFTLogProtocol <NSObject>

/*! @brief 记日志
 *
 *  @param tag 自定义tag
 *  [level][time][][tag][file, func, line][msg
 */
- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
        msg:(NSString *)msg, ... NS_REQUIRES_NIL_TERMINATION;

/*! @brief 记日志
 *
 *  @param tags 多tag数组
 *  [level][time][][tag][file, func, line][msg
 */
- (void)log:(RAFTLogLevel)level
        tags:(NSArray<NSString *> *)tags
       file:(const char *)file
       func:(const char *)func
       line:(int)line
        msg:(NSString *)msg, ... NS_REQUIRES_NIL_TERMINATION;

/*! @brief 设置打印log的级别
 *  @param level level
 */
- (void)setLogLevel:(RAFTLogLevel)level;

/*! @brief 强制写入日志到文件
 *
 */
- (void)flushLog;

@end
#endif /* RAFTLogProtocol_h */
