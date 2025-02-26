//
//  FLEXRuntime+UIKitHelpers.h
//  FLEX
//
//  Created by Tanner Bennett on 12/16/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RFKT_FLEXProperty.h"
#import "RFKT_FLEXIvar.h"
#import "RFKT_FLEXMethod.h"
#import "RFKT_FLEXProtocol.h"
#import "RFKT_FLEXTableViewSection.h"

@class RFKT_FLEXObjectExplorerDefaults;

/// Model objects of an object explorer screen adopt this
/// protocol in order respond to user defaults changes 
@protocol RFKT_FLEXObjectExplorerItem <NSObject>
/// Current explorer settings. Set when settings change.
@property (nonatomic) RFKT_FLEXObjectExplorerDefaults *defaults;

/// YES for properties and ivars which surely support editing, NO for all methods.
@property (nonatomic, readonly) BOOL isEditable;
/// NO for ivars, YES for supported methods and properties
@property (nonatomic, readonly) BOOL isCallable;
@end

@protocol RFKT_FLEXRuntimeMetadata <RFKT_FLEXObjectExplorerItem>
/// Used as the main title of the row
- (NSString *)description;
/// Used to compare metadata objects for uniqueness
@property (nonatomic, readonly) NSString *name;

/// For internal use
@property (nonatomic) id tag;

/// Should return \c nil if not applicable
- (id)currentValueWithTarget:(id)object;
/// Used as the subtitle or description of a property, ivar, or method
- (NSString *)previewWithTarget:(id)object;
/// For methods, a method calling screen. For all else, an object explorer.
- (UIViewController *)viewerWithTarget:(id)object;
/// For methods and protocols, nil. For all else, an a field editor screen.
/// The given section is reloaded on commit of any changes.
- (UIViewController *)editorWithTarget:(id)object section:(RFKT_FLEXTableViewSection *)section;
/// Used to determine present which interactions are possible to the user
- (UITableViewCellAccessoryType)suggestedAccessoryTypeWithTarget:(id)object;
/// Return nil to use the default reuse identifier
- (NSString *)reuseIdentifierWithTarget:(id)object;

#if RFKT_FLEX_AT_LEAST_IOS13_SDK

/// An array of actions to place in the first section of the context menu.
- (NSArray<UIAction *> *)additionalActionsWithTarget:(id)object sender:(UIViewController *)sender API_AVAILABLE(ios(13.0));
/// An array where every 2 elements are a key-value pair. The key is a description
/// of what to copy like "Name" and the values are what will be copied.
- (NSArray<NSString *> *)copiableMetadataWithTarget:(id)object;
/// Properties and ivars return the address of an object, if they hold one.
- (NSString *)contextualSubtitleWithTarget:(id)object;

#endif

@end

// Even if a property is readonly, it still may be editable
// via a setter. Checking isEditable will not reflect that
// unless the property was initialized with a class.
@interface RFKT_FLEXProperty (UIKitHelpers) <RFKT_FLEXRuntimeMetadata> @end
@interface RFKT_FLEXIvar (UIKitHelpers) <RFKT_FLEXRuntimeMetadata> @end
@interface RFKT_FLEXMethodBase (UIKitHelpers) <RFKT_FLEXRuntimeMetadata> @end
@interface RFKT_FLEXMethod (UIKitHelpers) <RFKT_FLEXRuntimeMetadata> @end
@interface RFKT_FLEXProtocol (UIKitHelpers) <RFKT_FLEXRuntimeMetadata> @end

typedef NS_ENUM(NSUInteger, RFKT_FLEXStaticMetadataRowStyle) {
    RFKT_FLEXStaticMetadataRowStyleSubtitle,
    RFKT_FLEXStaticMetadataRowStyleKeyValue,
    RFKT_FLEXStaticMetadataRowStyleDefault = RFKT_FLEXStaticMetadataRowStyleSubtitle,
};

/// Displays a small row as a static key-value pair of information.
@interface RFKT_FLEXStaticMetadata : NSObject <RFKT_FLEXRuntimeMetadata>

+ (instancetype)style:(RFKT_FLEXStaticMetadataRowStyle)style title:(NSString *)title string:(NSString *)string;
+ (instancetype)style:(RFKT_FLEXStaticMetadataRowStyle)style title:(NSString *)title number:(NSNumber *)number;

+ (NSArray<RFKT_FLEXStaticMetadata *> *)classHierarchy:(NSArray<Class> *)classes;

@end


/// This is assigned to the \c tag property of each metadata.

