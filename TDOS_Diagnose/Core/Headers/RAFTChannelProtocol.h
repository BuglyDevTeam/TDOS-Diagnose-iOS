//
//  RAFTChannelProtocol.h
//
//  Created by RAFT on 2021/5/10.
//
#import "IRTransformData.h"

#ifndef RAFTChannelProtocol_h
#define RAFTChannelProtocol_h

@protocol ITransferCallbackProtocol <NSObject>

@required

/**! @brief 传输结束回调
*  @param requestdata response
*/
- (void)onTransferFinished:(id<IRTransformArgs>)requestdata result:(id<IRTransformResult>)response;

@end


@protocol RAFTChannelProtocol <NSObject>

@required

/**! @brief 数据传输
*  @param args WNS初始化参数
*  @param delegate 请求结果回调
*  @return 请求seqno，用于cancelRequest
*/
- (long)transfer:(id<IRTransformArgs>)args delegate:(id<ITransferCallbackProtocol>)delegate;

/**! @brief 取消数据传输
* @seqno 请求序列号。
*/
- (void)cancelRequest:(long)seqno;

@end
#endif /* RAFTChannelProtocol_h */
