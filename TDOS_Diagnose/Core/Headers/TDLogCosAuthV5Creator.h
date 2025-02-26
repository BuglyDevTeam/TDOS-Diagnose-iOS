//   
//  TDLogCosAuthV5Creator.h
//  TDiagnose
//  
//  Created by raycgwang on 2021/12/24.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//
//  本文件修改自腾讯云COS SDK：QCloudAuthentationV5Creator

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 COS V5 （XML）版本签名创建器。强烈不推荐在线上版本中使用。请使用服务器获取签名的模式来使用签名。如果您使用改类，请配合临时密钥CAM服务使用。

 @note 强烈不推荐在线上版本中使用。请使用服务器获取签名的模式来使用签名。如果您使用改类，请配合临时密钥CAM服务使用。

 ### 示例

  @code

    QCloudCredential* credential = [QCloudCredential new];
    credential.secretID = kSecretIDCSP;
    credential.secretKey = kSecretKeyCSP;
    credential.expirationDate = [NSDate dateWithTimeIntervalSince1970:1504183628];
    QCloudAuthentationV5Creator* creator = [[QCloudAuthentationV5Creator alloc] initWithCredential:credential];
    QCloudSignature* signature =  [creator signatureForData:urlRequst];

 */
@interface TDLogCosAuthV5Creator : NSObject


/**
 开发者拥有的项目身份识别 ID，用以身份认证
 */
@property (nonatomic, strong) NSString *secretID;

/**
开发者拥有的项目身份密钥。可以为永久密钥，也可以是临时密钥（参考CAM系统）。
 */
@property (nonatomic, strong) NSString *secretKey;

/**
 签名有效期的起始时间。默认是设备的本地时间，如果传入起始时间，那么将以起始时间去计算签名。
 */
@property (nonatomic, strong) NSDate *startDate;

/**
 签名有效期截止的时间。没有设置的话，默认是起始时间加十分钟。
 */
@property (nonatomic, strong) NSDate *expirationDate;

/**
 改签名是否有效。
 */
@property (nonatomic, assign, readonly) BOOL valid;

/**
 当您使用了CAM系统获取临时密钥的时候，请设置改值，代表回话的ID。
 */
@property (nonatomic, strong) NSString *token;



@property (nonatomic, strong) NSString *tokenHeaderName;
/**
 自定义需要签名的属性列表：如果不传使用sdk默认的签名规则,设置为@[]表示不签任何头部和参数
 */
@property (nonatomic, strong) NSArray *shouldSignedList;

- (NSString *)signatureForData:(NSMutableURLRequest *)signData;

@end

NS_ASSUME_NONNULL_END
