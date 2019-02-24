Pod::Spec.new do |s|
  s.name                    = 'Appcues'
  s.version                 = '0.6.0'
  s.summary                 = 'The Appcues iOS SDK enables you to build, publish and test onboarding flows without submitting to the App Store'
  s.swift_version           = '4.2'
  s.platform                = :ios, '9.0'
  s.license                 = { :type => 'proprietary', :file => 'LICENSE' }
  s.homepage                = 'https://www.appcues.com/mobile/ios'
  s.authors                 = { 'YasminL' => 'yasmin.lindholm@hotmail.com', 
                                'nkhoshaf' => 'naregkhoshafian@gmail.com', 
                                'dodongo' => 'dgaxho@gmail.com' }
  s.requires_arc            = true
  s.source                  = { git: 'https://github.com/appcues/ios-sdk-releases.git', tag: s.version }
  s.ios.vendored_frameworks = 'Appcues.framework'
end
