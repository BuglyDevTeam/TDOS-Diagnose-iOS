//
//  FLEXMethodCallingViewController.h
//  Flipboard
//
//  Created by Ryan Olson on 5/23/14.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXVariableEditorViewController.h"
#import "RFKT_FLEXMethod.h"

@interface RFKT_FLEXMethodCallingViewController : RFKT_FLEXVariableEditorViewController

+ (instancetype)target:(id)target method:(RFKT_FLEXMethod *)method;

@end
