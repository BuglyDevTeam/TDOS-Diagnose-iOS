//   
//  TDIAUtil.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/10.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

#ifndef TDIAGCommonDefines_h
#define TDIAGCommonDefines_h

#pragma mark - Clang Warnings

#define TDIA_ArgumentToString(macro) #macro
#define TDIA_ClangWarningConcat(warning_name) TDIA_ArgumentToString(clang diagnostic ignored warning_name)

/// warning list ref:https://clang.llvm.org/docs/DiagnosticsReference.html
#define TDIA_IGNORE_WARNING_BEGIN(warningName) _Pragma("clang diagnostic push") _Pragma(TDIA_ClangWarningConcat(#warningName))
#define TDIA_IGNORE_WARNING_END _Pragma("clang diagnostic pop")



NS_ASSUME_NONNULL_BEGIN

/// 工具类
@interface TDIAUtil : NSObject

/// SDK自定义的设备ID
+ (NSString *)tdiagDeviceId;

/// SDK版本号
+ (NSString *)sdkVersion;

/// App's bundle id
+ (NSString *)bundleIdentifier;

/// App's short version string
+ (NSString *)appVersionString;

/// App's language
+ (nullable NSString *)appLanguage;

/// Device' model, e.g. @"iPhone12,3"
+ (NSString *)deviceModel;

/// System version, e.g. @"15.0"
+ (NSString *)systemVersion;

#pragma mark - File Related

/// 判断文件是否存在
/// @param path 文件路径（相对或绝对路径）
+ (BOOL)fileExistsAtPath:(NSString *)path;

/// 删除文件
/// @param path 文件路径（相对或绝对路径）
+ (BOOL)removeItemAtPath:(NSString *)path;

/// 获取文件/文件夹大小
/// @param path 文件或文件夹路径
+ (unsigned long long)fileSizeWithPath:(NSString *)path;

/// 获取文件/文件夹大小的字符串表示
/// @param fullPath 文件/文件夹路径
+ (NSString *)sizeStringForFileAtPath:(NSString *)fullPath;

#pragma mark -

/// MD5
/// @param input 源字符串
+ (NSString *)md5HexDigest:(NSString *)input;

/// SHA1
/// @param input 源字符串
+ (NSString *)sha1HexDigest:(NSString *)input;

/// 签名方式: HMAC-SHA1
/// @param data 内容
/// @param key 密钥
+ (NSString *)hmacSHA1HexWithContent:(NSString *)data secret:(NSString *)key;

/// 签名方式: HMAC-SHA256
/// @param content 内容
/// @param secret 密钥
+ (NSString *)hmacSHA256WithContent:(NSString *)content secret:(NSString *)secret;

/// 计算文件分片的MD5
/// @param filePath 文件路径
/// @param offset 分片偏移量
/// @param sliceLength 分片长度
+ (nullable NSString *)md5Base64WithFile:(NSString *)filePath offset:(int64_t)offset andSliceLength:(int64_t)sliceLength;

/// URL Encode 函数
/// @param string 目标字符串
+ (NSString *)urlEncodeWithString:(NSString *)string;

/// Date转字符串
/// @param date 时间
+ (NSString *)dateToString:(NSDate *)date;


#pragma mark - Test or Debug Mode

/// Returns true if running in UITest mode.
+ (BOOL)isRunningTests;

@end

NS_ASSUME_NONNULL_END

#endif /* TDIAGCommonDefines_h */
