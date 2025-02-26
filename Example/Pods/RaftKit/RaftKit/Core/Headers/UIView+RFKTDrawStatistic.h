//
//  UIView+DrawStatistic.h
//  RaftKit
//
//  Created by 张鹏 on 16/9/6.
//  Copyright © 2016年 com.tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UIView (RFKTDrawStatistic)

+ (void)rfkt_hook;
+ (long)rfkt_getAllDrawCount;
+ (void)rfkt_clearDrawCount;

@end
