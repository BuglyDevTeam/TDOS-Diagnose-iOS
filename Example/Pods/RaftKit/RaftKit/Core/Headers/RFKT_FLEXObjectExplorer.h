//
//  FLEXObjectExplorer.h
//  FLEX
//
//  Created by Tanner Bennett on 8/28/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXRuntime+UIKitHelpers.h"

/// Carries state about the current user defaults settings
@interface RFKT_FLEXObjectExplorerDefaults : NSObject
+ (instancetype)canEdit:(BOOL)editable wantsPreviews:(BOOL)showPreviews;

/// Only \c YES for properties and ivars
@property (nonatomic, readonly) BOOL isEditable;
/// Only affects properties and ivars
@property (nonatomic, readonly) BOOL wantsDynamicPreviews;
@end

@interface RFKT_FLEXObjectExplorer : NSObject

+ (instancetype)forObject:(id)objectOrClass;

+ (void)configureDefaultsForItems:(NSArray<id<RFKT_FLEXObjectExplorerItem>> *)items;

@property (nonatomic, readonly) id object;
/// Subclasses can override to provide a more useful description
@property (nonatomic, readonly) NSString *objectDescription;

/// @return \c YES if \c object is an instance of a class,
/// or \c NO if \c object is a class itself.
@property (nonatomic, readonly) BOOL objectIsInstance;

/// An index into the `classHierarchy` array.
///
/// This property determines which set of data comes out of the metadata arrays below
/// For example, \c properties contains the properties of the selected class scope,
/// while \c allProperties is an array of arrays where each array is a set of
/// properties for a class in the class hierarchy of the current object.
@property (nonatomic) NSInteger classScope;

@property (nonatomic, readonly) NSArray<NSArray<RFKT_FLEXProperty *> *> *allProperties;
@property (nonatomic, readonly) NSArray<RFKT_FLEXProperty *> *properties;

@property (nonatomic, readonly) NSArray<NSArray<RFKT_FLEXProperty *> *> *allClassProperties;
@property (nonatomic, readonly) NSArray<RFKT_FLEXProperty *> *classProperties;

@property (nonatomic, readonly) NSArray<NSArray<RFKT_FLEXIvar *> *> *allIvars;
@property (nonatomic, readonly) NSArray<RFKT_FLEXIvar *> *ivars;

@property (nonatomic, readonly) NSArray<NSArray<RFKT_FLEXMethod *> *> *allMethods;
@property (nonatomic, readonly) NSArray<RFKT_FLEXMethod *> *methods;

@property (nonatomic, readonly) NSArray<NSArray<RFKT_FLEXMethod *> *> *allClassMethods;
@property (nonatomic, readonly) NSArray<RFKT_FLEXMethod *> *classMethods;

@property (nonatomic, readonly) NSArray<Class> *classHierarchyClasses;
@property (nonatomic, readonly) NSArray<RFKT_FLEXStaticMetadata *> *classHierarchy;

@property (nonatomic, readonly) NSArray<NSArray<RFKT_FLEXProtocol *> *> *allConformedProtocols;
@property (nonatomic, readonly) NSArray<RFKT_FLEXProtocol *> *conformedProtocols;

@property (nonatomic, readonly) NSArray<RFKT_FLEXStaticMetadata *> *allInstanceSizes;
@property (nonatomic, readonly) RFKT_FLEXStaticMetadata *instanceSize;

@property (nonatomic, readonly) NSArray<RFKT_FLEXStaticMetadata *> *allImageNames;
@property (nonatomic, readonly) RFKT_FLEXStaticMetadata *imageName;

- (void)reloadMetadata;
- (void)reloadClassHierarchy;

@end
