#!/bin/bash

PROJ_NAME=_Pods.xcodeproj
TARGET_NAME=TDOS_Diagnose-iOS
FRAMEWORK_NAME=lib$TARGET_NAME.a
BUILD_DIR=./Example/build

echo "build dir is: $BUILD_DIR"

BUILD_SDK_VERSION=$(xcodebuild -showsdks | grep 'iphoneos' | sort -r -g -k 2 | head -n 1 | grep -o '[0-9]\+\.[0-9]\+$')

if [ -z "$BUILD_SDK_VERSION" ]; then
    echo "*** Error: No iphone sdk available !"
    exit -1
fi

BUILD_CONFIGURATION=$1
if ! [ "$BUILD_CONFIGURATION"x == "Release"x -o "$BUILD_CONFIGURATION"x == "Debug"x ];
then
    echo "Error, Invalid BUILD_CONFIGURATION, BUILD_CONFIGURATION must be Release or Debug!"
    exit -1
fi

echo "BUILD_SDK_VERSION:$BUILD_SDK_VERSION"
echo "BUILD_CONFIGURATION:$BUILD_CONFIGURATION"

checkReturn()
{
    ret=$?
    if ! [ $ret = 0 ];
    then
        echo "Error, build failed."
        exit -1
    fi
}

bulid()
{
#    xcodebuild -project $PROJ_NAME -target $TARGET_NAME clean
#    checkReturn
    
    xcodebuild -project $PROJ_NAME -target $TARGET_NAME -sdk iphoneos$BUILD_SDK_VERSION -configuration $BUILD_CONFIGURATION build
    checkReturn
    
    xcodebuild -project $PROJ_NAME -target $TARGET_NAME -sdk iphonesimulator$BUILD_SDK_VERSION -configuration $BUILD_CONFIGURATION build
    checkReturn
}

create()
{
    if [ -d './build_result' ]
    then
        rm -rf './build_result'
    fi
    mkdir ./build_result
    
    IPHONE_LIB="$BUILD_DIR/$BUILD_CONFIGURATION-iphoneos/$TARGET_NAME/$FRAMEWORK_NAME"
    SIMULATOR_LIB="$BUILD_DIR/$BUILD_CONFIGURATION-iphonesimulator/$TARGET_NAME/$FRAMEWORK_NAME"
    
    # Currently,since cocoapods(1.9.1) have bug with xcframework
    # see https://github.com/CocoaPods/CocoaPods/issues/10106
    # so we downgrade to traditional fat framework
    lipo -create $SIMULATOR_LIB $IPHONE_LIB -output "./build_result/lib$TARGET_NAME.a"
}

removeCache()
{
    if [ -d $BUILD_DIR ]
    then
        rm -rf $BUILD_DIR
    fi
}

bulid
create
removeCache
