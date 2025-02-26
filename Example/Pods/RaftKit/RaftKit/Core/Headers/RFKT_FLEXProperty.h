//
//  FLEXProperty.h
//  FLEX
//
//  Derived from MirrorKit.
//  Created by Tanner on 6/30/15.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXRuntimeConstants.h"
@class RFKT_FLEXPropertyAttributes, RFKT_FLEXMethodBase;


#pragma mark RFKT_FLEXProperty
@interface RFKT_FLEXProperty : NSObject

/// You may use this initializer instead of \c property:onClass: if you don't need
/// to know anything about the uniqueness of this property or where it comes from.
+ (instancetype)property:(objc_property_t)property;
/// This initializer can be used to access additional information
/// in an efficient manner. That information being whether this property
/// is certainly not unique and the name of the binary image which declares it.
/// @param cls the class, or metaclass if this is a class property.
+ (instancetype)property:(objc_property_t)property onClass:(Class)cls;
/// @param cls the class, or metaclass if this is a class property
+ (instancetype)named:(NSString *)name onClass:(Class)cls;
/// Constructs a new property with the given name and attributes.
+ (instancetype)propertyWithName:(NSString *)name attributes:(RFKT_FLEXPropertyAttributes *)attributes;

/// \c 0 if the instance was created via \c +propertyWithName:attributes,
/// otherwise this is the first property in \c objc_properties
@property (nonatomic, readonly) objc_property_t  objc_property;
@property (nonatomic, readonly) objc_property_t  *objc_properties;
@property (nonatomic, readonly) NSInteger        objc_propertyCount;
@property (nonatomic, readonly) BOOL             isClassProperty;

/// The name of the property.
@property (nonatomic, readonly) NSString         *name;
/// The type of the property. Get the full type from the attributes.
@property (nonatomic, readonly) RFKT_FLEXTypeEncoding type;
/// The property's attributes.
@property (nonatomic          ) RFKT_FLEXPropertyAttributes *attributes;
/// The (likely) setter, regardless of whether the property is readonly.
/// For example, this might be the custom setter.
@property (nonatomic, readonly) SEL likelySetter;
@property (nonatomic, readonly) NSString *likelySetterString;
/// Not valid unless initialized with the owning class.
@property (nonatomic, readonly) BOOL likelySetterExists;
/// The (likely) getter. For example, this might be the custom getter.
@property (nonatomic, readonly) SEL likelyGetter;
@property (nonatomic, readonly) NSString *likelyGetterString;
/// Not valid unless initialized with the owning class.
@property (nonatomic, readonly) BOOL likelyGetterExists;

/// Whether there are certainly multiple definitions of this property,
/// such as in categories in other binary images or something.
/// @return Whether \c objc_property matches the return value of \c class_getProperty,
/// or \c NO if this property was not created with \c property:onClass
@property (nonatomic, readonly) BOOL multiple;
/// @return The bundle of the image that contains this property definition,
/// or \c nil if this property was not created with \c property:onClass or
/// if this property was probably defined at runtime.
@property (nonatomic, readonly) NSString *imageName;
/// The full path of the image that contains this property definition,
/// or \c nil if this property was not created with \c property:onClass or
/// if this property was probably defined at runtime.
@property (nonatomic, readonly) NSString *imagePath;

/// For internal use
@property (nonatomic) id tag;

/// @return The value of this property on \c target as given by \c -valueForKey:
/// A source-like description of the property, with all of its attributes.
@property (nonatomic, readonly) NSString *fullDescription;

/// If this is a class property, you must class the class object.
- (id)getValue:(id)target;
/// Calls into -getValue: and passes that value into
/// -[RFKT_FLEXRuntimeUtility potentiallyUnwrapBoxedPointer:type:]
/// and returns the result.
///
/// If this is a class property, you must class the class object.
- (id)getPotentiallyUnboxedValue:(id)target;

/// Safe to use regardless of how the \c RFKT_FLEXProperty instance was initialized.
///
/// This uses \c self.objc_property if it exists, otherwise it uses \c self.attributes
- (objc_property_attribute_t *)copyAttributesList:(unsigned int *)attributesCount;

/// Replace the attributes of the current property in the given class,
/// using the attributes in \c self.attributes
///
/// What happens when the property does not exist is undocumented.
- (void)replacePropertyOnClass:(Class)cls;

#pragma mark Convenience getters and setters
/// @return A getter for the property with the given implementation.
/// @discussion Consider using the \c RFKT_FLEXPropertyGetter macros.
- (RFKT_FLEXMethodBase *)getterWithImplementation:(IMP)implementation;
/// @return A setter for the property with the given implementation.
/// @discussion Consider using the \c RFKT_FLEXPropertySetter macros.
- (RFKT_FLEXMethodBase *)setterWithImplementation:(IMP)implementation;

#pragma mark RFKT_FLEXMethod property getter / setter macros
// Easier than using the above methods yourself in most cases

/// Takes a \c RFKT_FLEXProperty and a type (ie \c NSUInteger or \c id) and
/// uses the \c RFKT_FLEXProperty's \c attribute's \c backingIvarName to get the Ivar.
#define RFKT_FLEXPropertyGetter(RFKT_FLEXProperty, type) [RFKT_FLEXProperty \
    getterWithImplementation:imp_implementationWithBlock(^(id self) { \
        return *(type *)[self getIvarAddressByName:RFKT_FLEXProperty.attributes.backingIvar]; \
    }) \
];
/// Takes a \c RFKT_FLEXProperty and a type (ie \c NSUInteger or \c id) and
/// uses the \c RFKT_FLEXProperty's \c attribute's \c backingIvarName to set the Ivar.
#define RFKT_FLEXPropertySetter(RFKT_FLEXProperty, type) [RFKT_FLEXProperty \
    setterWithImplementation:imp_implementationWithBlock(^(id self, type value) { \
        [self setIvarByName:RFKT_FLEXProperty.attributes.backingIvar value:&value size:sizeof(type)]; \
    }) \
];
/// Takes a \c RFKT_FLEXProperty and a type (ie \c NSUInteger or \c id) and an Ivar name string to get the Ivar.
#define RFKT_FLEXPropertyGetterWithIvar(RFKT_FLEXProperty, ivarName, type) [RFKT_FLEXProperty \
    getterWithImplementation:imp_implementationWithBlock(^(id self) { \
        return *(type *)[self getIvarAddressByName:ivarName]; \
    }) \
];
/// Takes a \c RFKT_FLEXProperty and a type (ie \c NSUInteger or \c id) and an Ivar name string to set the Ivar.
#define RFKT_FLEXPropertySetterWithIvar(RFKT_FLEXProperty, ivarName, type) [RFKT_FLEXProperty \
    setterWithImplementation:imp_implementationWithBlock(^(id self, type value) { \
        [self setIvarByName:ivarName value:&value size:sizeof(type)]; \
    }) \
];

@end
