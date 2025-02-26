//
//  FLEXArgumentInputTextView.h
//  FLEXInjected
//
//  Created by Ryan Olson on 6/15/14.
//
//

#import "RFKT_FLEXArgumentInputView.h"

@interface RFKT_FLEXArgumentInputTextView : RFKT_FLEXArgumentInputView <UITextViewDelegate>

// For subclass eyes only

@property (nonatomic, readonly) UITextView *inputTextView;
@property (nonatomic) NSString *inputPlaceholderText;

@end
