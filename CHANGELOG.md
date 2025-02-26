# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).


## [0.8.5]() - 2025-02-25

### Features

- 移除对于RaftInterface、Raftmeature的依赖


## [0.8.4]() - 2024-11-13

### Features

- 支持设置 App Version

## [0.8.3]() - 2024-07-30

### Features

- 支持 BuglyPro 海外版域名接入

## [0.8.2.1]() - 2024-06-06

### Fixs

- BuglyPro 域名未完全配置问题

## ~~[0.8.2]() - 2024-06-06~~

### Features

- 支持 BuglyPro 域名接入


## [0.8.1]() - 2024-06-05


### Bug Fixes
- log zip file management fix ([1041f921](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/1041f921d9d0595190681115ef63316f66fe5888) by xiaocui).


## [0.8.0.1]() - 2024-06-05


### Bug Fixes
- log zip file management fix ([1041f921](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/1041f921d9d0595190681115ef63316f66fe5888) by xiaocui).

## [0.8.0]() - 2023-04-03

<small>[Compare with 0.7.2]()</small>

### Features
- Macos support - file path adapt ([cc747f6](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/cc747f69f5dac4cc4d94ab8cd9a5fd87ece80add) by raycgwang).
- Macos support - logger适配 ([f1da352](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/f1da35205adb14b34a0e935ac9000f4356ed2114) by raycgwang).
- Update mmkv folder, file path and etc for macos support ([1bec473](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/1bec473354c568baa70a4f2788efb36adc428ec2) by raycgwang).


## [0.7.2]() - 2023-03-20

<small>[Compare with 0.7.0]()</small>

### Bug Fixes
- Upload fail due to invalid filename ([7d73668](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7d73668df7096eb78ae53eff8802cb06717f1cec) by raycgwang).

### Features
- Add query key parameter for auto_upload ([32fed0e](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/32fed0e4e39b3f24ba728c0b2ebda2e9aa42c386) by raycgwang).
- Support macos (core) ([9f79e23](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/9f79e23dd8f1b7579c1980aff24877cb9d66e2a5) by raycgwang).


## [0.7.0]() - 2022-12-05

<small>[Compare with 0.6.4]()</small>

### Features
- Bump minimum deployment target version to 11.0 ([1e62f3b](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/1e62f3bcc98eb80c455cf33c0bacdad4897c5b0b) by raycgwang).


## [0.6.4]() - 2022-12-05

<small>[Compare with 0.6.0]()</small>

### Bug Fixes
- Bypass qb's url protocol check ([c03c4a1](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/c03c4a19c05c5c92ae8f409c026e5f137c20127a) by raycgwang).
- Update source url to git.woa.com ([31fd29a](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/31fd29ab27b40ff475c1e768f884e36c6026b621) by raycgwang).


## [0.6.0]() - 2022-10-18

<small>[Compare with 0.5.9]()</small>

### Bug Fixes
- Files in shared container not get compressed ([7929194](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7929194d84dbe949769926185ebc5b5cc096cacd) by raycgwang).

### Features
- Support auto move and clean mmap files ([3120ee3](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/3120ee3fce75fbb4b1d413a0b1cc7709e464aa2e) by raycgwang).
- 更新海外版域名 ([16f0a18](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/16f0a1870f36d234f7ab67598eb55f3b8f80c26e) by raycgwang).
- 支持设置自定义域名 ([7f246a1](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7f246a19b5120dc7eaab79f565129ddcef64e2da) by raycgwang).
- Add log index for each lifecycle ([dac94cf](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/dac94cfc2ed28725c97c54dca0a4ae26c08430d5) by raycgwang).
- Align timestamp by the hour when retrieving log files ([7d4868b](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7d4868bd591745a8f821cf791067cfe71f78ad4f) by raycgwang).


## [0.5.9]() - 2022-07-04

<small>[Compare with 0.5.8]()</small>


## [0.5.8]() - 2022-06-30

<small>[Compare with 0.5.7]()</small>

### Features
- Support custom threshold for multi-part upload ([462d604](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/462d604cec7a93b51d27c5cda2cf25ba2acbc183) by raycgwang).
- Support both ziparchive and ssziparchive ([4ef2c2b](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/4ef2c2bc258a3c8bafecab88e0c6474e87f156b0) by raycgwang).


## [0.5.7]() - 2022-06-02

<small>[Compare with 0.5.6]()</small>

### Features
- 打日志模块支持多实例 ([de9f69d](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/de9f69d4c6243bc0371466245d38bc50217ee81c) by raycgwang).


## [0.5.6]() - 2022-05-25

<small>[Compare with 0.5.5]()</small>

### Bug Fixes
- 修复普通上传crc64异常问题 ([25f9082](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/25f90822e6c366dfae691b6f4aa395f8f3b681a1) by raycgwang).

### Features
- 打日志接口调整，区分是否带格式化参数 ([ef31659](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ef31659f2e4285a20061a360aaf1448d3c7999f7) by raycgwang).


## [0.5.5]() - 2022-05-18

<small>[Compare with 0.5.4]()</small>

### Bug Fixes
- 修复打日志格式化异常问题 ([c978235](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/c9782359f99c78390eb6a1c1cf4ec40fe10a9d16) by raycgwang).
- 文件不存在场景可能上传空文件的问题 ([4bcaa3f](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/4bcaa3f6a391572a17b2c49fb279c6c08d0f6c73) by raycgwang).
- 模拟器环境下日志不存在时可能会误删文件问题 ([d9a86ce](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/d9a86ce738cda87b5f4321b7f5b19408d8781d8f) by raycgwang).

### Features
- 获取日志支持设置大小上限 ([cae28bc](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/cae28bc1ee4000b80a94c18f47c53b7044bc9b04) by raycgwang).
- 自动上报异常保护支持自定义设置 ([2494d02](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/2494d027baa2c1a5e739819e75cb0a95a20f1da7) by raycgwang).
- 优化重试任务处理策略 ([306ba1a](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/306ba1aece9df0c000222bac75c396327a202713) by raycgwang).
- 增加自动上报异常保护模块 ([b1ceeb3](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/b1ceeb35add9318e33295cdf5c4f1e3159796088) by raycgwang).
- 调整文件大小限制策略 ([9eb235c](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/9eb235cfef33e61bc1ea698be15983734ee6d677) by raycgwang).


## [0.5.4]() - 2022-04-21

<small>[Compare with 0.5.3]()</small>

### Bug Fixes
- Eliminate a warning in tdlogger ([255064e](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/255064ec4d08b3b173e35ff366572918a63be87f) by raycgwang).


## [0.5.3]() - 2022-04-18

<small>[Compare with 0.5.2]()</small>

### Features
- 解耦对ssziparchive的依赖，提供依赖注入 ([ef6cc3d](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ef6cc3dddd7a3d26bda3160dfb2284d2c821daf4) by raycgwang).
- 协议更新，支持长期染色 (merge request !2) ([5381998](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/538199829ac69d07547e339dcf4c631aead5d311) by raycgwang).


## [0.5.2]() - 2022-04-02

<small>[Compare with 0.5.1]()</small>

### Bug Fixes
- 处理代码格式问题，demo更新 ([7ae65bf](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7ae65bf96433e868e1b322f4f468a7a888d10b91) by raycgwang).

### Features
- 删除内置ziparchive，调整为pod依赖 ([893a388](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/893a388fdaa836d4884597b2a40e42631c845e23) by raycgwang).


## [0.5.1]() - 2022-03-29

<small>[Compare with 0.5.0]()</small>

### Bug Fixes
- 新增文件上传回包crc64有效性检查 ([ad05515](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ad05515745420177e458d9c0891c282d19f20193) by raycgwang).

### Features
- 删除内置yymodel，调整为pod依赖 ([86c2b90](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/86c2b90617ea274bc6aa2270b02d0d13445c1d49) by raycgwang).


## [0.5.0]() - 2022-03-24

<small>[Compare with 0.4.0]()</small>

### Bug Fixes
- Cos分片上传异常 ([b298dcd](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/b298dcddc1f2b3c92f747aa1c31a74eeeb6d78a7) by raycgwang).

### Code Refactoring
- 隐私合规修改 ([2481ebe](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/2481ebe731566f26186930f0405ae736123c6573) by raycgwang).


## [0.4.0]() - 2022-03-22

<small>[Compare with 0.3.2]()</small>

### Features
- Change name to tdos_diagnose ([ca1abc7](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ca1abc72bf259f7400426d2f6062c7e9e61799a8) by raycgwang).


## [0.3.2]() - 2022-03-22

<small>[Compare with 0.3.1]()</small>


## [0.3.1]() - 2022-03-21

<small>[Compare with 0.3.0]()</small>

### Features
- 更新依赖项raftinterface，更新版本号 ([a268f21](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/a268f213ac61b4425728e0b7d32c3ea99c5d7b23) by raycgwang).


## [0.3.0]() - 2022-03-10

<small>[Compare with 0.2.3]()</small>

### Bug Fixes
- 修复失败任务清理问题 ([a0be29e](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/a0be29e8b0f0054700065817087187ef1745ca21) by raycgwang).
- 修复打日志入参异常可能导致的xlog crash，添加编译属性 ([3c23a3b](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/3c23a3b9301dbdc37f1c07896eaad5eef95f9782) by raycgwang).
- 修复本地时间不准确可能导致的上传异常 ([ca45c73](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ca45c73256b5ed1339ae1f0ddde49b19eb175650) by raycgwang).

### Features
- 自动上报增加摘要字段 ([ee703da](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ee703dae38b299fdf275038afab7389c5d0679f3) by raycgwang).


## [0.2.3]() - 2022-02-28

<small>[Compare with 0.2.2]()</small>

### Features
- 增加日志总量大小限制能力 ([fa9b1c7](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/fa9b1c748f062098830e1c9668ae392687b5edef) by raycgwang).


## [0.2.2]() - 2022-02-23

<small>[Compare with 0.2.0]()</small>

### Features
- Podpsec新增对raftmeasure的依赖 ([d6e4bee](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/d6e4bee15f0ae55c857312a22cb20777faf57b94) by raycgwang).
- 支持设置本地日志文件名前缀 ([490179c](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/490179cb90853d2a2b5da9170179dc3bfec72924) by raycgwang).
- 接入bugly 共享式上报 ([0318e07](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/0318e07e8c6f38e58a2a96e02a684eabe1571186) by raycgwang).


## [0.2.0]() - 2022-02-14

<small>[Compare with 0.1.0]()</small>

### Code Refactoring
- 优化cos任务重试逻辑，标准化代码 ([208881d](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/208881d1c31fee95e9b27afea343d080b4cb8f5d) by raycgwang).
- 修复yymodel符号重复问题 ([5945d88](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/5945d88235e16590967ae43629b73aa1e6b160be) by raycgwang).
- 修复符号重复问题 ([e116e73](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/e116e7398cda1ac0dc1f1b7a58d1112b7b3544c0) by raycgwang).
- 规范化代码，修复潜在符号重复问题 ([7dc7545](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7dc754546ad9d16c336ee0b6c8ae856cbc3a8089) by raycgwang).

### Features
- 优化和完善数据上报 ([ad43b05](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ad43b054429bf919f4fe71bd78c6dd5a0d31dafc) by raycgwang).
- Sub podspec 拆分，目录移动 ([94ce140](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/94ce14062e98fa0b76aee52ea014f1ec49e5d4cb) by raycgwang).
- 主动上报接口增加回调，规避部分符号重复问题 ([7ccc62e](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/7ccc62e256a7791e9f74e21f7453add8c64e9bec) by raycgwang).
- 增加对捞目录的支持 ([9063f62](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/9063f623c202c5d9da0f5acacfaf791d723d522e) by raycgwang).
- 自动上报支持自定义tag ([6baffcc](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/6baffcca3ae37d466abe24589e28bbe670210197) by raycgwang).
- 调整压缩包命名规则 ([eed1771](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/eed1771015dfdcaf965bb9b29ece2e11a4f4a611) by raycgwang).
- 更新协议，增加获取特定文件的能力 ([700ea86](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/700ea86eaeac34be6fe3ecff61253f65e2368e41) by raycgwang).
- 切换至正式环境 ([e92b8c5](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/e92b8c52b0db8a14eb8518e2beac2339dd08781e) by raycgwang).
- 完善功能，替换压缩组件 ([a97d75d](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/a97d75d92c0f20b62ed18fd2209bf15e5fa541e4) by raycgwang).
- 完善重试流程，增加数据上报 ([d68b37b](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/d68b37b339c96034d03a0be3404196e9f5984677) by raycgwang).
- 完善功能，增加业务自定义附件接口 ([3526c00](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/3526c000c6d94552abfeb5507c5df1fb8d61ef90) by raycgwang).


## [0.1.0]() - 2022-01-15

<small>[Compare with first commit]()</small>

### Features
- 完善功能，删除beacon依赖 ([cf9f4bc](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/cf9f4bca53918001747d47eb92f3fdb5962c1e45) by raycgwang).
- 完善功能，cos url调整为后台返回 ([2bdeb66](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/2bdeb664481db1f645447d439b34e8b44b495a2f) by raycgwang).
- 完善功能，更新readme ([37f7aab](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/37f7aab254b2c5a511575d2916315e3026f8a0ea) by raycgwang).
- First init project ([ed40067](https://git.woa.com/TDOS_Diagnose/TDS_Diagnose_iOS/commit/ed40067177acf7bc51be481522ea639033bea856) by raycgwang).


