//
//  FLEXFieldEditorViewController.h
//  FLEX
//
//  Created by Tanner on 11/22/18.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXVariableEditorViewController.h"
#import "RFKT_FLEXProperty.h"
#import "RFKT_FLEXIvar.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKT_FLEXFieldEditorViewController : RFKT_FLEXVariableEditorViewController

/// @return nil if the property is readonly or if the type is unsupported
+ (nullable instancetype)target:(id)target property:(RFKT_FLEXProperty *)property commitHandler:(void(^_Nullable)(void))onCommit;
/// @return nil if the ivar type is unsupported
+ (nullable instancetype)target:(id)target ivar:(RFKT_FLEXIvar *)ivar commitHandler:(void(^_Nullable)(void))onCommit;

/// Subclasses can change the button title via the \c title property
//@property (nonatomic, readonly) UIBarButtonItem *getterButton;

//- (void)getterButtonPressed:(id)sender;

@end

NS_ASSUME_NONNULL_END
