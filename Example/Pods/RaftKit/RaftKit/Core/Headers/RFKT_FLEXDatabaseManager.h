//
//  PTDatabaseManager.h
//  Derived from:
//
//  FMDatabase.h
//  FMDB( https://github.com/ccgus/fmdb )
//
//  Created by Peng Tao on 15/11/23.
//
//  Licensed to Flying Meat Inc. under one or more contributor license agreements.
//  See the LICENSE file distributed with this work for the terms under
//  which Flying Meat Inc. licenses this file to you.

#import <Foundation/Foundation.h>
#import "RFKT_FLEXSQLResult.h"

/// Conformers should automatically open and close the database
@protocol RFKT_FLEXDatabaseManager <NSObject>

@required

/// @return \c nil if the database couldn't be opened
+ (instancetype)managerForDatabase:(NSString *)path;

/// @return a list of all table names
- (NSArray<NSString *> *)queryAllTables;
- (NSArray<NSString *> *)queryAllColumnsOfTable:(NSString *)tableName;
- (NSArray<NSArray *> *)queryAllDataInTable:(NSString *)tableName;

@optional

- (RFKT_FLEXSQLResult *)executeStatement:(NSString *)SQLStatement;

/// Extend of queryAllColumnsOfTable, return data in dictionary formate
/// @param tableName str
- (NSArray<NSDictionary<NSString *,id> *> *)queryAllColumnsDetailDataOfTable:(NSString *)tableName;

/// whether has `rowid` in query results, usually sqlite has
- (BOOL)hasRowIdWhenQueryAllData;

@end
