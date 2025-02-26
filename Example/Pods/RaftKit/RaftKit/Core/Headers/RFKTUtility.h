//   
//  RFKTUtility.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>
#include <mach/thread_info.h>
#include <mach/mach_types.h>

NS_ASSUME_NONNULL_BEGIN

/// Utilities
@interface RFKTUtility : NSObject

/// SDK version string
+ (NSString *)sdkVersion;

/// Bundle Name
+ (NSString *)bundleName;

/// An unique uuid 
+ (NSString *)rfktUserId;

/// Set a unique user ID for report
/// @param uid string
+ (void)updateRFKTUserId:(NSString *)uid;

/// Customized user id for feedback: bundleName_rfktUserId
+ (NSString *)userOpenID;

/// The first active \c UIWindowScene of the app.
@property (nonatomic, readonly, class, nullable) UIWindowScene *activeScene API_AVAILABLE(ios(13.0));

/// The key window of the app, if it is not a RFKTWindow.
/// If it is, then RFKTWindow.previousKeyWindow is returned.
+ (nullable UIWindow *)appKeyWindow;

/// The key window of the app
/// @param isIgnore ignore raftkit window or not
+ (nullable UIWindow *)appKeyWindowIgoreRFKTWindow:(BOOL)isIgnore;

/// App's Supported Orientations
+ (UIInterfaceOrientationMask)infoPlistSupportedInterfaceOrientationsMask;

/// Current visible ViewController
+ (nullable UIViewController *)visibleViewController;

/// Get localized string for key.
/// Key is defined in RaftKitLocalized.strings
+ (NSString *)localizedString:(NSString *)key;

/// UIImpactFeedbackGenerator shortcut method
+ (void)impactFeedback;

#pragma mark - time utility
/// Date string in yyyy-MM-dd HH:mm:ss formate
/// @param timeInterval TimeIntervalSince1970
+ (NSString *)formatDateStringFromNSTimeInterval:(NSTimeInterval)timeInterval;

#pragma mark - Crypto
/// MD5
/// @param input source string
+ (NSString *)md5HexDigest:(NSString *)input;

#pragma mark - File utils

/// Create path with given string
/// @param folderpath path str
+ (BOOL)createFolderIfNeededWithPath:(NSString *)folderpath;

/// Get given file or folder's size
/// @param fileOrFolderName file or sub directory's name
+ (unsigned long long)fileSizeWithPath:(NSString *)fileOrFolderName;

/// Get size string with given file path
/// @param fullPath str
+ (NSString *)sizeStringForFileAtPath:(NSString *)fullPath;

@end


@interface RFKTUtility (SystemVersion)

/// e.g.:iPhone11,2
+ (NSString *)deviceModelString;

/// e.g.:14.5.1 = 140501
+ (NSInteger)numbericOSVersion;

/// System Version Compare
/// @param currentVersion str
/// @param targetVersion str
+ (NSComparisonResult)compareSystemVersion:(nonnull NSString *)currentVersion toVersion:(nonnull NSString *)targetVersion;

/// Current version same or above given version
/// @param targetVersion str
+ (BOOL)isCurrentSystemAtLeastVersion:(nonnull NSString *)targetVersion;

/// Current version lower than given version
/// @param targetVersion str
+ (BOOL)isCurrentSystemLowerThanVersion:(nonnull NSString *)targetVersion;

@end

@interface RFKTUtility (Resources)

#pragma mark - CPU

/// CPU 核心数
+ (unsigned int)numberOfCPUCores;

/// App当前CPU利用率
+ (float)currentCPUUsage;

/// 遍历各个CPU信息
/// @param threadCount 线程个数
/// @param block 回调CPU basic info
+ (float)enumerateCPU:(nullable mach_msg_type_number_t *)threadCount
           usingBlock:(nullable void NS_NOESCAPE (^)(thread_t threadId, thread_basic_info_t basicInfo))block;

#pragma mark - 内存

/// App footprint内存（dirty memory），单位byte
+ (uint64_t)appFootprintMemory;

/// App resident内存（包含footprint + 系统库clean内存），单位byte
+ (uint64_t)appResidentMemory;

/// 可用内存size，单位byte
+ (uint64_t)freeMemorySize;

#pragma mark - 磁盘

/// 设备磁盘大小
+ (uint64_t)storageTotalSize;

/// 设备可用磁盘大小
+ (uint64_t)storageFreeSize;

@end


@interface RFKTUtility (DebugMode)

/// Returns true if the current process is being debugged.
+ (BOOL)isRunningUnderDebugger;

/// Returns true if running in UITest mode.
+ (BOOL)isRunningTests;

@end


NS_ASSUME_NONNULL_END
