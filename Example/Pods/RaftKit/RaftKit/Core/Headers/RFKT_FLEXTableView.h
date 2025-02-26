//
//  FLEXTableView.h
//  FLEX
//
//  Created by Tanner on 4/17/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark Reuse identifiers

typedef NSString * RFKT_FLEXTableViewCellReuseIdentifier;

/// A regular \c RFKT_FLEXTableViewCell initialized with \c UITableViewCellStyleDefault
extern RFKT_FLEXTableViewCellReuseIdentifier const kRFKT_FLEXDefaultCell;
/// A \c RFKT_FLEXSubtitleTableViewCell initialized with \c UITableViewCellStyleSubtitle
extern RFKT_FLEXTableViewCellReuseIdentifier const kRFKT_FLEXDetailCell;
/// A \c RFKT_FLEXMultilineTableViewCell initialized with \c UITableViewCellStyleDefault
extern RFKT_FLEXTableViewCellReuseIdentifier const kRFKT_FLEXMultilineCell;
/// A \c RFKT_FLEXMultilineTableViewCell initialized with \c UITableViewCellStyleSubtitle
extern RFKT_FLEXTableViewCellReuseIdentifier const kRFKT_FLEXMultilineDetailCell;
/// A \c RFKT_FLEXTableViewCell initialized with \c UITableViewCellStyleValue1
extern RFKT_FLEXTableViewCellReuseIdentifier const kRFKT_FLEXKeyValueCell;
/// A \c RFKT_FLEXSubtitleTableViewCell which uses monospaced fonts for both labels
extern RFKT_FLEXTableViewCellReuseIdentifier const kRFKT_FLEXCodeFontCell;

#pragma mark - RFKT_FLEXTableView
@interface RFKT_FLEXTableView : UITableView

+ (instancetype)flexDefaultTableView;
+ (instancetype)groupedTableView;
+ (instancetype)plainTableView;
+ (instancetype)style:(UITableViewStyle)style;

/// You do not need to register classes for any of the default reuse identifiers above
/// (annotated as \c RFKT_FLEXTableViewCellReuseIdentifier types) unless you wish to provide
/// a custom cell for any of those reuse identifiers. By default, \c RFKT_FLEXTableViewCell,
/// \c RFKT_FLEXSubtitleTableViewCell, and \c RFKT_FLEXMultilineTableViewCell are used, respectively.
///
/// @param registrationMapping A map of reuse identifiers to \c UITableViewCell (sub)class objects.
- (void)registerCells:(NSDictionary<NSString *, Class> *)registrationMapping;

@end

NS_ASSUME_NONNULL_END
