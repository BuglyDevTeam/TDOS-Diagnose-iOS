# source 'https://mirrors.tencent.com/repository/generic/pod-go/T-CocoaPods/Specs/'

Pod::Spec.new do |spec|
  spec.name             = 'TDOS_Diagnose'
  spec.version          = '0.8.5'
  spec.summary          = '腾讯Bugly-日志诊断SDK'
  spec.description      = <<-DESC
                        一款由腾讯Bugly团队推出的日志诊断SDK.
                        提供日志打印、日志上传、问题诊断等App基础能力
                            DESC
                       
  spec.homepage         = 'hhttps://github.com/BuglyDevTeam/TDOS-Diagnose-iOS'
  spec.license          = { :type => 'MIT', :file => 'LICENSE' }
  spec.author           = { "Tencent" => "bugly@tencent.com" }
  spec.source           = { :git => 'https://git.woa.com/TDOS_Diagnose/TDOS-Diagnose-iOS.git', :tag => spec.version.to_s }
  spec.ios.deployment_target = '11.0'
  spec.osx.deployment_target = '10.11'
  
  # ――― Sub Specs ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  spec.default_subspec = 'AIO'
  
  #诊断核心模块
  spec.subspec 'Core' do |ss|
    ss.dependency 'YYModel'
    ss.frameworks = 'SystemConfiguration'
    ss.public_header_files = ['TDOS_Diagnose/Core/Headers/*.{h,hpp}']
    ss.source_files = 'TDOS_Diagnose/Core/Headers/*.{h,m,hpp,mm,cpp}'
    ss.vendored_frameworks = 'TDOS_Diagnose/Core/TDS_Diagnose.xcframework'
  end
  
  #默认的打日志实现，基于xlog(腾讯视频修改版)
  spec.subspec 'DefaultLogger' do |ss|
      ss.source_files = 'TDOS_Diagnose/DefaultInjectIMP/Logger/*{.h,.c,.hpp,.cpp,.m,.mm}'
      ss.public_header_files = 'TDOS_Diagnose/DefaultInjectIMP/Logger/*{.h}'
      ss.dependency 'TDOS_Diagnose/Core'
      ss.ios.vendored_frameworks = 'TDOS_Diagnose/DefaultInjectIMP/Logger/ios/mars.xcframework'
      ss.osx.vendored_frameworks = 'TDOS_Diagnose/DefaultInjectIMP/Logger/osx/mars.framework'
  end
  
  #默认的KV组件实现，依赖MMKV
  spec.subspec 'DefaultStorageImpl' do |ss|
      ss.source_files = 'TDOS_Diagnose/DefaultInjectIMP/Storage/**/*{.h,.c,.hpp,.cpp,.m,.mm}'
      ss.public_header_files = 'TDOS_Diagnose/DefaultInjectIMP/Storage/**/*{.h}'
      ss.dependency 'MMKV'
      ss.dependency 'TDOS_Diagnose/Core'
  end
  
  #默认的文件压缩实现，依赖SSZipArchive
  spec.subspec 'DefaultFilePacker' do |ss|
      ss.source_files = 'TDOS_Diagnose/DefaultInjectIMP/FilePacker/**/*{.h,.c,.hpp,.cpp,.m,.mm}'
      ss.public_header_files = 'TDOS_Diagnose/DefaultInjectIMP/FilePacker/**/*{.h}'
      ss.dependency 'TDOS_Diagnose/Core'
      ss.dependency 'SSZipArchive'
  end
  
  #默认的文件压缩实现2，依赖ZipArchive
  spec.subspec 'DefaultFilePacker2' do |ss|
      ss.source_files = 'TDOS_Diagnose/DefaultInjectIMP/FilePacker/**/*{.h,.c,.hpp,.cpp,.m,.mm}'
      ss.public_header_files = 'TDOS_Diagnose/DefaultInjectIMP/FilePacker/**/*{.h}'
      ss.dependency 'TDOS_Diagnose/Core'
      ss.dependency 'ZipArchive'
  end
  
  spec.subspec 'AIO' do |ss|
      ss.dependency 'TDOS_Diagnose/Core'
      ss.dependency 'TDOS_Diagnose/DefaultLogger'
      ss.dependency 'TDOS_Diagnose/DefaultStorageImpl'
      ss.dependency 'TDOS_Diagnose/DefaultFilePacker'
  end
  
  # ――― Project Linking ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  spec.libraries = "z", "c++"

  # ――― Project Settings ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  spec.requires_arc = true
  spec.pod_target_xcconfig = {
    'GCC_PREPROCESSOR_DEFINITIONS' => 'TDIAG_VERSION=' + spec.version.to_s,
  }

  # ――― Test Settings ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
 spec.test_spec 'UnitTests' do |test_spec|
     test_spec.requires_app_host = true #兼容M1 x86_64 UnitTest
     test_spec.source_files = 'Tests/*.{h,m}'
     test_spec.dependency 'OCMock'
     test_spec.dependency 'YYModel'
 end
  
end
