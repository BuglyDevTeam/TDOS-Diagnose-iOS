//
//  TDOSLogger.m
//  TDOS-Diagnose
//
//  Created by raycgwang on 2022/1/11.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//
//  Derived from RFLLogger

#import "TDOSLogger.h"
#import <mars/xlog/xlogger_interface.h>
#import <sys/xattr.h>
#import "TDLogUploadFileFinder.h"
#import "TDLogUploadFileTimeFilter.h"
#import "TDIAUtil.h"
#import <TargetConditionals.h>


#define TDOS_LOG_PREFIX "TDOSLog"
#define TDOS_TAG_INTERNAL @"TDiagnose"
NSString * const TDOSLogColorInfoKey = @"TDOS_LOG_COLOR_INFO_KEY"; // 日志染色信息
NSString * const TDOSLogColorEndTimeKey = @"TDOS_LOG_COLOR_ENDTIME_KEY"; // 日志染色结束时间
NSString * const TDOSLogColorLevelKey = @"TDOS_LOG_COLOR_LEVEL_KEY"; // 日志染色级别


@interface TDOSLoggerConfig ()

/// 日志目录
@property (nonatomic, copy) NSString *logPath;
/// 默认日志级别，默认RAFTLogLevel_Error
@property (nonatomic, assign) RAFTLogLevel defaultLogLevel;
/// 加密Key
@property (nonatomic, copy) NSString *publicKey;

@end

@implementation TDOSLoggerConfig

- (instancetype)init {
    self = [super init];
    if (self) {
        _logPath = [self.class defaultLogPath];
        _enableConsoleLog = NO;
        _defaultLogLevel = RAFTLogLevelError;
        _logFilePrefix = @TDOS_LOG_PREFIX;
    }
    return self;
}

+ (instancetype)defaultConfig {
    return [[self alloc] init];
}

+ (instancetype)configWithLogPath:(NSString *)logPath
                        logPrefix:(nonnull NSString *)logPrefix
                     defaultLevel:(RAFTLogLevel)level
                     andPublicKey:(NSString *)pubKey {
    TDOSLoggerConfig *config = [TDOSLoggerConfig new];
    if (logPath.length > 0) {
        config.logPath = logPath;
        config.defaultLogLevel = level;
        config.publicKey = pubKey;
        if (logPrefix.length > 0) {
            config.logFilePrefix = logPrefix;
        }
        return config;
    }
    return nil;
}

+ (NSString *)defaultLogPath {
    return [[NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0]
            stringByAppendingString:@"/Caches/TDOSLog"];
}

@end


@interface TDOSLogger () {
    std::atomic<uint64_t> _logIndex; //log index for current life cycle
}

/// config for TDOSLogger
@property (nonatomic, strong) TDOSLoggerConfig *config;

/// pointer to xlog instance
@property (nonatomic, assign) uintptr_t xlogInstancePtr;

@end


@implementation TDOSLogger

- (instancetype)initWithConfig:(TDOSLoggerConfig *)config {
    NSAssert(config != nil, @"Invalid Config");
    if (self = [super init]) {
        _config = config;
        [self initxlog:config];
        NSNotificationName willTerminateNotification = nil;
#if TARGET_OS_OSX
        willTerminateNotification = NSApplicationWillTerminateNotification;
#elif TARGET_OS_IOS
        willTerminateNotification = UIApplicationWillTerminateNotification;
#endif
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onAppWillTerminate:)
                                                     name:willTerminateNotification object:nil];
    }
    return self;
}

- (void)dealloc {
    mars::xlog::ReleaseXloggerInstance(self.config.logFilePrefix.UTF8String);
}

- (void)initxlog:(TDOSLoggerConfig *)config {
    NSString *logPath = config.logPath;
    NSLog(@"TDOSLog log path: %@", logPath);
    
    // update mmap file's name if needed
    if (config.isLogFilePrefixChanged) {
        [self updateMmapFilename];
    }

    // set do not backup for logpath
    const char *attrName = "com.apple.MobileBackup";
    u_int8_t attrValue = 1;
    setxattr([logPath UTF8String], attrName, &attrValue, sizeof(attrValue), 0, 0);
    
    // set color level
    TLogLevel logLevel = (TLogLevel)config.defaultLogLevel;
    NSDictionary *colorInfo = [[NSUserDefaults standardUserDefaults] objectForKey:TDOSLogColorInfoKey];
    if (colorInfo && [colorInfo isKindOfClass:NSDictionary.class]) {
        long level = [[colorInfo objectForKey:TDOSLogColorLevelKey] longValue];
        long endTime = [[colorInfo objectForKey:TDOSLogColorEndTimeKey] longValue];
        if (endTime > time(0)) {
            logLevel = (TLogLevel)level;
        }
    }
    
    XLogConfig cConfig;
    cConfig.mode_ = kAppenderAsync;
    cConfig.logdir_ = [logPath UTF8String];
    cConfig.pub_key_ = [config.publicKey UTF8String] ?: "";
    cConfig.nameprefix_ = [config.logFilePrefix UTF8String];
    
    mars::comm::XloggerCategory *logger = mars::xlog::NewXloggerInstance(cConfig, logLevel);
    _xlogInstancePtr = (uintptr_t)logger;
    mars::xlog::SetConsoleLogOpen(_xlogInstancePtr, config.enableConsoleLog);
}

- (void)onAppWillTerminate:(NSNotification *)notification {
    mars::xlog::ReleaseXloggerInstance(self.config.logFilePrefix.UTF8String);
    _xlogInstancePtr = NULL;
}

#pragma mark - TDLoggingIMPProtocol

- (void)setLogLevel:(RAFTLogLevel)level {
    TLogLevel xlogLevel = (TLogLevel)level;
    mars::xlog::SetLevel(_xlogInstancePtr, xlogLevel);
}

- (void)resetColorLevel {
    mars::xlog::SetLevel(_xlogInstancePtr, kLevelError);
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:TDOSLogColorInfoKey];
}

- (void)setLogLevel:(RAFTLogLevel)level endTimestamp:(time_t)endtime {
    [self setLogLevel:level];
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    [dict setObject:@(level) forKey:TDOSLogColorLevelKey];
    [dict setObject:@(endtime) forKey:TDOSLogColorEndTimeKey];
    [[NSUserDefaults standardUserDefaults] setObject:dict forKey:TDOSLogColorInfoKey];
}

- (BOOL)isColorState {
    NSDictionary *colorInfo = [[NSUserDefaults standardUserDefaults] objectForKey:TDOSLogColorInfoKey];
    if (colorInfo && [colorInfo isKindOfClass:NSDictionary.class]) {
        NSInteger endTime = [[colorInfo objectForKey:TDOSLogColorEndTimeKey] integerValue];
        if (endTime > time(0)) {
            return YES;
        }
    }
    return NO;
}

- (void)flushLog:(BOOL)isSync {
    [self log:RAFTLogLevelInfo tag:TDOS_TAG_INTERNAL file:__FILE__ func:__func__ line:__LINE__ format:@"log flush %d", isSync, nil];
    mars::xlog::Flush(_xlogInstancePtr, isSync);
}

- (void)setMaxLogAliveTime:(long)time {
    mars::xlog::SetMaxAliveTime(_xlogInstancePtr, time);
    // the mars sdk only remove .xlog files (internal delay 2 * 60s)
    // if app often change the log_prefix, then mmap file also need to remove
    __weak __typeof(self)weakSelf = self;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(60 * NSEC_PER_SEC)), dispatch_get_global_queue(0, 0), ^{
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        [strongSelf autoCleanOldMmapFiles:time];
    });
}

- (void)setMaxTotalLogFileSize:(int64_t)maxSize {
    __weak __typeof(self)weakSelf = self;
    // delay 60s to avoid startup time
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(60 * NSEC_PER_SEC)), dispatch_get_global_queue(0, 0), ^{
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        [strongSelf autoCleanLogFiles:maxSize];
    });
}

- (void)setConsoleLogEnabled:(BOOL)enabled {
    mars::xlog::SetConsoleLogOpen(_xlogInstancePtr, enabled);
}

static inline void writeToXlog(TDOSLogger *object,
                               const char * _Nonnull file,
                               const char * _Nonnull func,
                               RAFTLogLevel level,
                               int line, NSString * _Nonnull tag, NSString *msg) {
    NSString *truncatedString = truncateEmojiUnicodeForRawString(msg);
    uint64_t logIndex = object->_logIndex++;
    
    XLoggerInfo info;
    info.level = (TLogLevel)level;
    info.tag = tag.UTF8String;
    info.s_tag = @(logIndex).stringValue.UTF8String;
    info.t_tag = NULL;
    info.filename = file;
    info.func_name = func;
    info.line = line;
    NSString *threadName = [NSThread currentThread].name;
    info.t_name = threadName.UTF8String ?: "";
    gettimeofday(&info.timeval, NULL);
    info.pid = xlogger_pid();
    info.tid = xlogger_tid();
    info.maintid = xlogger_maintid();
    mars::xlog::XloggerWrite(object->_xlogInstancePtr, &info, truncatedString.UTF8String);
}

- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
     format:(NSString *)format, ... NS_REQUIRES_NIL_TERMINATION {
    if (!format) return;
    if (!_xlogInstancePtr) return;
    if (mars::xlog::IsEnabledFor(_xlogInstancePtr, (TLogLevel)level) == false) return;
    va_list args;
    va_start(args, format);
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    writeToXlog(self, file, func, level, line, tag, message);
}

- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
        msg:(NSString *)msg {
    if (!msg) return;
    if (!_xlogInstancePtr) return;
    if (mars::xlog::IsEnabledFor(_xlogInstancePtr, (TLogLevel)level) == false) return;
    writeToXlog(self, file, func, level, line, tag, msg);
}

- (NSString *)getPeroidLogWithDay:(NSString *)day beginHour:(int)beginHour endHour:(int)endHour {
    NSAssert(NO, @"Use 'getPeroidLogFilesWithStartTime:endTime:' method");
    // some xlog versions provide an alternative way to get logs
    // e.g. : appender_get_period_log()
    // you can implement this interface in your custom logger.
    return nil;
}

- (NSArray<NSString *> *)getPeroidLogFilesWithStartTime:(NSTimeInterval)startTime endTime:(NSTimeInterval)endTime {
    // 时间戳修正 (按小时对齐)
    int secondsPerHour = 3600;
    long startHour = (long)(startTime / secondsPerHour);
    long endHour = (long)(endTime / secondsPerHour);
    int64_t adjustedStartTime = startHour * secondsPerHour; // 第1s
    int64_t adjustedEndTime = ((endHour + 1) * secondsPerHour) - 1; // 最后1s
    
    // 采用腾讯视频文件查找方案
    TDLogUploadFileTimeFilter *timeFilter = [[TDLogUploadFileTimeFilter alloc] initWithStartTime:adjustedStartTime
                                                                                         endTime:adjustedEndTime];
    NSArray *logFiles = [TDLogUploadFileFinder searchFile:timeFilter directoryPath:self.config.logPath];
    // 过滤mmap
    NSMutableArray *pendingRemoveFiles = nil;
    for (NSString *file in logFiles) {
        if ([file.pathExtension hasPrefix:@"mmap"]) {
            if (!pendingRemoveFiles) {
                pendingRemoveFiles = [NSMutableArray array];
            }
            [pendingRemoveFiles addObject:file];
        }
    }
    if (pendingRemoveFiles) {
        NSMutableArray *tmpArr = logFiles.mutableCopy;
        [tmpArr removeObjectsInArray:pendingRemoveFiles];
        logFiles = tmpArr;
    }
    // 如果使用日志加密，补充加密公钥md5文件
    NSString *pubKey = self.config.publicKey;
    if (logFiles.count > 0 && pubKey.length > 100) {
        NSMutableArray *logFilesWithEncryptKey = [logFiles mutableCopy];
        NSString *pubkeyHashFilePath = [self.config.logPath stringByAppendingPathComponent:@"tdoslog_pubkey_hash.txt"];
        [[TDIAUtil md5HexDigest:pubKey] writeToFile:pubkeyHashFilePath atomically:YES encoding:NSUTF8StringEncoding error:nil];
        if (![logFilesWithEncryptKey containsObject:pubkeyHashFilePath]) {
            [logFilesWithEncryptKey addObject:pubkeyHashFilePath];
        }
        logFiles = logFilesWithEncryptKey;
    }
    return logFiles;
}

- (NSArray<NSString *> *)getPeroidLogFilesWithStartTime:(NSTimeInterval)startTime
                                                endTime:(NSTimeInterval)endTime
                                              sizeLimit:(unsigned long long)sizeLimit {
    NSArray *logFiles = [self getPeroidLogFilesWithStartTime:startTime endTime:endTime];
    // Size Limit Check
    NSFileManager *fileManager = [NSFileManager defaultManager];
    unsigned long long totalFilesSize = 0;
    for (NSString *singleFilePath in logFiles) {
        totalFilesSize += [TDIAUtil fileSizeWithPath:singleFilePath];
    }
    if (totalFilesSize > sizeLimit) {
        unsigned long long tmpTotalFilesSize = totalFilesSize;
        NSMutableArray *finalFilesArr = [logFiles mutableCopy];
        // sort by time，old to new
        NSArray *sortedArr = [logFiles sortedArrayUsingComparator:^NSComparisonResult(NSString *  _Nonnull obj1,
                                                                                      NSString *  _Nonnull obj2) {
            NSDictionary *fileAttributes1 = [fileManager attributesOfItemAtPath:obj1 error:nil];
            NSDictionary *fileAttributes2 = [fileManager attributesOfItemAtPath:obj2 error:nil];
            NSDate *modifyDate1 = [fileAttributes1 objectForKey:NSFileModificationDate];
            NSDate *modifyDate2 = [fileAttributes2 objectForKey:NSFileModificationDate];
            return [modifyDate1 compare:modifyDate2];
        }];
        for (NSString *singleFilePath in sortedArr) {
            tmpTotalFilesSize -= [TDIAUtil fileSizeWithPath:singleFilePath];
            [finalFilesArr removeObject:singleFilePath];
            if (tmpTotalFilesSize <= sizeLimit) {
                break;
            }
        }
        logFiles = finalFilesArr;
    }
    return logFiles;
}

- (NSString *)getLogFolderPath {
    return self.config.logPath;
}

- (NSString *)getLogEncryptPublicKey {
    return self.config.publicKey;
}

- (instancetype)createSubLoggerInstanceWithLogPrefix:(NSString *)prefix
                                             logPath:(NSString *)path
                                  andDefaultLogLevel:(RAFTLogLevel)level {
    TDOSLoggerConfig *subLoggerConfig = [TDOSLoggerConfig configWithLogPath:path
                                                                  logPrefix:prefix
                                                               defaultLevel:level
                                                               andPublicKey:self.config.publicKey];
    return [[TDOSLogger alloc] initWithConfig:subLoggerConfig];
}

#pragma mark - Utils

/// 处理emoji截断导致的UTF8String NULL
/// @param rawString 原始string
static inline NSString *truncateEmojiUnicodeForRawString(NSString *rawString) {
    NSString *truncatedString = rawString;
    if (rawString.length > 0 && ![rawString UTF8String]) {
        __block NSUInteger toIndex = 0;
        [rawString enumerateSubstringsInRange:NSMakeRange(0, rawString.length)
                                      options:NSStringEnumerationByComposedCharacterSequences
                                   usingBlock:^(NSString * _Nullable substring,
                                                NSRange substringRange,
                                                NSRange enclosingRange,
                                                BOOL * _Nonnull stop) {
            if (substringRange.length > 1) {
                toIndex = substringRange.location + substringRange.length;
                *stop = YES;
            }
        }];
        truncatedString = [rawString substringWithRange:NSMakeRange(0, toIndex)];
    }
    return truncatedString;
}

- (void)autoCleanLogFiles:(int64_t)maxTotalFileSize {
    if (maxTotalFileSize < 1024 * 1024 * 50) {
        return; // 保护逻辑，最少50M
    }
    NSArray<NSString *> *logFiles = [TDLogUploadFileFinder getFilesWithDirectoryPath:self.config.logPath];
    NSMutableArray *filesInfoArr = [NSMutableArray array];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *filePathKey = @"TDS_TMP_FILEPATH_KEY";
    for (NSString *logFilePath in logFiles) {
        NSDictionary *fileInfo = [fileManager attributesOfItemAtPath:logFilePath error:nil];
        if (fileInfo) {
            NSMutableDictionary *dic = fileInfo.mutableCopy;
            [dic setObject:logFilePath forKey:filePathKey];
            [filesInfoArr addObject:dic];
        }
    }
    
    NSArray *sortedArr = [filesInfoArr sortedArrayUsingComparator:^(id _Nonnull obj1, id _Nonnull obj2) {
        NSDate *firstDate = [(NSDictionary *)obj1 objectForKey:NSFileModificationDate];
        NSDate *secondDate = [(NSDictionary *)obj2 objectForKey:NSFileModificationDate];
        return [(NSDate *)secondDate compare:firstDate];//降序
    }];
    
    int64_t remain = maxTotalFileSize;
    for (int i = 0; i < sortedArr.count; i++) {
        NSDictionary *logInfo = sortedArr[i];
        if (remain > 0) {
            NSNumber *fileSizeObj = [logInfo objectForKey:NSFileSize];
            remain = remain - fileSizeObj.longLongValue;
        } else {
            NSString *path = (NSString *)logInfo[filePathKey];
            [fileManager removeItemAtPath:path error:nil];
            [self log:RAFTLogLevelInfo tag:TDOS_TAG_INTERNAL file:__FILE__ func:__func__ line:__LINE__
               format:@"del log due to size limit:%lld path:%@", maxTotalFileSize, path, nil];
        }
    }
}

- (BOOL)updateMmapFilename {
    NSArray<NSString *> *files = [TDLogUploadFileFinder getFilesWithDirectoryPath:self.config.logPath];
    NSMutableArray<NSString *> *mmapFiles = [NSMutableArray arrayWithCapacity:1];
    for (NSString *filePath in files) {
        if ([filePath.pathExtension hasPrefix:@"mmap"]) {
            if ([filePath.lastPathComponent.stringByDeletingPathExtension isEqualToString:self.config.logFilePrefix]) {
                return NO; // already has new mmap, return.
            } else {
                [mmapFiles addObject:filePath];
            }
        }
    }
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (mmapFiles.count > 0) {
        NSString *oldMmapFilePath = mmapFiles.firstObject;
        if (mmapFiles.count > 1) {
            NSMutableArray *filesInfoArr = [NSMutableArray arrayWithCapacity:mmapFiles.count];
            NSString *tmpFilePathKey = @"TDS_TMP_FILEPATH_KEY";
            for (NSString *mmapPath in mmapFiles) {
                NSDictionary *mmapFileAttrs = [fileManager attributesOfItemAtPath:mmapPath error:nil];
                if (mmapFileAttrs) {
                    NSMutableDictionary *dic = mmapFileAttrs.mutableCopy;
                    [dic setObject:mmapPath forKey:tmpFilePathKey];
                    [filesInfoArr addObject:dic];
                }
            }
            NSArray<NSDictionary *> *sortedArr = [filesInfoArr sortedArrayUsingComparator:^(id _Nonnull obj1, id _Nonnull obj2) {
                NSDate *firstDate = [(NSDictionary *)obj1 objectForKey:NSFileModificationDate];
                NSDate *secondDate = [(NSDictionary *)obj2 objectForKey:NSFileModificationDate];
                return [(NSDate *)secondDate compare:firstDate];//降序
            }];
            oldMmapFilePath = sortedArr.firstObject[tmpFilePathKey];
        }
        // do rename
        NSString *updatedPath = [[[oldMmapFilePath stringByDeletingLastPathComponent]
                                  stringByAppendingPathComponent:self.config.logFilePrefix]
                                 stringByAppendingPathExtension:oldMmapFilePath.pathExtension];
        [fileManager moveItemAtPath:oldMmapFilePath toPath:updatedPath error:nil];
    }
    return YES;
}

- (void)autoCleanOldMmapFiles:(long)time {
    NSArray<NSString *> *files = [TDLogUploadFileFinder getFilesWithDirectoryPath:self.config.logPath];
    for (NSString *filePath in files) {
        if ([filePath.pathExtension hasPrefix:@"mmap"] &&
            ![filePath.lastPathComponent.stringByDeletingPathExtension isEqualToString:self.config.logFilePrefix]) {
            NSDictionary *fileInfo = [[NSFileManager defaultManager] attributesOfItemAtPath:filePath error:nil];
            NSDate *modifyDate = [fileInfo objectForKey:NSFileModificationDate];
            if (abs([modifyDate timeIntervalSinceNow]) > time) {
                [[NSFileManager defaultManager] removeItemAtPath:filePath error:nil];
                [self log:RAFTLogLevelInfo tag:TDOS_TAG_INTERNAL file:__FILE__ func:__func__ line:__LINE__
                   format:@"remove old mmap: %@", filePath, nil];
            }
        }
    }
}

@end
