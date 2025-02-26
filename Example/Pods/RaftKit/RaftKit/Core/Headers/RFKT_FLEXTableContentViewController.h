//
//  RFKT_FLEXTableContentViewController.h
//  RaftKit
//
//  Created by Peng Tao on 15/11/23.
//  Copyright © 2015年 Peng Tao. All rights reserved.
//  Modified by Ray

#import "RFKTCommonViewController.h"
#import "RFKT_FLEXDatabaseManager.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKT_FLEXTableContentViewController : RFKTCommonViewController

@property (nonatomic, weak, nullable) id <RFKT_FLEXDatabaseManager> dbManager;
@property (nonatomic, copy) NSString *dbTableName;

+ (instancetype)columns:(NSArray<NSString *> *)columnNames
          columnDetails:(nullable NSArray<NSDictionary<NSString *,id> *> *)columnDetails
                   rows:(NSArray<NSArray<NSString *> *> *)rowData
               hasRowId:(BOOL)hasRowId;

/// Reload data from db if possible
- (void)reloadDBDataIfPossible;

@end

NS_ASSUME_NONNULL_END
