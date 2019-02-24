# Appcues iOS SDK Releases

This repository contains binary distributions of iOS products released by [Appcues](https://www.appcues.com/mobile/ios).

If you have any questions, comments, or issues related to any products distributed via this repository then please contact the team by emailing [support@appcues.com](mailto:support@appcues.com).

## Appcues iOS SDK

The Appcues iOS SDK allows iOS app developers to build, publish, and test onboarding flows, without submitting to the app store.

In order to use Appcues you must register an account on https://beta.my.appcues.com/mobile, and install the SDK into an iOS app. You can then use the SDK in conjunction with the mobile web editor to set up flows that will be targeted to live users of your app.

### Installation

Appcues can be installed directly into your application by importing a framework or via CocoaPods. Quick installation instructions are provided below for reference, but please refer to the [Appcues iOS Documentation](https://docs.appcues.com/collection/390-mobile-appl) for full details and troubleshooting.

#### CocoaPods Installation

The recommended path for installation is [CocoaPods](http://cocoapods.org/). CocoaPods provides a simple, versioned dependency management system that automates the tedious and error prone aspects of manually configuring libraries and frameworks. You can add Appcues to your project via CocoaPods by doing the following:

```sh
$ sudo gem install cocoapods
$ pod setup
```

Now create a `Podfile` in the root of your project directory and add the following:

```ruby
pod 'Appcues'
```

Complete the installation by executing:

```sh
$ pod install
```

These instructions will setup your local CocoaPods environment and import Appcues into your project. Once this has completed, test your installation by referring to the [Verifying Appcues Configuration](#verifying-appcues-configuration) section below.

#### Framework Installation

If you wish to install Appcues directly into your application via the binary framework, then you can download the Appcues.framework, a dynamic framework that is compatible with Objective-C and Swift projects that target **iOS 9** and higher.

Download .framework artifact from this repository and add it to your application:

1. Drag and drop the framework onto your project, instructing Xcode to copy items into your destination group's folder.
2. The dynamic framework distribution requires the configuration of additional build phases to complete installation. The steps are detailed on the [Appcues Knowledge Base](https://docs.appcues.com/article/424-mobile-installation-manually).

Build and run your project to verify installation was successful. Once you have completed a successful build, refer to the section below for details on how to test your setup.

### Verifying Appcues Configuration

Once you have finished installing Appcues via CocoaPods or framework, you can test your installation by following the instructions on the [Appcues iOS Documentation](https://docs.appcues.com/article/398-mobile-initialization).

## Contact

You can reach the Appcues team at any time by emailing [support@appcues.com](mailto:support@appcues.com).

## License

Appcues is licensed under the [Appcues SDK License](https://github.com/appcues/ios-sdk-releases/LICENSE.md).