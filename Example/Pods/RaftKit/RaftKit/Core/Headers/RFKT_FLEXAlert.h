//
//  FLEXAlert.h
//  FLEX
//
//  Created by Tanner Bennett on 8/20/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RFKT_FLEXAlert, RFKT_FLEXAlertAction;

typedef void (^RFKT_FLEXAlertReveal)(void);
typedef void (^RFKT_FLEXAlertBuilder)(RFKT_FLEXAlert *make);
typedef RFKT_FLEXAlert *(^RFKT_FLEXAlertStringProperty)(NSString *);
typedef RFKT_FLEXAlert *(^RFKT_FLEXAlertStringArg)(NSString *);
typedef RFKT_FLEXAlert *(^RFKT_FLEXAlertTextField)(void(^configurationHandler)(UITextField *textField));
typedef RFKT_FLEXAlertAction *(^RFKT_FLEXAlertAddAction)(NSString *title);
typedef RFKT_FLEXAlertAction *(^RFKT_FLEXAlertActionStringProperty)(NSString *);
typedef RFKT_FLEXAlertAction *(^RFKT_FLEXAlertActionProperty)(void);
typedef RFKT_FLEXAlertAction *(^RFKT_FLEXAlertActionBOOLProperty)(BOOL);
typedef RFKT_FLEXAlertAction *(^RFKT_FLEXAlertActionHandler)(void(^handler)(NSArray<NSString *> *strings));

@interface RFKT_FLEXAlert : NSObject

/// Shows a simple alert with one button which says "Dismiss"
+ (void)showAlert:(NSString *)title message:(NSString *)message from:(UIViewController *)viewController;

/// Construct and display an alert
+ (void)makeAlert:(RFKT_FLEXAlertBuilder)block showFrom:(UIViewController *)viewController;
/// Construct and display an action sheet-style alert
+ (void)makeSheet:(RFKT_FLEXAlertBuilder)block
         showFrom:(UIViewController *)viewController
           source:(id)viewOrBarItem;

/// Construct an alert
+ (UIAlertController *)makeAlert:(RFKT_FLEXAlertBuilder)block;
/// Construct an action sheet-style alert
+ (UIAlertController *)makeSheet:(RFKT_FLEXAlertBuilder)block;

/// Set the alert's title.
///
/// Call in succession to append strings to the title.
@property (nonatomic, readonly) RFKT_FLEXAlertStringProperty title;
/// Set the alert's message.
///
/// Call in succession to append strings to the message.
@property (nonatomic, readonly) RFKT_FLEXAlertStringProperty message;
/// Add a button with a given title with the default style and no action.
@property (nonatomic, readonly) RFKT_FLEXAlertAddAction button;
/// Add a text field with the given (optional) placeholder text.
@property (nonatomic, readonly) RFKT_FLEXAlertStringArg textField;
/// Add a text field with the given (optional) preset text.
@property (nonatomic, readonly) RFKT_FLEXAlertStringArg textFieldPresetText;
/// Add and configure the given text field.
///
/// Use this if you need to more than set the placeholder, such as
/// supply a delegate, make it secure entry, or change other attributes.
@property (nonatomic, readonly) RFKT_FLEXAlertTextField configuredTextField;

@end

@interface RFKT_FLEXAlertAction : NSObject

/// Set the action's title.
///
/// Call in succession to append strings to the title.
@property (nonatomic, readonly) RFKT_FLEXAlertActionStringProperty title;
/// Make the action destructive. It appears with red text.
@property (nonatomic, readonly) RFKT_FLEXAlertActionProperty destructiveStyle;
/// Make the action cancel-style. It appears with a bolder font.
@property (nonatomic, readonly) RFKT_FLEXAlertActionProperty cancelStyle;
/// Enable or disable the action. Enabled by default.
@property (nonatomic, readonly) RFKT_FLEXAlertActionBOOLProperty enabled;
/// Give the button an action. The action takes an array of text field strings.
@property (nonatomic, readonly) RFKT_FLEXAlertActionHandler handler;
/// Access the underlying UIAlertAction, should you need to change it while
/// the encompassing alert is being displayed. For example, you may want to
/// enable or disable a button based on the input of some text fields in the alert.
/// Do not call this more than once per instance.
@property (nonatomic, readonly) UIAlertAction *action;

@end
