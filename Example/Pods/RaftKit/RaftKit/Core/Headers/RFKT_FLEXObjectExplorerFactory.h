//
//  FLEXObjectExplorerFactory.h
//  Flipboard
//
//  Created by Ryan Olson on 5/15/14.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#ifndef _RFKT_FLEXObjectExplorerViewController_h
#import "RFKT_FLEXObjectExplorerViewController.h"
#else
@class RFKT_FLEXObjectExplorerViewController;
#endif

NS_ASSUME_NONNULL_BEGIN

@interface RFKT_FLEXObjectExplorerFactory : NSObject

+ (nullable RFKT_FLEXObjectExplorerViewController *)explorerViewControllerForObject:(nullable id)object;

/// Register a specific explorer view controller class to be used when exploring
/// an object of a specific class. Calls will overwrite existing registrations.
/// Sections must be initialized using \c forObject: like
+ (void)registerExplorerSection:(Class)sectionClass forClass:(Class)objectClass;

+ (Class)explorerSectionClassforClass:(id)object;

@end

NS_ASSUME_NONNULL_END
