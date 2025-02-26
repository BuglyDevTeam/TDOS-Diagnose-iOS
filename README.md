# Bugly Diagnose (`TDOS_Diagnose`)


## 项目简介 (Introduction)

Bugly Diagnose是由腾讯Bugly团队推出的移动端问题诊断服务。
提供多端SDK快速接入能力，目前已覆盖Android、iOS、macOS、Flutter。本项目是iOS、macOS端SDK。

Bugly诊断系统由两部分组成：

`Diagnose`：提供日志捞取、日志染色、条件采集、远程调试等端上问题的调试诊断服务。

`Logger`：提供本地打日志能力，底层基于微信xlog方案。此模块可选接入，业务前期可使用自有打日志模块配合Diagnose使用。

当前系统支持能力：

1. **日志捞取**（支持在线PUSH、批量捞取）
1. **日志染色**（支持批量）
1. **自动上报**

## 示例项目 (Example)

To run the example project, clone the repo, and run `pod install` from the Example directory first.

## 快速上手 (Installation)

### 一、平台注册

在Bugly专业版创建新应用。

成功创建后，平台自动分配`AppId`与`AppKey`, 记录以备后续本地接入使用。

### 二、本地接入

* 第一步：使用Pod安装

`TDOS_Diagnose` is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby


# TDOS_Diagnose组成上包含四个模块：
# 'TDOS_Diagnose/Core'
# 'TDOS_Diagnose/DefaultLogger'（默认的打日志模块实现，底层依赖mars.framework）
# 'TDOS_Diagnose/DefaultStorageImpl'（默认的KV存储实现，依赖MMKV）
# 'TDOS_Diagnose/DefaultFilePacker' (默认的文件压缩实现，依赖SSZipArchive)
# 'TDOS_Diagnose/DefaultFilePacker2' (同上，默认的文件压缩实现2，依赖ZipArchive)
# 其中后三者可以替换为其他实现，默认集成时四个模块将全部包含。

# 添加Pod依赖
pod 'TDOS_Diagnose', '0.8.1'

```

> **环境要求 (Requirements)：**
>
> * iOS: 0.6.3版本及以下: 9.0+, 0.7.0版本及以上: 11.0+
>  
> * macOS: 0.8.0以上支持 10.11+ (Support both Intel and Apple chips)

* 第二步：导入头文件

```objc
#import <TDOS_Diagnose/TDOS_Diagnose.h>
#import <TDOS_Diagnose/TDMMKVFactoryImpl.h>
#import <TDOS_Diagnose/TDOSLogger.h>
#import <TDOS_Diagnose/TDOSLoggerProxy.h>
#import <TDOS_Diagnose/TDLogFilePackerImp.h>

或使用modular headers:
@import TDOS_Diagnose;
```

* 第三步：注入SDK必要依赖项

```objc
    TDIAGDepends *depends = [TDIAGDepends dependsWithLogImp:loggerProxy
                                               kvFactoryImp:[TDMMKVFactoryImpl sharedInstance]
                                           andFilePackerImp:[TDLogFilePackerImp new]];
```

>
> 🟢 请注意，对于日志打印模块的依赖，可选择两种接入方式：
>
>   1. 使用自身项目已有的打日志SDK：
>
> 已有的打日志SDK需实现 `TDLoggingIMPProtocol`协议，并将实例提供给SDK：
>
>  ```objc
>   // 请注意，自定义日志模块需严格依照协议约定实现，尤其是染色与加密相关的配置，否则部分功能可能出现异常。
>   depends.logImpl = 自身的打日志实例;
>  ```
>
>   2. 使用 `TDOS_Diagnose` SDK内置的打日志实现：
>
>  ```objc
>   // 初始化打日志模块
>   TDOSLoggerConfig *loggerConfig = [TDOSLoggerConfig defaultConfig];
>   TDOSLogger *logger = [[TDOSLogger alloc] initWithConfig:loggerConfig];
>   // 更多日志模块配置请参考下文“SDK日志打印模块说明”
>    
>   TDOSLoggerProxy *loggerProxy = [TDOSLoggerProxy defaultProxy];
>   [loggerProxy setLogger:logger];
>   depends.logImpl = loggerProxy;
>  ```
>

* 第四步：生成SDK配置实例并启动SDK

```objc
TDLogSDKConfig *config = [TDLogSDKConfig configWithAppId:@"appid_demo" // 从日志平台申请到的AppID
                                                appKey:@"appkey_demo" // 从日志平台申请到的AppKey
                                            dataSource:self // 实现 *TDLogSDKDataSource* 协议
                                               depends:depends];
[[TDLogSDK sharedInstance] startWithConfig:config];                                       
```


Extension项目接入特别说明：
> 本SDK支持iOS Extension，如使用默认的依赖模块MMKV，需在项目Podfile中添加如下脚本：
>
> ```ruby
> post_install do |installer|
>   installer.pods_project.targets.each do |target|
>     if target.name == "MMKV"
>       target.build_configurations.each do |config|
>         config.build_settings['GCC_PREPROCESSOR_DEFINITIONS'] ||= ['$(inherited)', 'MMKV_IOS_EXTENSION']
>       end
>     end
>   end
> end
> ```
>

### 三、接入Push命令 （可选）

`TDOS_Diagnose`SDK会默认在`启动` / `进前台`等时机以一定时间间隔主动检查有无日志捞取命令。

接入Push后可更及时收到日志捞取命令，减少等待时间。（PS：该能力依赖后台提前对接业务Push系统，TDOS诊断平台不提供Push能力。）

客户端在收到Push命令后，需主动调用`TDOS_Diagnose`SDK的如下接口，实现及时请求捞日志配置：

```objc
/// 主动拉取捞日志命令
///
/// 调用场景：如收到Push消息时
- (void)requestLogConfigFromServer;


// 调用示例：
#import <TDOS_Diagnose/TDOS_Diagnose.h>
[TDLogSDK.sharedInstance requestLogConfigFromServer];
```

### 四、主动上报日志

`TDOS_Diagnose`SDK支持APP主动调用上报接口，上传自定义日志、文件等信息。

该功能可用于用户反馈、异常发生等场景及时上报本地日志信息，帮助保留问题现场。

接口说明：

```objc
/// 主动上报日志
/// @param files 日志文件列表
/// @param tag 标签，必填，最大长度64bytes
/// @param summary 摘要信息（支持搜索）,最大长度256bytes
/// @param extendInfoDict 扩展信息，最大长度1K
/// @param completionBlock 上传结果回调
- (void)uploadFiles:(nonnull NSArray <NSString *> *)files
            withTag:(NSString *)tag
            summary:(nullable NSString *)summary
      andExtendInfo:(nullable NSDictionary *)extendInfoDict
         completion:(void (^)(BOOL result, NSString *_Nullable errMsg))completionBlock;
```

成功上报后，在平台端“自动上报”页面即可查看上报记录和内容。

⚠️注意，请合理指定上报内容或时间范围，避免主动上报日志过大或调用过频繁。

✅更新说明(v0.5.5)：

由于主动上报是程序自动触发，其频率与时机存在不可控性。为了保障上报安全，避免App异常情况下高频上报，导致浪费流量等问题，`TDOS_Diagnose`SDK对主动上报提供了如下4种安全机制：

1. 大小限制机制：限制压缩前的总文件大小（默认500M），超过上限则只保留修改时间较新的部分文件。
2. 频率限制机制：支持设置主动上传的频率，如10分钟内3次（SDK默认不开启）。设置接口参见`TDLogSDKConfig`。
3. 流量限制机制：支持设置每24小时的总上报流量与xg流量（SDK默认不开启），超过额度将禁止上报。设置接口参见`TDLogSDKConfig`。
4. 错误熔断机制：连续上传失败10次后，将停用自动上报6h。（此机制为SDK内部安全兜底机制，暂不支持调整）。

### 五、SDK日志打印模块说明

SDK内置的打日志能力基于微信Mars-xlog方案，对外提供能力在`TDLoggingIMPProtocol`中定义，主要包含如下本地日志打印、日志染色、日志文件获取等功能，使用方法：

```objc
// 头文件
#import <TDOS_Diagnose/TDOSLoggerProxy.h>

// 初始化方式：
@interface TDOSLogger : NSObject <TDLoggingIMPProtocol>

/// 根据配置初始化日志SDK
/// @param config 配置
- (instancetype)initWithConfig:(TDOSLoggerConfig *)config;

@end

// 其中，TDOSLoggerConfig配置包含如下可选设置项：

/// 日志目录
@property (nonatomic, readonly) NSString *logPath;
/// 默认日志级别，默认RAFTLogLevel_Error
@property (nonatomic, readonly) RAFTLogLevel defaultLogLevel;
/// 加密Key
@property (nonatomic, readonly) NSString *publicKey;
/// 控制台是否输出，默认关闭
@property (nonatomic, assign) BOOL enableConsoleLog;
/// 日志文件名前缀（可选设置）
@property (nonatomic, copy) NSString *logFilePrefix;

```

✅更新说明v0.5.7：打日志模块支持多实例，即不同业务日志输出至不同文件。使用方式详见`TDLoggingIMPProtocol`或参考Example工程。

下面具体说明一些能力：

#### 5.1 基础能力

包含打日志、设置日志级别、强制日志落地等。其中日志级别遵循RAFT日志定义——`RAFTLogDef`，提供7个级别。

```c++
RAFTLogLevelVerbose = 0,
RAFTLogLevelDebug = 1,
RAFTLogLevelInfo = 2,
RAFTLogLevelWarn = 3,
RAFTLogLevelError = 4,
RAFTLogLevelFatal = 5,
RAFTLogLevelNone = 6,
```

在此基础上，`TDOS_Diagnose`SDK提供了5个宏定义，以便业务快速接入。这些宏定义在`TDOSLoggerProxy`中，如下所示：

```c++
#define TDLogDebug(tag, format, ...)
#define TDLogInfo(tag, format, ...)
#define TDLogWarn(tag, format, ...)
#define TDLogError(tag, format, ...)
#define TDLogFatal(tag, format, ...)
```

原始具体接口如下所示：

```objc
/// 打日志接口（不带格式化字符串）
- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
        msg:(NSString *)msg;

/// 打日志接口（带格式化字符串）
- (void)log:(RAFTLogLevel)level
        tag:(NSString *)tag
       file:(const char *)file
       func:(const char *)func
       line:(int)line
     format:(NSString *)format, ... __attribute__((format(__NSString__, 6, 7))) NS_REQUIRES_NIL_TERMINATION;

/// 获取当前是否处于染色状态
- (BOOL)isColorState;

/// 重置染色级别
- (void)resetColorLevel;

/// 设置Log打印级别
/// @param level 日志级别
- (void)setLogLevel:(RAFTLogLevel)level;

/// 设置打印log的特殊级别, 以及特殊级别的过期时间
/// @param level 日志级别
/// @param endtime 结束时间
- (void)setLogLevel:(RAFTLogLevel)level endTimestamp:(time_t)endtime;

/// 强制写入日志到文件
/// @param isSync 是否同步写入
- (void)flushLog:(BOOL)isSync;  
```

#### 5.2 更多日志设置能力

包含设置本地日志最大保留时间（默认10天）、设置本地保留的最大日志总量、设置控制台日志输出、设置日志落地时机等。

```objc
/// 设置日志最大存留时间
/// @param time 单位s，默认10（10*24*60*60）天
- (void)setMaxLogAliveTime:(long)time;

/// 设置总的日志文件大小，超出即清理（底层限制最小50M）
/// @param maxSize 总文件大小，默认为0不限制
- (void)setMaxTotalLogFileSize:(int64_t)maxSize;

/// 设置控制台log输出
/// @param enabled 是否开启
- (void)setConsoleLogEnabled:(BOOL)enabled;
```

#### 5.3 日志信息获取

```objc
/// 获取日志列表（按小时打印）
/// @param startTime 开始时间戳
/// @param endTime 结束时间戳
- (nullable NSArray<NSString *> *)getPeroidLogFilesWithStartTime:(NSTimeInterval)startTime
                                                         endTime:(NSTimeInterval)endTime;
                                                         
/// 获取日志列表，支持限定最大日志量
/// （超过大小优先丢弃旧文件）
///
/// @param startTime 开始时间戳
/// @param endTime 结束时间戳
/// @param sizeLimit 最大日志包
- (nullable NSArray<NSString *> *)getPeroidLogFilesWithStartTime:(NSTimeInterval)startTime
                                                         endTime:(NSTimeInterval)endTime
                                                       sizeLimit:(unsigned long long)sizeLimit;

/// 获取日志文件夹路径。
- (NSString *)getLogFolderPath;

/// 获取日志加密公钥
- (nullable NSString *)getLogEncryptPublicKey;
```

## Author

Tencent, bugly@tencent.com

## Thanks & Credits

本项目部分功能基于如下项目建设：

* Mars (<https://github.com/Tencent/mars>)

## License

TDOS_Diagnose is available under the MIT license. See the LICENSE file for more info.
