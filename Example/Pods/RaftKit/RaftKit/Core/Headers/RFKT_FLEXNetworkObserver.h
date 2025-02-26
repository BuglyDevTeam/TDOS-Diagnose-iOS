//
//  RFKT_FLEXNetworkObserver.h
//  Derived from:
//
//  PDAFNetworkDomainController.h
//  PonyDebugger
//
//  Created by Mike Lewis on 2/27/12.
//
//  Licensed to Square, Inc. under one or more contributor license agreements.
//  See the LICENSE file distributed with this work for the terms under
//  which Square, Inc. licenses this file to you.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXTERN NSString * const kRFKT_FLEXNetworkObserverEnabledStateChangedNotification;
FOUNDATION_EXTERN NSString * const kRFKTWeakNetSwitchKey;
FOUNDATION_EXTERN NSString * const kRFKTWeakNetDelayTimeKey;

/// This class swizzles NSURLConnection and NSURLSession delegate methods to observe events in the URL loading system.
/// High level network events are sent to the default RFKT_FLEXNetworkRecorder instance which maintains the request history and caches response bodies.
@interface RFKT_FLEXNetworkObserver : NSObject

/// Swizzling occurs when the observer is enabled for the first time.
/// This reduces the impact of RFKT_FLEX if network debugging is not desired.
/// NOTE: this setting persists between launches of the app.
@property (nonatomic, class, getter=isEnabled) BOOL enabled;

/// Swizzling occurs when weakNetSimulation is enabled for the first time.
@property (nonatomic, class, getter=isWeakNetSimuEnabled) BOOL weakNetSimuEnabled;

@end
