//
//  RAFTBeaconProtocol.h
//
//  Created by RAFT on 2021/5/10.
//  Copyright © 2021 RAFT. All rights reserved.
//
#import "IBaseEvent.h"

#ifndef RAFTBeaconProtocol_h
#define RAFTBeaconProtocol_h
@protocol RAFTBeaconProtocol <NSObject>

/**! @brief 上报事件
*  @param event event
*  @return bool report success or not
*/
- (BOOL)report:(id<IBaseEvent>)event businessId:(NSString *)businessId;

@end
#endif /* RAFTBeaconProtocol_h */
