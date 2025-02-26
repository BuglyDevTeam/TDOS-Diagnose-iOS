/**
 * Tencent is pleased to support the open source community by making rfkt_iOS available.
 * Copyright (C) 2016-2020 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
 */

//
//  NSArray+RFKT.h
//  QMUIKit
//
//  Created by QMUI Team on 2017/11/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSArray<ObjectType> (RFKT)

/**
 *  将多维数组打平成一维数组再遍历所有子元素
 */
- (void)rfkt_enumerateNestedArrayWithBlock:(void (NS_NOESCAPE^)(id obj, BOOL *stop))block;

/**
 *  将多维数组递归转换成 mutable 多维数组
 */
- (NSMutableArray *)rfkt_mutableCopyNestedArray;

/**
 *  过滤数组元素，将 block 返回 YES 的 item 重新组装成一个数组返回
 */
- (NSArray<ObjectType> *)rfkt_filterWithBlock:(BOOL (NS_NOESCAPE^)(ObjectType item))block;

/**
*  转换数组元素，将每个 item 都经过 block 转换成一遍 返回转换后的新数组
*/
- (NSArray *)rfkt_mapWithBlock:(id (NS_NOESCAPE^)(ObjectType item))block;

@end

NS_ASSUME_NONNULL_END
