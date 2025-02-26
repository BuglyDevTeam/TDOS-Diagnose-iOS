//   
//  RFKTSimpleCellModel.h
//  RaftKit
//  
//  Created by raycgwang on 2021/4/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    RFKTSimpleTableViewCellTypeOneLineText, // left text, right text (same to cell default style1)
    RFKTSimpleTableViewCellTypeTwoLineText, // top text, bottom text (same to cell default style2)
    RFKTSimpleTableViewCellTypeSwitch, // left text, right switch
    RFKTSimpleTableViewCellTypeDisclosure, // left text, right disclosure view
    RFKTSimpleTableViewCellTypeTwoLineDisclosure, // text + detail text + disclosure view in two lines
    RFKTSimpleTableViewCellTypeCustomAccessoryButton, // accessoryView = custom button
    RFKTSimpleTableViewCellTypeAccessoryEdit, // accessoryView = Edit button
    RFKTSimpleTableViewCellTypeAccessoryCheckmark,
    RFKTSimpleTableViewCellTypeCustom,
} RFKTSimpleTableViewCellType;


@protocol RFKTSimpleTableViewCellDataModelActionDelegate <NSObject>

@required
/// Called when cell selected
- (void)onCellSelected:(_Nullable id)sender;

/// Called when switch button value changed
- (void)onSwitchChange:(_Nullable id)sender;

@end


@interface RFKTSimpleCellModel : NSObject <RFKTSimpleTableViewCellDataModelActionDelegate>

@property (nonatomic, copy, nonnull) NSString *mainText;
@property (nonatomic, copy, nullable) NSString *detailText;
@property (nonatomic, assign, readonly) RFKTSimpleTableViewCellType cellType;

@property (nonatomic, strong, nullable) UIColor *mainTextColor;
@property (nonatomic, strong, nullable) id accessoryValue;
@property (nonatomic, strong, nullable) UIView *customAccessoryView;
@property (nonatomic, copy) void (^actionBlock)(_Nullable id para);

#pragma mark - CustomCell Support
@property (nonatomic, strong, nullable) NSString *customCellIdentifier;
@property (nonatomic, strong, nullable) UIView *customCellView;
@property (nonatomic, assign) CGFloat customCellHeight;

/// Init a new simle cell model
/// @param text1 Main Text
/// @param text2 Detail Text
/// @param type cell display type
- (instancetype)initWithMainText:(nonnull NSString *)text1
                      detailText:(nullable NSString *)text2
                     andCellType:(RFKTSimpleTableViewCellType)type NS_DESIGNATED_INITIALIZER;

/// Init a custom type cell model
/// @param identifier reuse identifier
/// @param customView custom cell's subview
+ (instancetype)customCellWithReuseID:(NSString *)identifier andCustomView:(UIView *)customView;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)modelWithMainText:(nonnull NSString *)text1
                       detailText:(nullable NSString *)text2
                      andCellType:(RFKTSimpleTableViewCellType)type;

@end

NS_ASSUME_NONNULL_END
