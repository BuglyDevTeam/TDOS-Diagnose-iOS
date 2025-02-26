//   
//  RFKTLogViewer.h
//  RaftKit
//  
//  Created by raycgwang on 2021/7/15.
//  Copyright © 2021 RaftKit Team. All rights reserved.
//  

#import <UIKit/UIKit.h>
#import "RFKTDataProvider.h"

NS_ASSUME_NONNULL_BEGIN

@class RFKTLogViewerConfig;
@class RFKTLogViewer;

@protocol RFKTLogViewerDelegate <NSObject>

/// Called when user pressed close btn.
/// @param logViewer ObjectType
///
/// return NO if close action fail.
- (BOOL)onLogViewerWantsToClose:(RFKTLogViewer *)logViewer;

/// Called when user pressed share btn.
/// @param logViewer ObjectType
///
/// return NO if share action fail.
- (BOOL)onLogViewerWantsToShareContent:(RFKTLogViewer *)logViewer;

/// Called when user pressed filter btn.
/// @param logViewer obj
/// @param sender the btn
- (BOOL)logViewer:(RFKTLogViewer *)logViewer onFilterBtnClick:(UIButton *)sender;

@end


/// Common Log Viewer for RaftKit
///
/// Function:
/// 1. realtime/static display.(done)
/// 2. search and highlight.(done)
/// 3. filter.(done)
/// 4. resize.(done)
/// 5. share.(done)
///
@interface RFKTLogViewer : UIView

/// Init by config
/// @param config obj
- (instancetype)initWithConfig:(RFKTLogViewerConfig *)config;

/// The action delegate
@property (nonatomic, weak) id<RFKTLogViewerDelegate> delegate;
/// Editable or not, default NO
@property (nonatomic, assign, getter=isEditable) BOOL editable;
/// Resizable or not, default YES
@property (nonatomic, assign, getter=isResizable) BOOL resizable;


/// Tip text
/// @param tipText str
- (void)setTipText:(NSString *)tipText;

/// Title
/// @param titleStr str
- (void)setLogViewerTitle:(NSString *)titleStr;

#pragma mark - Log Related

/// Display result log text
/// @param logText filter result
- (void)setLogText:(NSString *)logText;

/// Get full log content
- (NSString *)getFullLogText;


/// Append one log to a new line
/// @param logStr NSString
- (void)addOneLog:(NSString *)logStr;

/// Append one log
/// @param logStr NSString
/// @param addNewLine BOOL
- (void)addOneLog:(NSString *)logStr inserNewLine:(BOOL)addNewLine;


#pragma mark - Log Filter

/// 过滤关键词数组
@property (nonatomic, strong) NSMutableArray *keywordArray;

/// 仅显示过滤日志
@property (nonatomic, assign) BOOL onlyShowFilteredLog;

/// Set keywords
/// @param keywordArray filter keyword
- (void)setKeywords:(nullable NSArray *)keywordArray;

#pragma mark - DataSource Listen

/// Listen to datasource
/// @param source ObjectType
- (void)listenToBroadcastSource:(id<RFKTBroadcastSourceProtocol>)source;

/// Unlisten to datasource
/// @param source ObjectType
- (void)unlistenToBroadcastSource:(id<RFKTBroadcastSourceProtocol>)source;

/// Return current listend datasources
- (NSArray<id<RFKTBroadcastSourceProtocol>> *)allListenedBroadcastSources;

@end



/// Config for RFKTLogViewer
@interface RFKTLogViewerConfig : NSObject

/// 是否可编辑
@property (nonatomic, assign) BOOL editable;
/// 最大记录长度
@property (nonatomic, assign) NSUInteger maxTextRecordLength;

/// 字体
@property (nonatomic, strong) UIFont *textFont;
/// 文字颜色
@property (nonatomic, strong) UIColor *textForgroundColor;
/// 文字背景色
@property (nonatomic, strong) UIColor *textBackgroundColor;
/// 段落格式
@property (nonatomic, strong) NSMutableParagraphStyle *paragraphStyle;

@end


NS_ASSUME_NONNULL_END
