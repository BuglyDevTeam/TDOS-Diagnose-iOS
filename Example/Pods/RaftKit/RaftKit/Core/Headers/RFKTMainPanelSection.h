//   
//  RFKTMainPanelSection.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/19.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    RFKTMainPanelSectionTypeCustom = 0,
    RFKTMainPanelSectionTypeBuiltin = 1000,
    RFKTMainPanelSectionTypeRecentUsed = 2000,
} RFKTMainPanelSectionType;


/// 主面板Section
@interface RFKTMainPanelSection : NSObject <NSCopying>

/// Section标题
@property (nonatomic, strong) NSString *sectionName;
/// Section类型
@property (nonatomic, assign) NSUInteger sectionType;
/// Section优先级
@property (nonatomic, assign) NSUInteger displayPiority;

@end

NS_ASSUME_NONNULL_END
