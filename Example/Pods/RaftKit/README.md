## 项目介绍

**RaftKit** 是一款有PCG特色的，旨在提升App开发调试效率的“一站式”研发工具，由**PCG端服务中台**下设的**调试效率工作组**推出。

**RaftKit** 内置了数十款调试效率工具，从常用的 **应用信息查看**、**沙盒操作** 、**http抓包**，到自动定位性能问题的**卡顿监控** 、**内存泄漏监控**、 **线程监控** 、**函数耗时监控**等，以及UI相关的**取色计** 、**控件信息查看**、**图片路径展示**等一应俱全。

**RaftKit**包含如下几大特点：

* 一站式：汇集丰富的iOS端调试工具，解决开发调试各种问题。
* 可扩展：不仅支持sdk端插件扩展，更能支持桌面端等的远程扩展。
* 协同化：发挥现有组件优势，建设有PCG特色的开发调试工具。

对标业界调试工具，RaftKit的差异化在哪里？

* 更优秀的工具能力：站在巨人肩膀上，充分发挥PCG现有优秀工具实力，如RMonitor、RFix等，同时结合业界开源的优秀工具，打造出一款更强大的工具集。

* 更好的体验：在使用中不断优化交互，提供更优秀的接入使用体验。

* 更方便的多端扩展：未来不仅支持应用内，在桌面端、Web端都可直接使用。

  

##### 平台端体验地址（Beta版）：https://raftkit.woa.com #####



## 功能概览

工具主面板预览：

<img src="./resource-README/mainPage.png" alt="mainPage" style="zoom:50%;" /><img src="./resource-README/远程连接.png" alt="远程连接" style="zoom:50%;" />

**RaftKit主要包含以下几类工具：**

| 常用工具          | 性能工具              | UI工具                | 平台工具 |
| ----------------- | --------------------- | --------------------- | --------------------- |
| App信息查看       | FPS查看               | 取色计                |*【new】*RFix补丁调试 |
| Info.plist查看    | CPU查看               | UI控件检查            |* [todo]Hippy调试 * |
| UserDefaults      | 内存查看              | 控件相对距离          | |
| 沙盒浏览          | 网络查看              | 实时录屏 ||
| 定位模拟          | IO查看                |*【new】*动画变速           | |
| Http抓包          | 卡顿监控              |*【new】*图片路径          | |
| NSLog查看       | 内存泄漏监控          |                       | |
| 显示当前VC名      | Load耗时监控          |                       | |
| 弱网模拟          | 子线程UI监控          |                       | |
| 日志过滤          | Crash记录             |                       | |
| DB查看            | *【new】*线程创建监控 |                       | |
|*【new】*push模拟  |                       |                       | |
|*【new】*TraceLog  |                       |                       | |
|*【new】*调用追踪  |                       |                       | |

**关于各功能的详细介绍及动图演示，您可以查看：[RaftKit-iOS功能介绍](https://iwiki.woa.com/pages/viewpage.action?pageId=807028307)**

## 快速开始

### CocoaPods接入

您可以选择源码引入或二进制方式引入：

* 【推荐】方式一：源码引入

  打开 **Podfile**，添加以下**podspec**到您的 app target 里面；

  ```ruby
  source 'https://mirrors.tencent.com/repository/generic/pod-go/T-CocoaPods/Specs/'
  
  # 将以下 ['Debug'] 中，增加您的工程的CI版本配置，以便在CI版本生效，如修改成['Debug', 'xxx'](xxx为工程CI配置名称)，注意不要增加'Release'，避免影响发布版本
  # 支持modular headers，可添加“:modular_headers => true” 以使用 @import RaftKit;
  pod 'RaftKit', '~> 1.4', :configurations => ['Debug', 'DailyBuild']
  # current lastest version: 1.5.3

  # RaftKit支持模块按需集成
  # 未指定subpod时，默认加载全部模块
  # 可指定subpod，选择要集成的插件工具：
  pod 'RaftKit/BasicPlugins', '~> 1.4', :configurations => ['Debug', 'DailyBuild']
  pod 'RaftKit/BuglyBasedPlugins', '~> 1.4', :configurations => ['Debug', 'DailyBuild']
  pod 'RaftKit/LoadMeasurePlugin', '~> 1.4', :configurations => ['Debug', 'DailyBuild']

  # 请注意：以下是RaftKit的依赖库，如果集成了对应RaftKit子模块，则需像这样显式指定configurations，否则会在Release版本编译，下同
  pod 'Bugly', '~> 2.7.3', :configurations => ['Debug', 'DailyBuild'] # RaftKit/BuglyBasedPlugins模块的依赖库
  pod 'FBRetainCycleDetector', '~> 5.0.5', :configurations => ['Debug', 'DailyBuild'] # RaftKit/RMonitorBasedPlugins模块的依赖库
  pod 'A4LoadMeasure', '~> 0.1.3', :configurations => ['Debug', 'DailyBuild'] # RaftKit/LoadMeasurePlugin模块的依赖库
  ```

* 方式二：静态库引入

> xcframework格式，支持Mac Catalyst
>
> 请注意，静态库需依赖RMonitor、FBRetainCycleDetector、A4LoadMeasure三个第三方库
>
> 静态库仓库地址：https://git.woa.com/RaftKit/RaftKit_iOS_XCBinary 

  打开 **Podfile**，添加以下**podspec**到您的 app target 里面；

  ```ruby
  source 'https://mirrors.tencent.com/repository/generic/pod-go/T-CocoaPods/Specs/'
  
  #将以下 ['Debug'] 中，增加您的工程的CI版本配置，以便在CI版本生效，如修改成['Debug', 'xxx'](xxx为工程CI配置名称)，注意不要增加'Release'，避免影响发布版本
  pod 'RaftKit-xcbin', '~> 1.4', :configurations => ['Debug']
  ```

### SDK初始化

 推荐在`application:didFinishLaunchingWithOptions:`delegate中进行初始化：
 （使用了UIWindowScene的App，在`sceneDidBecomeActive:`delegate中进行初始化）

  ```objectivec
    #if DEBUG   //添加您的工程CI版本控制的宏，以便在CI版本使用RaftKit，如 #if DEBUG || CI_BUILD
    #import <RaftKit/RaftKit.h>
    #endif
    
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        ...
        #if DEBUG   //添加您的工程CI版本控制的宏，以便在CI版本使用RaftKit，如 #if DEBUG || CI_BUILD
        // 显示工具的悬浮球入口（悬浮球可以在RaftKit面板->设置中隐藏）
        [RFKTManager install];
        // 注意：为避免用户手动关闭悬浮球后无法再次打开，可在适当固定入口调用-[RFKTManager showFloatingBall]接口来重新显示。
        // 或使用下述手势触发方式来显示悬浮球。
    
        //【可选】设置工具的其他触发方式，包括摇一摇，双指双击，双指长按。
        // 你也可以通过RFKTTapTrigger、RFKTLongPressTrigger的初始化方法设置点击次数、长按时间。
        [RFKTManager.sharedInstance setupWithTriggers: @[[RFKTShakeTrigger trigger], [RFKTTapTrigger trigger], [RFKTLongPressTrigger trigger]]];
        
        #endif
        ...
    }
  ```

然后在App启动后便会显示RaftKit的悬浮球，点击悬浮球进入主面板即可使用RaftKit丰富的功能。

您也可以在自己工程其他地方自定义启动方式，调用`[RFKTManager.sharedInstance showFloatingBall]`即可。

### 自定义插件

您可以自定义自己的调试插件，方便地集成到RaftKit中：

1. 创建一个类，实现RFKTPlugin协议；

    ```objectivec
    #import <RFKTPlugin.h>
    @interface RaftKitCustomPlugin : NSObject <RFKTPlugin>
    
    @end
    ```

2. 在SDK初始化的代码后加入自定义插件。

    ```objectivec
    [RFKTManager.sharedInstance showFloatingBall];
    [RFKTManager.sharedInstance addPlugin:[RaftKitCustomPlugin new]];
    ```

具体代码可参考RaftKitDemo工程中的 `RaftKitDemoPlugin1.m`。

## Thanks & Credits

`RaftKit`是在巨人肩膀上建设，许多灵感或能力来自于公司内外的开源项目。如下项目等为RaftKit的建设提供了非常大的帮助：

* Bugly(原RMonitor_iOS)：PCG组件平台中心提供的性能监控框架。
* QMUI_iOS：Provides some useful UI components.
* FLEX：An in-app debugging and exploration tool for iOS.
* DBDebugToolKit：Set of easy to use debugging tools for iOS developers & QA engineers.
* FBRetainCycleDetector：iOS library to help detecting retain cycles in runtime.
* HookLoadMethods：A tool used to measure load method execution time.
* fishhook：A library that enables dynamically rebinding symbols in Mach-O binaries running on iOS.
* SocketRocket：A conforming Objective-C WebSocket client library.
* JSON_Model：Data Modeling Framework for JSON.
* Tabler Icons：Fully customizable free SVG icons.

## 开发流程规范

我们十分期待您的任何贡献，无论是修复错别字、提 Bug 还是提交一个新的提案。如果您是第一次贡献代码，请阅读 [开发流程](https://iwiki.woa.com/pages/viewpage.action?pageId=644714783) ，并提交  `Merge Request` 给我们。
