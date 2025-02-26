//
//  FLEXColorPreviewSection.h
//  FLEX
//
//  Created by Tanner Bennett on 12/12/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXSingleRowSection.h"
#import "RFKT_FLEXObjectInfoSection.h"

@interface RFKT_FLEXColorPreviewSection : RFKT_FLEXSingleRowSection <RFKT_FLEXObjectInfoSection>

+ (instancetype)forObject:(UIColor *)color;

@end
