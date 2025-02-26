//
//  FLEXRuntime+Compare.h
//  FLEX
//
//  Created by Tanner Bennett on 8/28/19.
//  Copyright © 2020 FLEX Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RFKT_FLEXProperty.h"
#import "RFKT_FLEXIvar.h"
#import "RFKT_FLEXMethodBase.h"
#import "RFKT_FLEXProtocol.h"

@interface RFKT_FLEXProperty (Compare)
- (NSComparisonResult)compare:(RFKT_FLEXProperty *)other;
@end

@interface RFKT_FLEXIvar (Compare)
- (NSComparisonResult)compare:(RFKT_FLEXIvar *)other;
@end

@interface RFKT_FLEXMethodBase (Compare)
- (NSComparisonResult)compare:(RFKT_FLEXMethodBase *)other;
@end

@interface RFKT_FLEXProtocol (Compare)
- (NSComparisonResult)compare:(RFKT_FLEXProtocol *)other;
@end
