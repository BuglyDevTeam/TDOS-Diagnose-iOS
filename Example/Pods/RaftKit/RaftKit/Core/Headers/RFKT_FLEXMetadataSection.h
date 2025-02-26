//
//  FLEXMetadataSection.h
//  FLEX
//
//  Created by Tanner Bennett on 9/19/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXTableViewSection.h"
#import "RFKT_FLEXObjectExplorer.h"

typedef NS_ENUM(NSUInteger, RFKT_FLEXMetadataKind) {
    RFKT_FLEXMetadataKindProperties = 1,
    RFKT_FLEXMetadataKindClassProperties,
    RFKT_FLEXMetadataKindIvars,
    RFKT_FLEXMetadataKindMethods,
    RFKT_FLEXMetadataKindClassMethods,
    RFKT_FLEXMetadataKindClassHierarchy,
    RFKT_FLEXMetadataKindProtocols,
    RFKT_FLEXMetadataKindOther
};

/// This section is used for displaying ObjC runtime metadata
/// about a class or object, such as listing methods, properties, etc.
@interface RFKT_FLEXMetadataSection : RFKT_FLEXTableViewSection

+ (instancetype)explorer:(RFKT_FLEXObjectExplorer *)explorer kind:(RFKT_FLEXMetadataKind)metadataKind;

@property (nonatomic, readonly) RFKT_FLEXMetadataKind metadataKind;

/// The names of metadata to exclude. Useful if you wish to group specific
/// properties or methods together in their own section outside of this one.
///
/// Setting this property calls \c reloadData on this section.
@property (nonatomic) NSSet<NSString *> *excludedMetadata;

@end
