//
//  RAFTMeasureReporter.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RAFTMeasureReportDefines.h"
@class RAFTMeasureStartUpReportItem;
@class RAFTMeasureSLIReportItem;

NS_ASSUME_NONNULL_BEGIN

/**
    RAFTMeasure上报器
        上报表AttaID：08500061666
        Atta对应链接：https://atta.woa.com/#/dataManage/myData/attaIdDetail?attaid=08500061666
 */
@interface RAFTMeasureReporter : NSObject

// 发起上报
- (void)report:(id<RAFTMeasureReportParamProtocol>)reportItem;

@end

NS_ASSUME_NONNULL_END
