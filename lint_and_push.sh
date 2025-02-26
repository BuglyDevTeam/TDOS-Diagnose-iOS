
checkReturn()
{
    ret=$?
    if ! [ $ret = 0 ];
    then
        echo "ERROR, please check!"
        exit -1
    fi
}


pod lib lint TDOS_Diagnose.podspec --sources='https://mirrors.tencent.com/repository/generic/pod-go/T-CocoaPods/Specs/,https://cdn.cocoapods.org/' --verbose --use-libraries --fail-fast --use-modular-headers --allow-warnings

checkReturn

pod repo push woa-t-cocoapods TDOS_Diagnose.podspec --sources='https://mirrors.tencent.com/repository/generic/pod-go/T-CocoaPods/Specs/,https://cdn.cocoapods.org/' --verbose --use-libraries --use-modular-headers --allow-warnings --skip-tests

checkReturn
