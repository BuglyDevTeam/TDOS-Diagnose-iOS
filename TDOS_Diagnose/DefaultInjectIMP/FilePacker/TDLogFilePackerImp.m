//
//  TDLogFilePackerImp.m
//  TDOS_Diagnose
//
//  Created by raycgwang on 2022/4/15.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//

#import "TDLogFilePackerImp.h"
#if __has_include(<SSZipArchive/SSZipArchive.h>)
#import <SSZipArchive/SSZipArchive.h>
#elif __has_include(<ZipArchive/ZipArchive.h>)
#import "TDIAUtil.h"
TDIA_IGNORE_WARNING_BEGIN(-Wdocumentation)
#import <ZipArchive/ZipArchive.h>
TDIA_IGNORE_WARNING_END
#endif

@implementation TDLogFilePackerImp

- (instancetype)init {
    self = [super init];
    if (self) {
        _packDir = [NSString stringWithFormat:@"%@/tmp/TDOSLogTmp/", NSHomeDirectory()];
    }
    return self;
}

- (void)setCustomPackDir:(NSString *)tmpPackDir {
    BOOL isDir;
    BOOL isExist = [[NSFileManager defaultManager] fileExistsAtPath:tmpPackDir isDirectory:&isDir];
    if (isExist && isDir) {
        _packDir = tmpPackDir;
    } else {
        NSAssert(NO, @"Invalid PackDir.%@", tmpPackDir);
    }
}

- (NSString *)packFiles:(NSArray<NSString *> *)files withZipName:(NSString *)zipName {
    if (zipName.length <= 0) {
        return nil;
    }
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:_packDir]) {
        [fileManager createDirectoryAtPath:_packDir withIntermediateDirectories:YES attributes:nil error:nil];
    }
    NSString *zipPath = [_packDir stringByAppendingPathComponent:zipName];
    if (![zipPath hasSuffix:@"zip"]) {
        zipPath = [zipPath stringByAppendingString:@".zip"];
    }
    
    // remove zip if exist
    if ([fileManager fileExistsAtPath:zipPath]) {
        [fileManager removeItemAtPath:zipPath error:NULL];
    }
    
    // files check
    NSMutableDictionary *finalFilesDict = [NSMutableDictionary dictionaryWithObjects:files forKeys:files];
    for (NSString *filePath in files) {
        if (![filePath hasPrefix:NSHomeDirectory()]) {
            if (![fileManager fileExistsAtPath:filePath]) {
                [finalFilesDict setObject:[NSHomeDirectory() stringByAppendingPathComponent:filePath] forKey:filePath];
            }
        }
        if (![fileManager fileExistsAtPath:[finalFilesDict objectForKey:filePath]]) {
            [finalFilesDict removeObjectForKey:filePath];
        }
    }
    if (finalFilesDict.allValues.count > 0) {
#if __has_include(<SSZipArchive/SSZipArchive.h>)
        BOOL isOk = [SSZipArchive createZipFileAtPath:zipPath withFilesAtPaths:finalFilesDict.allValues];
        return isOk ? zipPath : nil;
#elif __has_include(<ZipArchive/ZipArchive.h>)
        ZipArchive *zipArchive = [[ZipArchive alloc] init];
        BOOL createResult = [zipArchive CreateZipFile2:zipPath];
        if (createResult) {
            for (NSString *filePath in finalFilesDict.allValues) {
                [zipArchive addFileToZip:filePath newname:[filePath pathComponents].lastObject];
            }
            [zipArchive CloseZipFile2];
            return zipPath;
        }
#else
        NSAssert(NO, @"NO Zip Lib");
#endif
    }
    return nil;
}

@end
