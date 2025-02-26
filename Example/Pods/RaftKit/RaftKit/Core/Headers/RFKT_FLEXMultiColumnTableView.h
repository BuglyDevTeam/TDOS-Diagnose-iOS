//
//  PTMultiColumnTableView.h
//  PTMultiColumnTableViewDemo
//
//  Created by Peng Tao on 15/11/16.
//  Copyright © 2015年 Peng Tao. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RFKT_FLEXTableColumnHeader.h"

@class RFKT_FLEXMultiColumnTableView;

@protocol RFKT_FLEXMultiColumnTableViewDelegate <NSObject>

@required
- (void)multiColumnTableView:(RFKT_FLEXMultiColumnTableView *)tableView didSelectRow:(NSInteger)row;
- (void)multiColumnTableView:(RFKT_FLEXMultiColumnTableView *)tableView didSelectCellInRow:(NSInteger)row column:(NSInteger)column;
- (void)multiColumnTableView:(RFKT_FLEXMultiColumnTableView *)tableView didSelectHeaderForColumn:(NSInteger)column
                    sortType:(RFKT_FLEXTableColumnHeaderSortType)sortType;

@optional
- (void)multiColumnTableView:(RFKT_FLEXMultiColumnTableView *)tableView didTapLabelWithText:(NSString *)text;

@end

@protocol RFKT_FLEXMultiColumnTableViewDataSource <NSObject>

@required

- (NSInteger)numberOfColumnsInTableView:(RFKT_FLEXMultiColumnTableView *)tableView;
- (NSInteger)numberOfRowsInTableView:(RFKT_FLEXMultiColumnTableView *)tableView;
- (NSString *)columnTitle:(NSInteger)column;
- (NSString *)rowTitle:(NSInteger)row;
- (NSArray<NSString *> *)contentForRow:(NSInteger)row;

- (CGFloat)multiColumnTableView:(RFKT_FLEXMultiColumnTableView *)tableView widthForContentCellInColumn:(NSInteger)column;
- (CGFloat)multiColumnTableView:(RFKT_FLEXMultiColumnTableView *)tableView heightForContentCellInRow:(NSInteger)row;
- (CGFloat)heightForTopHeaderInTableView:(RFKT_FLEXMultiColumnTableView *)tableView;
- (CGFloat)widthForLeftHeaderInTableView:(RFKT_FLEXMultiColumnTableView *)tableView;

@end


@interface RFKT_FLEXMultiColumnTableView : UIView

@property (nonatomic, weak) id<RFKT_FLEXMultiColumnTableViewDataSource> dataSource;
@property (nonatomic, weak) id<RFKT_FLEXMultiColumnTableViewDelegate> delegate;

- (void)reloadData;

@end
