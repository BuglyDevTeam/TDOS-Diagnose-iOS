//
//  FLEXManager+Private.h
//  PebbleApp
//
//  Created by Javier Soto on 7/26/14.
//  Copyright (c) 2020 FLEX Team. All rights reserved.
//

#import "RFKT_FLEXManager.h"
#import "RFKTWindow.h"

@class RFKT_FLEXGlobalsEntry, RFKT_FLEXExplorerViewController;

@interface RFKT_FLEXManager (Private)

@property (nonatomic, readonly) RFKTWindow *explorerWindow;
@property (nonatomic, readonly) RFKT_FLEXExplorerViewController *explorerViewController;

/// An array of RFKT_FLEXGlobalsEntry objects that have been registered by the user.
@property (nonatomic, readonly) NSMutableArray<RFKT_FLEXGlobalsEntry *> *userGlobalEntries;
@property (nonatomic, readonly) NSMutableDictionary<NSString *, RFKT_FLEXCustomContentViewerFuture> *customContentTypeViewers;

@end
