//
//  FLEXTableContentHeaderCell.h
//  FLEX
//
//  Created by Peng Tao on 15/11/26.
//  Copyright © 2015年 f. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, RFKT_FLEXTableColumnHeaderSortType) {
    RFKT_FLEXTableColumnHeaderSortTypeNone = 0,
    RFKT_FLEXTableColumnHeaderSortTypeAsc,
    RFKT_FLEXTableColumnHeaderSortTypeDesc,
};

NS_INLINE RFKT_FLEXTableColumnHeaderSortType FLEXNextTableColumnHeaderSortType(
    RFKT_FLEXTableColumnHeaderSortType current) {
    switch (current) {
        case RFKT_FLEXTableColumnHeaderSortTypeAsc:
            return RFKT_FLEXTableColumnHeaderSortTypeDesc;
        case RFKT_FLEXTableColumnHeaderSortTypeNone:
        case RFKT_FLEXTableColumnHeaderSortTypeDesc:
            return RFKT_FLEXTableColumnHeaderSortTypeAsc;
    }
    
    return RFKT_FLEXTableColumnHeaderSortTypeNone;
}

@interface RFKT_FLEXTableColumnHeader : UIView

@property (nonatomic) NSInteger index;
@property (nonatomic, readonly) UILabel *titleLabel;

@property (nonatomic) RFKT_FLEXTableColumnHeaderSortType sortType;

@end

