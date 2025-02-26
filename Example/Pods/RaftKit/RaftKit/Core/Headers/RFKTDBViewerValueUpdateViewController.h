//   
//  RFKTDBViewerValueUpdateViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/1.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTCommonViewController.h"
#import "RFKT_FLEXDatabaseManager.h"
#import "RFKT_FLEXTableContentViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKTDBViewerValueUpdateViewController : RFKTCommonViewController

/// Init method
/// @param cellValue str or null or ...
- (instancetype)initWithCellValue:(id)cellValue
                        tableName:(NSString *)tblname
                            rowId:(NSUInteger)rowid
                       columnInfo:(NSDictionary *)columnInfo
                        dbManager:(id<RFKT_FLEXDatabaseManager>)dbm NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil
                         bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

/// db table vc that push from
@property (nonatomic, weak) RFKT_FLEXTableContentViewController *dbTableContentVC;

@end

NS_ASSUME_NONNULL_END
