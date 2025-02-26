//   
//  RFKTMsgDispatcher.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>
#import "RFKTMsg.h"
#import "RFKTConnection.h"

NS_ASSUME_NONNULL_BEGIN

@interface RFKTMsgDispatcher : NSObject

/// Singleton
+ (instancetype)sharedInstance;

/// Dispatch Message
/// @param msg RFKTMsg object
- (BOOL)dispatchMessage:(RFKTBaseMsg *)msg;

/// Subscribe Message
/// @param subscriber id
/// @param cmd string
/// @param action callback
- (BOOL)registSubscriber:(NSObject *)subscriber withCmd:(NSString *)cmd andAction:(RFKTDispatchedMsgHandler)action;

/// Subscribe Message only once
- (BOOL)registSubscriberOnce:(NSObject *)subscriber withCmd:(NSString *)cmd andAction:(RFKTDispatchedMsgHandler)action;

/// Unsubscribe for a particular command for a particular object
- (BOOL)unregistSubscriber:(NSObject *)subscriber withCmd:(NSString *)cmd;

/// Unsubscribe for a particular command for all objects
- (BOOL)unregistSubscribersForCmd:(NSString *)cmd;

/// Clear subscribers for all commands
- (void)clearAllSubscribers;

@end

NS_ASSUME_NONNULL_END
