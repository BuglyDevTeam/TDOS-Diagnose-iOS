//
//  IRTransformData.h
//
//  Created by RAFT on 2021/5/10.
//
@protocol IChannelTokenInfo <NSObject>

@property(nonatomic, assign) long            tokenType;
@property(nonatomic, strong) NSData*         token;
@property(nonatomic, strong) NSData*         openId;

@end

@protocol IRTransformArgs <NSObject>

@property(nonatomic, strong) NSData*                                data;                // 业务请求二进制内容
@property(nonatomic, strong) NSString*                              command;             // 请求命令字
@property(nonatomic, assign) NSUInteger                             timeout;             // 超时时间
@property(nonatomic, assign) NSUInteger                             retryCnt;            // 客户端端重试次数
@property(nonatomic, assign) NSInteger                              priority;            // 请求优先级
@property(nonatomic, assign) BOOL                                   busiBufUpFlag;       // 上行包是否加压
@property(nonatomic, assign) BOOL                                   busiBufDownFlag;     // 是否支持下行包加压
@property(nonatomic, assign) BOOL                                   isSupportReentry;    //业务后台是否支持重入请求
@property(nonatomic, assign) BOOL                                   isHighRealTimeReq;   // 是否高实时命令字
@property(nonatomic, strong) NSString*                              uid;                 // user id
@property(nonatomic, assign) BOOL                                   isAnony;             // 是否匿名
@property(nonatomic, strong) NSObject<IChannelTokenInfo>*           tokenInfo;           // token数据
@property(nonatomic, strong) NSDictionary<NSString*, NSString*>*    extraDictionary;     // 扩展字段,用于一些特定的场景需求

@end


@protocol IRTransformResult <NSObject>

@property(nonatomic, assign) NSInteger                              sdkCode;            //客户端层返回码
@property(nonatomic, assign) NSInteger                              serverCode;         //后台返回码
@property(nonatomic, assign) NSInteger                              bizCode;            //业务层返回码
@property(nonatomic, strong) NSData*                                data;               // 业务层返回数据
@property(nonatomic, strong) NSString*                              businessMessage;    // 异常错误信息
@property(nonatomic, strong) NSString*                              sdkMsg;             // SDK层异常错误信息
@property(nonatomic, strong) NSDictionary<NSString*, NSString*>*    extraDictionary;    // 扩展字段,回带部分wns连接状态，以便业务关联数据上报

@end

