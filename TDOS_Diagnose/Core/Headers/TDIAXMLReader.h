//
//  XMLReader.h
//
//  Created by Troy Brant on 9/18/10.
//  Updated by Antoine Marcadet on 9/23/11.
//  Updated by Divan Visagie on 2012-08-26
//  Copyright © 2021 XMLReader. All rights reserved.

#import <Foundation/Foundation.h>

enum {
    TDIAXMLReaderOptionsProcessNamespaces    = 1 << 0, // Specifies whether the receiver reports the namespace and the qualified name of an element.
    TDIAXMLReaderOptionsReportNamespacePrefixes    = 1 << 1, // Specifies whether the receiver reports the scope of namespace declarations.
    TDIAXMLReaderOptionsResolveExternalEntities    = 1 << 2, // Specifies whether the receiver reports declarations of external entities.
};
typedef NSUInteger TDIAXMLReaderOptions;

@interface TDIAXMLReader : NSObject <NSXMLParserDelegate>

+ (NSDictionary *)dictionaryForXMLData:(NSData *)data error:(NSError **)errorPointer;
+ (NSDictionary *)dictionaryForXMLString:(NSString *)string error:(NSError **)errorPointer;
+ (NSDictionary *)dictionaryForXMLData:(NSData *)data options:(TDIAXMLReaderOptions)options error:(NSError **)errorPointer;
+ (NSDictionary *)dictionaryForXMLString:(NSString *)string options:(TDIAXMLReaderOptions)options error:(NSError **)errorPointer;

@end
