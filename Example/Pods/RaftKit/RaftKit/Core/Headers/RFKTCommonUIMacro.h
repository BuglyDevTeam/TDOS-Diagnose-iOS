//
//  RFKTCommonUIMacro.h
//
//  Copyright © 2021年 RaftKit Team. All rights reserved.
//

#ifndef RFKTCommonUIMacro_h
#define RFKTCommonUIMacro_h

#import <Foundation/Foundation.h>
#import "RFKTUIHelper.h"

#pragma mark - Colors & Fonts

#define UIColorMake(r, g, b)                [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1]
#define UIColorMakeWithRGBA(r, g, b, a)     [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a/1.0]
#define UIFontMake(size)                    [UIFont systemFontOfSize:size]
#define UIFontItalicMake(size)              [UIFont italicSystemFontOfSize:size]
#define UIFontBoldMake(size)                [UIFont boldSystemFontOfSize:size]
#define UIFontBoldWithFont(_font)           [UIFont boldSystemFontOfSize:_font.pointSize]

#define RFKT_THEME_COLOR UIColorBlue6 // TDesign Brand6

#define UIColorGray1 UIColorMake(53, 60, 70)
#define UIColorGray2 UIColorMake(73, 80, 90)
#define UIColorGray3 UIColorMake(93, 100, 110)
#define UIColorGray4 UIColorMake(113, 120, 130)
#define UIColorGray5 UIColorMake(133, 140, 150)
#define UIColorGray6 UIColorMake(153, 160, 170)
#define UIColorGray7 UIColorMake(173, 180, 190)
#define UIColorGray8 UIColorMake(196, 200, 208)
#define UIColorGray9 UIColorMake(216, 220, 228)

#define UIColorDarkGray1 UIColorMake(218, 220, 224)
#define UIColorDarkGray2 UIColorMake(198, 200, 204)
#define UIColorDarkGray3 UIColorMake(178, 180, 184)
#define UIColorDarkGray4 UIColorMake(158, 160, 164)
#define UIColorDarkGray5 UIColorMake(138, 140, 144)
#define UIColorDarkGray6 UIColorMake(118, 120, 124)
#define UIColorDarkGray7 UIColorMake(98, 100, 104)
#define UIColorDarkGray8 UIColorMake(78, 80, 84)
#define UIColorDarkGray9 UIColorMake(58, 60, 64)

#pragma mark - TDesign
#define UIColorBlue1 UIColorMake(0xdf, 0xef, 0xff)
#define UIColorBlue2 UIColorMake(0xbf, 0xdb, 0xf7)
#define UIColorBlue3 UIColorMake(0x9b, 0xc5, 0xf2)
#define UIColorBlue4 UIColorMake(0x7b, 0xaf, 0xed)
#define UIColorBlue5 UIColorMake(0x5c, 0x99, 0xeb)
#define UIColorBlue6 UIColorMake(0x38, 0x81, 0xe8)
#define UIColorBlue7 UIColorMake(0x20, 0x6a, 0xe1)
#define UIColorBlue8 UIColorMake(0x00, 0x52, 0xd9)
#define UIColorBlue9 UIColorMake(0x00, 0x3c, 0xbe)
#define UIColorBlue10 UIColorMake(0x00, 0x26, 0xa1)

#define UIColorRed1 UIColorMake(0xff, 0xe9, 0xe9)
#define UIColorRed2 UIColorMake(0xff, 0xcc, 0xce)
#define UIColorRed3 UIColorMake(0xff, 0xac, 0xaf)
#define UIColorRed4 UIColorMake(0xff, 0x88, 0x8c)
#define UIColorRed5 UIColorMake(0xfb, 0x64, 0x6d)
#define UIColorRed6 UIColorMake(0xe3, 0x4d, 0x59)
#define UIColorRed7 UIColorMake(0xc9, 0x30, 0x43)
#define UIColorRed8 UIColorMake(0xb0, 0x15, 0x31)
#define UIColorRed9 UIColorMake(0x96, 0x00, 0x22)
#define UIColorRed10 UIColorMake(0x73, 0x00, 0x21)

#define UIColorOrange1 UIColorMake(0xff, 0xef, 0xdb)
#define UIColorOrange2 UIColorMake(0xff, 0xd3, 0xa3)
#define UIColorOrange3 UIColorMake(0xff, 0xb4, 0x73)
#define UIColorOrange4 UIColorMake(0xff, 0x92, 0x47)
#define UIColorOrange5 UIColorMake(0xed, 0x7b, 0x2f)
#define UIColorOrange6 UIColorMake(0xd6, 0x62, 0x1c)
#define UIColorOrange7 UIColorMake(0xc2, 0x4c, 0x08)
#define UIColorOrange8 UIColorMake(0xa2, 0x3c, 0x00)
#define UIColorOrange9 UIColorMake(0x87, 0x2d, 0x00)
#define UIColorOrange10 UIColorMake(0x69, 0x1f, 0x00)

#define UIColorGreen1 UIColorMake(0xdf, 0xf7, 0xed)
#define UIColorGreen2 UIColorMake(0xa9, 0xe8, 0xcd)
#define UIColorGreen3 UIColorMake(0x69, 0xd5, 0xab)
#define UIColorGreen4 UIColorMake(0x30, 0xbf, 0x8b)
#define UIColorGreen5 UIColorMake(0x00, 0xa8, 0x70)
#define UIColorGreen6 UIColorMake(0x00, 0x93, 0x5d)
#define UIColorGreen7 UIColorMake(0x00, 0x7e, 0x4a)
#define UIColorGreen8 UIColorMake(0x00, 0x69, 0x37)
#define UIColorGreen9 UIColorMake(0x00, 0x54, 0x26)
#define UIColorGreen10 UIColorMake(0x00, 0x41, 0x14)

#define UIColorTheme1 UIColorMake(239, 83, 98) // Grapefruit
#define UIColorTheme2 UIColorMake(254, 109, 75) // Bittersweet
#define UIColorTheme3 UIColorMake(255, 207, 71) // Sunflower
#define UIColorTheme4 UIColorMake(159, 214, 97) // Grass
#define UIColorTheme5 UIColorMake(63, 208, 173) // Mint
#define UIColorTheme6 UIColorMake(49, 189, 243) // Aqua
#define UIColorTheme7 UIColorMake(90, 154, 239) // Blue Jeans
#define UIColorTheme8 UIColorMake(172, 143, 239) // Lavender
#define UIColorTheme9 UIColorMake(238, 133, 193) // Pink Rose
#define UIColorTheme10 UIColorMake(39, 192, 243) // Dark


#pragma mark - System Colors

#define SystemGray6Color UIColorMake(0xf2, 0xf2, 0xf7) // UIColor.systemGray6Color
#define SystemGray3Color UIColorMake(0xc7, 0xc7, 0xcc) // UIColor.systemGray3Color


#endif /* RFKTCommonUIMacro_h */
