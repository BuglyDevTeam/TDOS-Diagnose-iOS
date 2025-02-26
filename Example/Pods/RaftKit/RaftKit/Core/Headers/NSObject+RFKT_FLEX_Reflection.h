//
//  NSObject+RFKT_FLEX_Reflection.h
//  FLEX
//
//  Derived from MirrorKit.
//  Created by Tanner on 6/30/15.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>
@class RFKT_FLEXMirror, RFKT_FLEXMethod, RFKT_FLEXIvar, RFKT_FLEXProperty, RFKT_FLEXMethodBase, RFKT_FLEXPropertyAttributes, RFKT_FLEXProtocol;

NS_ASSUME_NONNULL_BEGIN

/// Returns the type encoding string given the encoding for the return type and parameters, if any.
/// @discussion Example usage for a \c void returning method which takes
/// an \c int: @code RFKT_FLEXTypeEncoding(@encode(void), @encode(int));
/// @param returnType The encoded return type. \c void for exmaple would be \c @encode(void).
/// @param count The number of parameters in this type encoding string.
/// @return The type encoding string, or \c nil if \e returnType is \c NULL.
NSString * RFKT_FLEXTypeEncodingString(const char *returnType, NSUInteger count, ...);

NSArray<Class> *RFKT_FLEXGetAllSubclasses(_Nullable Class cls, BOOL includeSelf);
NSArray<Class> *RFKT_FLEXGetClassHierarchy(_Nullable Class cls, BOOL includeSelf);
NSArray<RFKT_FLEXProtocol *> *RFKT_FLEXGetConformedProtocols(_Nullable Class cls);

NSArray<RFKT_FLEXIvar *> *RFKT_FLEXGetAllIvars(_Nullable Class cls);
/// @param cls a class object to get instance properties,
/// or a metaclass object to get class properties
NSArray<RFKT_FLEXProperty *> *RFKT_FLEXGetAllProperties(_Nullable Class cls);
/// @param cls a class object to get instance methods,
/// or a metaclass object to get class methods
/// @param instance used to mark methods as instance methods or not.
/// Not used to determine whether to get instance or class methods. 
NSArray<RFKT_FLEXMethod *> *RFKT_FLEXGetAllMethods(_Nullable Class cls, BOOL instance);
/// @param cls a class object to get all instance and class methods.
NSArray<RFKT_FLEXMethod *> *RFKT_FLEXGetAllInstanceAndClassMethods(_Nullable Class cls);



#pragma mark Reflection
@interface NSObject (Reflection)

@property (nonatomic, readonly       ) RFKT_FLEXMirror *rfkt_flex_reflection;
@property (nonatomic, readonly, class) RFKT_FLEXMirror *rfkt_flex_reflection;

/// Calls into /c RFKT_FLEXGetAllSubclasses
/// @return Every subclass of the receiving class, including the receiver itself.
@property (nonatomic, readonly, class) NSArray<Class> *rfkt_flex_allSubclasses;

/// @return The \c Class object for the metaclass of the recieving class, or \c Nil if the class is Nil or not registered.
@property (nonatomic, readonly, class) Class rfkt_flex_metaclass;
/// @return The size in bytes of instances of the recieving class, or \c 0 if \e cls is \c Nil.
@property (nonatomic, readonly, class) size_t rfkt_flex_instanceSize;

/// Changes the class of an object instance.
/// @return The previous value of the objects \c class, or \c Nil if the object is \c nil.
- (Class)rfkt_flex_setClass:(Class)cls;
/// Sets the recieving class's superclass. "You should not use this method" — Apple.
/// @return The old superclass.
+ (Class)rfkt_flex_setSuperclass:(Class)superclass;

/// Calls into \c RFKT_FLEXGetClassHierarchy()
/// @return a list of classes going up the class hierarchy,
/// starting with the receiver and ending with the root class.
@property (nonatomic, readonly, class) NSArray<Class> *rfkt_flex_classHierarchy;

/// Calls into \c RFKT_FLEXGetConformedProtocols
/// @return a list of protocols this class itself conforms to.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXProtocol *> *rfkt_flex_protocols;

@end


#pragma mark Methods
@interface NSObject (Methods)

/// All instance and class methods specific to the recieving class.
/// @discussion This method will only retrieve methods specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call this on \c [self superclass].
/// @return An array of \c RFKT_FLEXMethod objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXMethod *> *rfkt_flex_allMethods;
/// All instance methods specific to the recieving class.
/// @discussion This method will only retrieve methods specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call this on \c [self superclass].
/// @return An array of \c RFKT_FLEXMethod objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXMethod *> *rfkt_flex_allInstanceMethods;
/// All class methods specific to the recieving class.
/// @discussion This method will only retrieve methods specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call this on \c [self superclass].
/// @return An array of \c RFKT_FLEXMethod objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXMethod *> *rfkt_flex_allClassMethods;

/// Retrieves the class's instance method with the given name.
/// @return An initialized \c RFKT_FLEXMethod object, or \c nil if the method wasn't found.
+ (RFKT_FLEXMethod *)rfkt_flex_methodNamed:(NSString *)name;

/// Retrieves the class's class method with the given name.
/// @return An initialized \c RFKT_FLEXMethod object, or \c nil if the method wasn't found.
+ (RFKT_FLEXMethod *)rfkt_flex_classMethodNamed:(NSString *)name;

/// Adds a new method to the recieving class with a given name and implementation.
/// @discussion This method will add an override of a superclass's implementation,
/// but will not replace an existing implementation in the class.
/// To change an existing implementation, use \c replaceImplementationOfMethod:with:.
///
/// Type encodings start with the return type and end with the parameter types in order.
/// The type encoding for \c NSArray's \c count property getter looks like this:
/// @code [NSString stringWithFormat:@"%s%s%s%s", @encode(void), @encode(id), @encode(SEL), @encode(NSUInteger)] @endcode
/// Using the \c RFKT_FLEXTypeEncoding function for the same method looks like this:
/// @code RFKT_FLEXTypeEncodingString(@encode(void), 1, @encode(NSUInteger)) @endcode
/// @param typeEncoding The type encoding string. Consider using the \c RFKT_FLEXTypeEncodingString() function.
/// @param instanceMethod NO to add the method to the class itself or YES to add it as an instance method.
/// @return YES if the method was added successfully, \c NO otherwise
/// (for example, the class already contains a method implementation with that name).
+ (BOOL)addMethod:(SEL)selector
     typeEncoding:(NSString *)typeEncoding
   implementation:(IMP)implementaiton
      toInstances:(BOOL)instanceMethod;

/// Replaces the implementation of a method in the recieving class.
/// @param instanceMethod YES to replace the instance method, NO to replace the class method.
/// @note This function behaves in two different ways:
///
/// - If the method does not yet exist in the recieving class, it is added as if
/// \c addMethod:typeEncoding:implementation were called.
///
/// - If the method does exist, its \c IMP is replaced.
/// @return The previous \c IMP of \e method.
+ (IMP)replaceImplementationOfMethod:(RFKT_FLEXMethodBase *)method with:(IMP)implementation useInstance:(BOOL)instanceMethod;
/// Swaps the implementations of the given methods.
/// @discussion If one or neither of the given methods exist in the recieving class,
/// they are added to the class with their implementations swapped as if each method did exist.
/// This method will not fail if each \c RFKT_FLEXSimpleMethod contains a valid selector.
/// @param instanceMethod YES to swizzle the instance method, NO to swizzle the class method.
+ (void)swizzle:(RFKT_FLEXMethodBase *)original with:(RFKT_FLEXMethodBase *)other onInstance:(BOOL)instanceMethod;
/// Swaps the implementations of the given methods.
/// @param instanceMethod YES to swizzle the instance method, NO to swizzle the class method.
/// @return \c YES if successful, and \c NO if selectors could not be retrieved from the given strings.
+ (BOOL)swizzleByName:(NSString *)original with:(NSString *)other onInstance:(BOOL)instanceMethod;
/// Swaps the implementations of methods corresponding to the given selectors.
+ (void)swizzleBySelector:(SEL)original with:(SEL)other onInstance:(BOOL)instanceMethod;

@end


#pragma mark Properties
@interface NSObject (Ivars)

/// All of the instance variables specific to the recieving class.
/// @discussion This method will only retrieve instance varibles specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call \c [[self superclass] allIvars].
/// @return An array of \c RFKT_FLEXIvar objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXIvar *> *rfkt_flex_allIvars;

/// Retrieves an instance variable with the corresponding name.
/// @return An initialized \c RFKT_FLEXIvar object, or \c nil if the Ivar wasn't found.
+ (RFKT_FLEXIvar *)rfkt_flex_ivarNamed:(NSString *)name;

/// @return The address of the given ivar in the recieving object in memory,
/// or \c NULL if it could not be found.
- (void *)rfkt_flex_getIvarAddress:(RFKT_FLEXIvar *)ivar;
/// @return The address of the given ivar in the recieving object in memory,
/// or \c NULL if it could not be found.
- (void *)rfkt_flex_getIvarAddressByName:(NSString *)name;
/// @discussion This method faster than creating an \c RFKT_FLEXIvar and calling
/// \c -getIvarAddress: if you already have an \c Ivar on hand
/// @return The address of the given ivar in the recieving object in memory,
/// or \c NULL if it could not be found\.
- (void *)rfkt_flex_getObjcIvarAddress:(Ivar)ivar;

/// Sets the value of the given instance variable on the recieving object.
/// @discussion Use only when the target instance variable is an object.
- (void)rfkt_flex_setIvar:(RFKT_FLEXIvar *)ivar object:(id)value;
/// Sets the value of the given instance variable on the recieving object.
/// @discussion Use only when the target instance variable is an object.
/// @return \c YES if successful, or \c NO if the instance variable could not be found.
- (BOOL)rfkt_flex_setIvarByName:(NSString *)name object:(id)value;
/// @discussion Use only when the target instance variable is an object.
/// This method is faster than creating an \c RFKT_FLEXIvar and calling
/// \c -setIvar: if you already have an \c Ivar on hand.
- (void)rfkt_flex_setObjcIvar:(Ivar)ivar object:(id)value;

/// Sets the value of the given instance variable on the recieving object to the
/// \e size number of bytes of data at \e value.
/// @discussion Use one of the other methods if you can help it.
- (void)rfkt_flex_setIvar:(RFKT_FLEXIvar *)ivar value:(void *)value size:(size_t)size;
/// Sets the value of the given instance variable on the recieving object to the
/// \e size number of bytes of data at \e value.
/// @discussion Use one of the other methods if you can help it
/// @return \c YES if successful, or \c NO if the instance variable could not be found.
- (BOOL)rfkt_flex_setIvarByName:(NSString *)name value:(void *)value size:(size_t)size;
/// Sets the value of the given instance variable on the recieving object to the
/// \e size number of bytes of data at \e value.
/// @discussion This is faster than creating an \c RFKT_FLEXIvar and calling
/// \c -setIvar:value:size if you already have an \c Ivar on hand.
- (void)rfkt_flex_setObjcIvar:(Ivar)ivar value:(void *)value size:(size_t)size;

@end

#pragma mark Properties
@interface NSObject (Properties)

/// All instance and class properties specific to the recieving class.
/// @discussion This method will only retrieve properties specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call this on \c [self superclass].
/// @return An array of \c RFKT_FLEXProperty objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXProperty *> *rfkt_flex_allProperties;
/// All instance properties specific to the recieving class.
/// @discussion This method will only retrieve properties specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call this on \c [self superclass].
/// @return An array of \c RFKT_FLEXProperty objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXProperty *> *rfkt_flex_allInstanceProperties;
/// All class properties specific to the recieving class.
/// @discussion This method will only retrieve properties specific to the recieving class.
/// To retrieve instance variables on a parent class, simply call this on \c [self superclass].
/// @return An array of \c RFKT_FLEXProperty objects.
@property (nonatomic, readonly, class) NSArray<RFKT_FLEXProperty *> *rfkt_flex_allClassProperties;

/// Retrieves the class's property with the given name.
/// @return An initialized \c RFKT_FLEXProperty object, or \c nil if the property wasn't found.
+ (RFKT_FLEXProperty *)rfkt_flex_propertyNamed:(NSString *)name;
/// @return An initialized \c RFKT_FLEXProperty object, or \c nil if the property wasn't found.
+ (RFKT_FLEXProperty *)rfkt_flex_classPropertyNamed:(NSString *)name;

/// Replaces the given property on the recieving class.
+ (void)rfkt_flex_replaceProperty:(RFKT_FLEXProperty *)property;
/// Replaces the given property on the recieving class. Useful for changing a property's attributes.
+ (void)rfkt_flex_replaceProperty:(NSString *)name attributes:(RFKT_FLEXPropertyAttributes *)attributes;

@end

NS_ASSUME_NONNULL_END
