//
//  FLEXImageShortcuts.h
//  FLEX
//
//  Created by Tanner Bennett on 8/29/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXShortcutsSection.h"

/// Provides "view image" and "save image" shortcuts for UIImage objects
@interface RFKT_FLEXImageShortcuts : RFKT_FLEXShortcutsSection

+ (instancetype)forObject:(UIImage *)image;

@end
