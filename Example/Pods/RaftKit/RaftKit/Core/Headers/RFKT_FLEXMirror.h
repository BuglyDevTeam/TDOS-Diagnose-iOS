//
//  FLEXMirror.h
//  FLEX
//
//  Derived from MirrorKit.
//  Created by Tanner on 6/29/15.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>
@class RFKT_FLEXMethod, RFKT_FLEXProperty, RFKT_FLEXIvar, RFKT_FLEXProtocol;
#import <objc/runtime.h>


#pragma mark RFKT_FLEXMirror
@interface RFKT_FLEXMirror : NSObject

/// Reflects an instance of an object or \c Class.
/// @discussion \c RFKT_FLEXMirror will immediately gather all useful information. Consider using the
/// \c NSObject categories provided if your code will only use a few pieces of information,
/// or if your code needs to run faster.
///
/// If you reflect an instance of a class then \c methods and \c properties will be populated
/// with instance methods and properties. If you reflect a class itself, then \c methods
/// and \c properties will be populated with class methods and properties as you'd expect.
///
/// @param objectOrClass An instance of an objct or a \c Class object.
/// @return An instance of \c RFKT_FLEXMirror.
+ (instancetype)reflect:(id)objectOrClass;

/// The underlying object or \c Class used to create this \c RFKT_FLEXMirror instance.
@property (nonatomic, readonly) id   value;
/// Whether the reflected thing was a class or a class instance.
@property (nonatomic, readonly) BOOL isClass;
/// The name of the \c Class of the \c value property.
@property (nonatomic, readonly) NSString *className;

@property (nonatomic, readonly) NSArray<RFKT_FLEXProperty *> *properties;
@property (nonatomic, readonly) NSArray<RFKT_FLEXIvar *>     *ivars;
@property (nonatomic, readonly) NSArray<RFKT_FLEXMethod *>   *methods;
@property (nonatomic, readonly) NSArray<RFKT_FLEXProtocol *> *protocols;

/// @return A reflection of \c value.superClass.
@property (nonatomic, readonly) RFKT_FLEXMirror *superMirror;

@end


@interface RFKT_FLEXMirror (ExtendedMirror)

/// @return The method with the given name, or \c nil if one does not exist.
- (RFKT_FLEXMethod *)methodNamed:(NSString *)name;
/// @return The property with the given name, or \c nil if one does not exist.
- (RFKT_FLEXProperty *)propertyNamed:(NSString *)name;
/// @return The instance variable with the given name, or \c nil if one does not exist.
- (RFKT_FLEXIvar *)ivarNamed:(NSString *)name;
/// @return The protocol with the given name, or \c nil if one does not exist.
- (RFKT_FLEXProtocol *)protocolNamed:(NSString *)name;

@end
