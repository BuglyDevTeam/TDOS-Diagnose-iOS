//
//  FLEXMultilineTableViewCell.h
//  FLEX
//
//  Created by Ryan Olson on 2/13/15.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXTableViewCell.h"

/// A cell with both labels set to be multi-line capable.
@interface RFKT_FLEXMultilineTableViewCell : RFKT_FLEXTableViewCell

+ (CGFloat)preferredHeightWithAttributedText:(NSAttributedString *)attributedText
                                    maxWidth:(CGFloat)contentViewWidth
                                       style:(UITableViewStyle)style
                              showsAccessory:(BOOL)showsAccessory;

@end

/// A \c RFKT_FLEXMultilineTableViewCell initialized with \c UITableViewCellStyleSubtitle
@interface RFKT_FLEXMultilineDetailTableViewCell : RFKT_FLEXMultilineTableViewCell

@end
