//
//  RAFTMeasureReportDefines.h
//  RAFTMeasure
//
//  Created by RAFTMeasure on 2021/11/16.
//  Copyright © 2021 RAFT. All rights reserved.
//

#ifndef RAFTMeasureReportDefines
#define RAFTMeasureReportDefines

/** 数据上报参数协议 **/
@protocol RAFTMeasureReportParamProtocol <NSObject>

- (NSDictionary *)reportParams;

@end

/** 抽样结果枚举值 **/
typedef NS_ENUM(NSUInteger, RAFTMEASURE_SAMPLING_RESULT) {
    RAFTMEASURE_SAMPLING_RESULT_REPORT = 1,                 // 本次允许上报
    RAFTMEASURE_SAMPLING_RESULT_SLI_APP_LIMIT = 2,          // SLI：本次受限于APP上报次数
    RAFTMEASURE_SAMPLING_RESULT_SLI_RATE_LIMIT = 3,         // SLI：本次受限于默认抽样率上报次数
    RAFTMEASURE_SAMPLING_RESULT_SLI_COM_LIMIT = 4,          // SLI：本次受限于组件上报次数
    RAFTMEASURE_SAMPLING_RESULT_SLI_COMWITHKEY_LIMIT = 5,   // SLI：本次受限于组件+key上报次数
    RAFTMEASURE_SAMPLING_RESULT_SLI_COMRATE_LIMIT = 6,      // SLI：本次受限于组件抽样率
    RAFTMEASURE_SAMPLING_RESULT_STARTUP_RATE_LIMIT = 7,     // StartUp：本次受限于启动抽样率
    RAFTMEASURE_SAMPLING_RESULT_STARTUP_REPEAT_LIMIT = 8    // StartUp：本次受限于启动上报次数
};

/**
    SLI抽样上报规则
        在一个自然日内，一个App共享以下次数限制：
            1、是否超过单App上报次数 {@link #RAFTMEASURE_SAMPLING_SLI_MAXAPPREPORT_COUNT} , 目前是25
            2、是否超过组件上报次数 {@link #RAFTMEASURE_SAMPLING_SLI_MAXCOMREPORT_COUNT} , 目前是10
            3、是否超过组件+Key上报次数 {@link #RAFTMEASURE_SAMPLING_SLI_MAXCOMWITHKEYREPORT_COUNT} , 目前是5
            4、按照业务传入的抽样率采样上报
            5、高于{@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE} 的业务采样率会再进行 {@link RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE} 的二次抽样 ，目前是1%
 
    启动上报抽样规则如下：
        在一次APP存活期间，一个组件只能上报一次:
            采用 {@link #RAFTMEASURE_SAMPLING_STARTUP_DEFAULT_RATE} 的抽样率进行抽样, 目前是1%
 **/
// SLI：单App上报次数
static uint32_t const RAFTMEASURE_SAMPLING_SLI_MAXAPPREPORT_COUNT = 25;
// SLI：组件上报次数
static uint32_t const RAFTMEASURE_SAMPLING_SLI_MAXCOMREPORT_COUNT = 10;
// SLI：组件+key上报次数
static uint32_t const RAFTMEASURE_SAMPLING_SLI_MAXCOMWITHKEYREPORT_COUNT = 5;
// SLI：默认抽样率
static uint32_t const RAFTMEASURE_SAMPLING_SLI_DEFAULT_RATE = 1;
// StartUp：默认抽样率
static uint32_t const RAFTMEASURE_SAMPLING_STARTUP_DEFAULT_RATE = 1;

/** 抽样记录存储Key **/
// 存储空间
static NSString * const RAFTMEASURE_SAMPLING_RECORD_SPACE = @"RAFTMEASURE_SAMPLING_RECORD_SPACE";
// APP上报次数
static NSString * const RAFTMEASURE_SAMPLING_APP_REPORT_COUNT = @"RAFTMEASURE_SAMPLING_APP_REPORT_COUNT";
// 上报日期
static NSString * const RAFTMEASURE_SAMPLING_REPORT_DATE = @"RAFTMEASURE_SAMPLING_REPORT_DATE";

/** 数据上报HTTP配置 **/
// ATTA URL
static NSString * const RAFTMEASURE_ATTA_URL = @"https://h.trace.qq.com/kv";
// POST Method
static NSString * const RAFTMEASURE_HTTP_METHOD_POST = @"POST";
// HTTP请求超时时间，单位秒
static uint32_t const RAFTMEASURE_HTTP_TIMEOUT = 300;
// ATTA Batch Type
static NSString * const RAFTMEASURE_HTTPKEY_BATCH_REPORT = @"batch-report";
static NSString * const RAFTMEASURE_HTTPVAL_ATTA_TYPE = @"Atta-Type";
// Content Type
static NSString * const RAFTMEASURE_HTTPKEY_CONTENT_TYPE = @"Content-Type";
static NSString * const RAFTMEASURE_HTTPVAL_TEXT_PLAIN_CHARSET_UTF_8 = @"text/plain;charset=UTF-8";

/** 数据上报参数 **/
// 组件名
static NSString * const RAFTMEASURE_PARAMKEY_COM_NAME = @"com_name";
// 组件版本号
static NSString * const RAFTMEASURE_PARAMKEY_COM_VER = @"com_ver";
// SLI名称
static NSString * const RAFTMEASURE_PARAMKEY_SLI_NAME = @"sli_name";
// SLI值
static NSString * const RAFTMEASURE_PARAMKEY_SLI_VALUE = @"sli_value";
// SLI类型
static NSString * const RAFTMEASURE_PARAMKEY_SLI_TYPE = @"sli_type";
// APP BundleId
static NSString * const RAFTMEASURE_PARAMKEY_APP_ID = @"app_id";
// APP名称
static NSString * const RAFTMEASURE_PARAMKEY_APP_NAME = @"app_name";
// APP版本
static NSString * const RAFTMEASURE_PARAMKEY_APP_VER = @"app_ver";
// APP编译模式
static NSString * const RAFTMEASURE_PARAMKEY_APP_DEBUG = @"app_debug";
// 抽样率
static NSString * const RAFTMEASURE_PARAMKEY_RATE = @"rate";
// 平台
static NSString * const RAFTMEASURE_PARAMKEY_PLATFORM = @"platform";
static NSString * const RAFTMEASURE_PARAMVAL_PLATFORM = @"iOS";
// ATTA ID
static NSString * const RAFTMEASURE_PARAMKEY_ATTA_ID = @"attaid";
static NSString * const RAFTMEASURE_PARAMVAL_ATTA_APP_ID = @"08500061666";
// ATTA Token
static NSString * const RAFTMEASURE_PARAMKEY_TOKEN = @"token";
static NSString * const RAFTMEASURE_PARAMVAL_ATTA_TOKEN = @"3978713261";
// ATTA TYPE
static NSString * const RAFTMEASURE_PARAMKEY_TYPE = @"type";
static NSString * const RAFTMEASURE_PARAMVAL_BATCH = @"batch";
// ATTA VERSION
static NSString * const RAFTMEASURE_PARAMKEY_VERSION = @"version";
static NSString * const RAFTMEASURE_PARAMVAL_VERSION_DEFAULT = @"v1.0.0";
// SDK VERSION
static NSString * const RAFTMEASURE_PARAMKEY_SDK_VER = @"sdk_ver";

/** Bugly Crash SP Name **/
static NSString * const RAFTMEASURE_CRASH_MONITOR_SP_NAME = @"BuglySDKInfos";

#endif
