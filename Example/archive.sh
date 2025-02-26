#!/bin/bash
#只需要在终端中输入 $ sh archive.sh  即可打包成ipa

BUILD_SDK_VERSION=$(xcodebuild -showsdks | grep 'iphoneos' | sort -r -g -k 2 | head -n 1 | grep -o '[0-9]\+\.[0-9]\+$')

if [ -z "$BUILD_SDK_VERSION" ]; then
  echo "*** Error: No iphone sdk available !"
  exit -1
fi
echo "build sdk version = $BUILD_SDK_VERSION"

#***********配置项目
#工程名称(Project的名字)
ProjectName="TDiagnose"
#scheme名字 -可以点击Product->Scheme->Manager Schemes...查看
Scheme="TDiagnose-Example"
#Release还是Debug
BUILD_CONFIGURATION=$1
#日期
Date=$(date +%Y%m%d_%H%M)
#build路径
BuildDir="build"
BuildTempDir="$BuildDir/temp"

#工程路径
Workspace="./"
#plist文件名，默认放在工程文件路径的位置
PlistName="ExportOptions.plist"

packaging() {

  #创建构建和输出的路径
  mkdir -p $BuildDir

  #更新pod配置
  pod install

  #构建
  xcodebuild archive \
    -workspace "$ProjectName.xcworkspace" \
    -scheme "$Scheme" \
    -configuration "$BUILD_CONFIGURATION" \
    -archivePath "$BuildDir/$ProjectName" \
    -allowProvisioningUpdates \
    clean \
    build \
    -derivedDataPath "$BuildTempDir" \
    -destination 'generic/platform=iOS'

  #生成ipa
  xcodebuild -exportArchive \
    -archivePath "$BuildDir/$ProjectName.xcarchive" \
    -exportPath "$BuildDir/${ProjectName}_ipa" \
    -exportOptionsPlist "$Workspace/$PlistName"

  #open $BuildDir/Build/Products
}

#函数调用
# $1 工程名  $2 scheme名字  $3 Release还是Debug  $4 工程路径  $5 ipa文件输出路径 $6 plist文件名字
packaging
