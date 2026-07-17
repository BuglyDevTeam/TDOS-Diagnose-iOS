
# 说明

此处存放TDS_Diagnose Core的二进制静态库及头文件

背景：Core源码迁移至TDS_Diagnose仓库，此TDOS_Diagnose仓库作为“壳”继续对外提供服务

注意：由于CocoaPod机制限制，头文件不可直接放置在TDS_Diagnose.framework中（放置其中会导致其他模块以#import “xxx” 方式导入时找不到TDOS头文件），因此单独将Headers文件夹外置。

