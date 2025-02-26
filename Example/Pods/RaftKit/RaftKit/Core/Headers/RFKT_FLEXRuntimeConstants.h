//
//  FLEXRuntimeConstants.h
//  FLEX
//
//  Created by Tanner on 3/11/20.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

#define RFKT_FLEXEncodeClass(class) ("@\"" #class "\"")
#define RFKT_FLEXEncodeObject(obj) (obj ? [NSString stringWithFormat:@"@\"%@\"", [obj class]].UTF8String : @encode(id))

// Arguments 0 and 1 are self and _cmd always
extern const unsigned int kRFKT_FLEXNumberOfImplicitArgs;

// See https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtPropertyIntrospection.html#//apple_ref/doc/uid/TP40008048-CH101-SW6
extern NSString *const kRFKT_FLEXPropertyAttributeKeyTypeEncoding;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyBackingIvarName;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyReadOnly;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyCopy;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyRetain;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyNonAtomic;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyCustomGetter;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyCustomSetter;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyDynamic;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyWeak;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyGarbageCollectable;
extern NSString *const kRFKT_FLEXPropertyAttributeKeyOldStyleTypeEncoding;

typedef NS_ENUM(NSUInteger, RFKT_FLEXPropertyAttribute) {
    RFKT_FLEXPropertyAttributeTypeEncoding       = 'T',
    RFKT_FLEXPropertyAttributeBackingIvarName    = 'V',
    RFKT_FLEXPropertyAttributeCopy               = 'C',
    RFKT_FLEXPropertyAttributeCustomGetter       = 'G',
    RFKT_FLEXPropertyAttributeCustomSetter       = 'S',
    RFKT_FLEXPropertyAttributeDynamic            = 'D',
    RFKT_FLEXPropertyAttributeGarbageCollectible = 'P',
    RFKT_FLEXPropertyAttributeNonAtomic          = 'N',
    RFKT_FLEXPropertyAttributeOldTypeEncoding    = 't',
    RFKT_FLEXPropertyAttributeReadOnly           = 'R',
    RFKT_FLEXPropertyAttributeRetain             = '&',
    RFKT_FLEXPropertyAttributeWeak               = 'W'
};

typedef NS_ENUM(char, RFKT_FLEXTypeEncoding) {
    RFKT_FLEXTypeEncodingNull             = '\0',
    RFKT_FLEXTypeEncodingUnknown          = '?',
    RFKT_FLEXTypeEncodingChar             = 'c',
    RFKT_FLEXTypeEncodingInt              = 'i',
    RFKT_FLEXTypeEncodingShort            = 's',
    RFKT_FLEXTypeEncodingLong             = 'l',
    RFKT_FLEXTypeEncodingLongLong         = 'q',
    RFKT_FLEXTypeEncodingUnsignedChar     = 'C',
    RFKT_FLEXTypeEncodingUnsignedInt      = 'I',
    RFKT_FLEXTypeEncodingUnsignedShort    = 'S',
    RFKT_FLEXTypeEncodingUnsignedLong     = 'L',
    RFKT_FLEXTypeEncodingUnsignedLongLong = 'Q',
    RFKT_FLEXTypeEncodingFloat            = 'f',
    RFKT_FLEXTypeEncodingDouble           = 'd',
    RFKT_FLEXTypeEncodingLongDouble       = 'D',
    RFKT_FLEXTypeEncodingCBool            = 'B',
    RFKT_FLEXTypeEncodingVoid             = 'v',
    RFKT_FLEXTypeEncodingCString          = '*',
    RFKT_FLEXTypeEncodingObjcObject       = '@',
    RFKT_FLEXTypeEncodingObjcClass        = '#',
    RFKT_FLEXTypeEncodingSelector         = ':',
    RFKT_FLEXTypeEncodingArrayBegin       = '[',
    RFKT_FLEXTypeEncodingArrayEnd         = ']',
    RFKT_FLEXTypeEncodingStructBegin      = '{',
    RFKT_FLEXTypeEncodingStructEnd        = '}',
    RFKT_FLEXTypeEncodingUnionBegin       = '(',
    RFKT_FLEXTypeEncodingUnionEnd         = ')',
    RFKT_FLEXTypeEncodingQuote            = '\"',
    RFKT_FLEXTypeEncodingBitField         = 'b',
    RFKT_FLEXTypeEncodingPointer          = '^',
    RFKT_FLEXTypeEncodingConst            = 'r'
};
