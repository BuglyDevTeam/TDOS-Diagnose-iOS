//   
//  RFKTMsg.h
//  RaftKit
//  
//  Created by raycgwang on 2021/6/24.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import "RFKT_JSONModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : int {
    RFKTMsgType_Plat,   // 平台交互
    RFKTMsgType_Req,    // 请求包
    RFKTMsgType_Rsp,    // 回包
} RFKTMsgType;


/// Json msg between client and server
@interface RFKTBaseMsg : RFKT_JSONModel

#pragma mark - Required
/// cmd
@property (nonatomic, copy) NSString *cmd;
/// cmd type
@property (nonatomic, assign) RFKTMsgType type;

#pragma mark - Optional
/// sub cmd
@property (nonatomic, copy) NSString<Optional> *subcmd;
/// cmd version
@property (nonatomic, copy) NSString<Optional> *ver;
/// data field (body)
@property (nonatomic, copy) NSString<Optional> *data;
/// rsp code
@property (nonatomic, copy) NSString<Optional> *code;
/// error info
@property (nonatomic, copy) NSString<Optional> *error;

/// the room id
@property (nonatomic, copy) NSString<Optional> *roomid;
/// the remote peer id
@property (nonatomic, copy) NSString<Optional> *remoteid;

#pragma mark - 拆包支持
/// 拆分后数据包总数
@property (nonatomic, copy) NSString<Optional> *packageCount;
/// 拆分后数据包index
@property (nonatomic, copy) NSString<Optional> *packageIndex;
/// 数据包整体的唯一ID，所有子数据包相同UUID
@property (nonatomic, copy) NSString<Optional> *packageUUID;
/// 数据包整体data的Md5，注意不是单个sub package的md5
@property (nonatomic, copy) NSString<Optional> *packageMD5;


#pragma mark - Convenient Methods

/// 构造平台请求消息
/// @param cmd 命令字
/// @param data 内容
+ (instancetype)platformMsg:(NSString *)cmd andData:(nullable NSString *)data;

/// 构造平台
/// @param cmd 命令字
/// @param errorCode 错误码
/// @param data 内容
/// @param error 错误信息
+ (instancetype)platformMsg:(NSString *)cmd code:(NSString *)errorCode data:(nullable NSString *)data andError:(nullable NSString *)error;

/// 构造透传请求消息
/// @param cmd 命令字
/// @param data 内容
+ (instancetype)transReqMsg:(NSString *)cmd andData:(nullable NSString *)data;

/// 构造透传错误消息
/// @param cmd 命令字
/// @param errorCode 错误码
/// @param data 内容
/// @param error 错误描述
+ (instancetype)transRspMsg:(NSString *)cmd code:(NSString *)errorCode data:(nullable NSString *)data andError:(nullable NSString *)error;

/// 从请求包构造回包
/// @param reqMsg 请求包
+ (instancetype)transRspMsgFromReqMsg:(RFKTBaseMsg *)reqMsg;

@end


NS_ASSUME_NONNULL_END
