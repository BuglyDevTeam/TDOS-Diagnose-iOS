//
//  RFKT_FLEXDBQueryRowCell.h
//  FLEX
//
//  Created by Peng Tao on 15/11/24.
//  Copyright © 2015年 f. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSString * const kRFKT_FLEXDBQueryRowCellReuse;

@class RFKT_FLEXDBQueryRowCell;
@protocol RFKT_FLEXDBQueryRowCellDelegate <NSObject>

@optional
- (void)queryRowCell:(RFKT_FLEXDBQueryRowCell *)cell labelDidTapWithText:(NSString *)text index:(NSUInteger)idx;

@end

@interface RFKT_FLEXDBQueryRowCell : UITableViewCell

@property (nonatomic, weak) id<RFKT_FLEXDBQueryRowCellDelegate> delegate;

/// An array of NSString, NSNumber, or NSData objects
@property (nonatomic) NSArray *data;

@end
