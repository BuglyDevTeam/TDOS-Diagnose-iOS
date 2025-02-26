//
//  PTTableListViewController.h
//  PTDatabaseReader
//
//  Created by Peng Tao on 15/11/23.
//  Copyright © 2015年 Peng Tao. All rights reserved.
//

#import "RFKT_FLEXFilteringTableViewController.h"

@interface RFKT_FLEXTableListViewController : RFKT_FLEXFilteringTableViewController

+ (BOOL)supportsExtension:(NSString *)extension;
- (instancetype)initWithPath:(NSString *)path;

@end
