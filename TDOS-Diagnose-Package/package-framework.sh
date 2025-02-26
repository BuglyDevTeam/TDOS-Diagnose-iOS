#!/bin/bash

cd TDOS-Diagnose

not_embed_deps=0
if [ "$1" == 'not_embed' ]; then
export NOT_EMBED_DEPS=true
not_embed_deps=1
fi 

pod install

if [ "$not_embed_deps" -eq "1" ]; then
    # 不需要 embed 依赖时，只编译 Pods 生成的 target 即可
    xcodebuild -workspace TDOS-Diagnose.xcworkspace -scheme 'TDOS_Diagnose' -configuration Release \
    -derivedDataPath ../build \
    CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO \
    CODE_SIGN_ENTITLEMENTS="" CODE_SIGNING_ALLOWED="NO"
else
    # 编译壳工程
    xcodebuild -workspace TDOS-Diagnose.xcworkspace -scheme 'TDOS-Diagnose' -configuration Release \
    -derivedDataPath ../build \
    CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO \
    CODE_SIGN_ENTITLEMENTS="" CODE_SIGNING_ALLOWED="NO"
fi


cd ..

rm -rf products
mkdir products

if [ "$not_embed_deps" -eq "1" ]; then
    mv -f build/Build/Products/Release/TDOS_Diagnose/TDOS_Diagnose.framework products
else
    mv -f build/Build/Products/Release/TDOS_Diagnose.framework products
fi
# 直接创建的工程没有包含头文件，此处将头文件复制出来
cp -rf ../TDOS_Diagnose/Core/Headers/* products/TDOS_Diagnose.framework/Headers
cp -rf ../TDOS_Diagnose/DefaultInjectIMP/FilePacker/*.h products/TDOS_Diagnose.framework/Headers
cp -rf ../TDOS_Diagnose/DefaultInjectIMP/Logger/*.h products/TDOS_Diagnose.framework/Headers
cp -rf ../TDOS_Diagnose/DefaultInjectIMP/Storage/*.h products/TDOS_Diagnose.framework/Headers
if [ "$not_embed_deps" -eq "0" ]; then
    cp TDOS-Diagnose/Pods/RaftInterface/Log/RAFTLogDef.h products/TDOS_Diagnose.framework/Headers
    cp TDOS-Diagnose/Pods/RaftInterface/KVStorage/RAFTKVStorageFactoryProtocol.h products/TDOS_Diagnose.framework/Headers
    cp TDOS-Diagnose/Pods/RaftInterface/KVStorage/RAFTKVStorageProtocol.h products/TDOS_Diagnose.framework/Headers
    # dSYM 文件同步提供
    mv -f build/Build/Products/Release/TDOS_Diagnose.framework.dSYM products
fi 

# 清理环境
# rm -rf build
