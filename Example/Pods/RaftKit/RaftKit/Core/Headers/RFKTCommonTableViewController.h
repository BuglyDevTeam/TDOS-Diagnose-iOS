//   
//  RFKTCommonTableViewController.h
//  RaftKit
//  
//  Created by raycgwang on 2021/4/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKTCommonViewController.h"
#import "RFKTSimpleCellModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKTCommonTableViewController : RFKTCommonViewController

/// Main tableView
@property (nonatomic, readonly) UITableView *tableView;

/// Preferred tableView's style, default is UITableViewStyleGrouped
- (UITableViewStyle)preferredTableStyle;

/// Override this method to provide cell data
- (NSArray<NSArray<RFKTSimpleCellModel *> *> *)cellModelsForTableView;

/// Override this method to provide section header data
- (nullable NSArray<NSString *> *)sectionHeaderStringsForTableView;

/// Override this method to provide section footer data
- (nullable NSArray<NSString *> *)sectionFooterStringsForTableView;

/// Reload data from DataSource and reload tableView
- (void)reloadData;

/// Reload dataSource only, for deleteRowsAtIndexPaths and etc. use
- (void)reloadDataSourceOnly;


#pragma mark - Simple Cell Factory
/// Create cell with given model
/// @param model cellmodel
/// @param tableView Tableview
+ (UITableViewCell *)simpleCellForModel:(RFKTSimpleCellModel *)model
                          fromTableView:(nullable UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
