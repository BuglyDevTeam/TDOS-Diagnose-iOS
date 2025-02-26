//   
//  RFKTConnection.h
//  RaftKit
//  
//  Created by raycgwang on 2021/3/25.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#ifndef RFKTConnection_h
#define RFKTConnection_h

NS_ASSUME_NONNULL_BEGIN

@class RFKTBaseMsg;
typedef void (^RFKTDispatchedMsgHandler)(RFKTBaseMsg *msg);

/// A Connection between "datasource" and "ui"
@protocol RFKTConnection <NSObject>

/// Register a receiver to be notified of incoming calls of the given method
/// from the desktop plugin with a matching identifier.
/// @param cmd identifier
/// @param subscriber id
/// @param handler actionblock
- (void)receive:(NSString *)cmd subscriber:(id)subscriber withBlock:(RFKTDispatchedMsgHandler)handler;

/// Reply to request message with only data
/// @param reqMsg the request msg
/// @param params the params dict
- (void)replyToReqMsg:(RFKTBaseMsg *)reqMsg withParams:(NSDictionary *)params;

/// Reply to request message with only data
/// @param reqMsg the request msg
/// @param data the body
- (void)replyToReqMsg:(RFKTBaseMsg *)reqMsg withData:(id)data;

/// Reply to request message with more info
/// @param reqMsg the request msg
/// @param code error Code
/// @param errMsg error Message
/// @param data extra data
- (void)replyToReqMsg:(RFKTBaseMsg *)reqMsg
           resultCode:(NSString *)code
                error:(nullable NSString *)errMsg
            extraData:(nullable NSString *)data;

/// 发送广播
/// @param cmd command string
/// @param params dict
- (void)sendBroadcast:(NSString *)cmd withParams:(NSDictionary *)params;

@end

NS_ASSUME_NONNULL_END

#endif /* RFKTConnection_h */
