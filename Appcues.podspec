Pod::Spec.new do |s|
  s.name = "Appcues"
  s.version = "0.12.1"
  s.summary = "The Appcues iOS SDK enables you to build, publish and test onboarding flows without submitting to the App Store"
  s.platform = :ios, "10.0"
  s.license = { :type => "proprietary", :file => "LICENSE" }
  s.homepage = "https://www.appcues.com/mobile/ios"
  s.authors = { "YasminL" => "yasmin.lindholm@hotmail.com",
                "dodongo" => "dgaxho@gmail.com" }
  s.source = { :git => "https://github.com/appcues/ios-sdk-releases.git", :tag => "#{s.version}" }
  s.module_name = "Appcues"
  s.cocoapods_version = ">= 1.7.2"
  s.vendored_frameworks = "Appcues.framework"
end
