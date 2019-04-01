<img width=443 src="https://uploads-ssl.webflow.com/5b227a6bd898e26d54ce18ac/5b76d242d0e5786ec310dd4d_Appcues-Logo-2018-Rebrand.svg" alt="Appcues Logo" />

[![swift](https://img.shields.io/badge/Swift-4.2-orange.svg)](https://developer.apple.com/swift)
[![ios 9+](https://img.shields.io/badge/iOS-9%2B-lightgrey.svg)](https://swift.org)
[![xcode 10.1](https://img.shields.io/badge/Xcode-10.1%2B-blue.svg)](https://swift.org)
![cocoapods](https://img.shields.io/cocoapods/v/Appcues.svg)
[![carthage](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)
![license](https://img.shields.io/cocoapods/l/Appcues.svg)
[![tests](https://app.bitrise.io/app/156d3d483952dfb9/status.svg?token=fqKNRwYACUlwJGHPMNe3Dg&branch=master)](https://app.bitrise.io/app/156d3d483952dfb9)

# Appcues iOS SDK Releases

This repository contains binary distributions of the iOS SDK released by [Appcues](https://www.appcues.com/mobile/ios).

If you have any questions, comments, or issues related to any products distributed via this repository then please contact the team by emailing [support@appcues.com](mailto:support@appcues.com).

## Appcues iOS SDK

The Appcues iOS SDK allows iOS app developers to build, publish, and test onboarding flows, without submitting to the app store. The SDK is a dynamic framework that is compatible with Objective-C and Swift projects that target **iOS 9** and higher, **Xcode 10.1** and higher. 

In order to use Appcues you must register an account on https://beta.my.appcues.com/mobile, and install the SDK into your iOS app. You can then use the SDK in conjunction with the mobile web editor to set up flows that will be targeted to live users of your app.

Before installing Appcues, make sure that you 
1. [Create and join an Appcues Account](https://appcues.wistia.com/medias/i2ss29oa71)
2. [Navigate to the Mobile Web Editor](https://appcues.wistia.com/medias/efeq7u4yt7) 

Fully integrating the SDK into your app involves these steps:
1. [Installation](#Installation)
    -  [CocoaPods](#CocoaPods-Installation)
    -  [Carthage](#Carthage-Installation)
    -  [Manual Installation](#Direct-Framework-Installation)
2. [Setup Appcues](#Setup-Appcues)
3. [Identify Users in your App](#Identify-Users-in-your-App)
4. [Identify Screens in your App](#Show-Flows-in-your-App)
5. [Launch the Appcues Mobile SDK Editor](#Launch-Appcues-Mobile-SDK-Editor)
6.  [Add AccessibilityIdentifiers to your App](#Add-AccessibilityIdentifiers-to-your-App)

The following steps are optional: 
* [Enable Appcues Logs](#Enable-Appcues-Logs)
* [Send Custom Events to Appcues](#Send-Custom-Events-to-Appcues)

### Installation

Appcues can be installed into your application by importing a framework or via CocoaPods. Quick installation instructions are provided below for reference, but please refer to the [Appcues iOS Documentation](https://docs.appcues.com/collection/390-mobile-appl) for full details and troubleshooting.

#### CocoaPods Installation

The recommended path for installation is [CocoaPods](http://cocoapods.org/). CocoaPods provides a simple, versioned dependency management system that automates the tedious and error prone aspects of manually configuring libraries and frameworks. You can add Appcues to your project via CocoaPods by doing the following:

```sh
$ sudo gem install cocoapods
$ pod setup
```

Now create a `Podfile` in the root of your project directory

```sh
$ pod init
```
and add the following to your  `Podfile` :

```ruby
use_frameworks!

pod 'Appcues'
```

Complete the installation by executing:

```sh
$ pod install
```

These instructions will setup your local CocoaPods environment and import Appcues into your project. Once this has completed, test your installation by referring to the [Verifying Appcues Configuration](#verifying-appcues-configuration) section below.

#### Carthage Installation

[Carthage](https://github.com/Carthage/Carthage) is an alternative dependency management system that we support via the Carthage [binary json spec](https://github.com/Carthage/Carthage/blob/master/Documentation/Artifacts.md#binary-project-specification). To install via Carthage, add a `Cartfile` to your project with these contents:

```sh
binary "https://raw.githubusercontent.com/appcues/ios-sdk-releases/master/Appcues.framework.json"
```

and run:

```sh
$ carthage update
```

You can then complete the installation by following the default Carthage [setup instructions](https://github.com/Carthage/Carthage#quick-start).

#### Direct Framework Installation

If you wish to install Appcues directly into your application via the binary framework, download the `Appcues.framework` artifact from this repository and add it to your application:

1. Add the framework to the `Embedded Binaries` section of your app `target` in `Xcode`, instructing Xcode to copy items into your destination group's folder.

...<img width=600 src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/ManualFrameworkInstall.png" alt="Install Framework" />

2. The framework distribution includes simulator architectures so that you can build and run it in an `iOS Simulator`, but these need to be removed when archiving for submission to iTunesConnect. To do this, a script is included in the framework to strip these architectures, but must be configured on your project so that it runs whenever you build the app for archive. 

Add the below script to your target's Build Phases, by selecting your project, then the main app target in the `TARGETS` list, then the `Build Phases` tab, selecting the `+` button, selecting `New Run Script Phase`, and pasting the below code in the script content. Make sure this script is ordered below the `Embedded Frameworks` `Build Phase`.

```ruby
bash "$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH/Appcues.framework/strip_frameworks.sh"
```

Build and run your project to verify installation was successful. Once you have completed a successful build, refer to the section below for details on how to test your setup.

### Verifying Appcues Configuration

Once you have finished installing Appcues via CocoaPods or the Framework, you can test your installation by initializing Appcues. 

#### Setup Appcues

In your `UIApplicationDelegate`, setup Appcues by calling `Appcues.shared.setup()` at the end of the `application(_:didFinishLaunchingWithOptions:)` method. 

You can also watch a video of how to setup Appcues [here](https://appcues.wistia.com/medias/2irgu29cpc).

<i>Swift</i>
```swift
import Appcues

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
  // Your own app's initialization code here
  Appcues.shared.setup()

  return true
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Your own app's initialization code here

  [Appcues.shared setup];

  return YES;
}
```

In cases of non standard window usage, for instance if your application uses multiple windows or does not initialize the keyWindow when the app launches, a keyWindow can be provided to Appcues with `Appcues.shared.setup(keyWindow:)`

<i>Swift</i>
```swift
import Appcues

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
  // Your own app's initialization code here
  Appcues.shared.setupWith(keyWindow: UIApplication.shared.keyWindow!)

  return true
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Your own app's initialization code here

  [Appcues.shared setupWithKeyWindow:UIApplication.sharedApplication.keyWindow];

  return YES;
}
```

#### Enable Appcues Logs

The SDK can print console logs that can help troubleshoot issues with your installation. The framework currently supports two log levels: `none`, and `debug`, which shows all error logs. By default, the log level is `none`. *Important:* When deploying your app, ensure that logging is disabled by removing this code or setting the `none` log level.

<i>Swift</i>
```swift
import Appcues

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
  // Your own app's initialization code here

  Appcues.shared.update(logLevel: .debug)
  Appcues.shared.setup()

  return true
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Your own app's initialization code here

  [Appcues.shared updateWithLogLevel:AppcuesLogLevelDebug];
  [Appcues.shared setup];

  return YES;
}
```

#### Identify Users in your App

Users have to be identified to see flows. An `AppcuesUser` must have a unique id, and can have attached custom user attributes. You can find recommendations of additional user attributes to track [here](https://docs.appcues.com/article/410-mobile-user-properties-overview).

You can also watch a video of how to do identify users [here](https://appcues.wistia.com/medias/bdooulc8r1).

<i>Swift</i>
```swift
import Appcues

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
  // Your own app's initialization code here

  Appcues.shared.setup()
  let userAttributes = ["name": user.name, "email": user.email]
  let user = AppcuesUser(id: user.id, attributes: userAttributes)
  Appcues.shared.identify(user: user)

  return true
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Your own app's initialization code here

  [Appcues.shared setup];
  NSDictionary *userAttributes = @{ @"name": user.id, @"email": user.email };
  AppcuesUser *user = [[AppcuesUser alloc] initWithId:user.id attributes:userAttributes];
  [Appcues.shared identifyWithUser:user];

  return YES;
}
```

Once a user is identified, the SDK automatically sends some user information to Appcues. This information is:
* `OS version` the iOS version that the device or simulator is running on. For instance, "12.1".
* `App version` the version of your app. For instance, "2.1.0".
* `Build version` the build version of your app. For instance, "1".
* `Device type` "iPhone", "iPad" or "Pod touch"
* `Day of week` the day of where the device or simulator is. For instance, "Monday", "Tuesday", "Wednesday" etc.
* `Device language` the local device or simulator language. For instance, "en" for English .
* `Simulator` true if your app is running on a simulator, otherwise false.
* `Appcues version` the Appcues Mobile sdk version your app is running. For instance, "0.3.0".

##### Using Appcues with Anonymous Users

*Do not add this call if you already have `Appcues.shared.identify()` implemented.*

Uniquely identifying users will give you the most control over flow targeting, but the `anonymous` method can be used when flows are not targeted to specific users or for initial testing.

<i>Swift</i>
```swift
import Appcues

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
  // Your own app's initialization code here

  Appcues.shared.setup()
  Appcues.shared.anonymous()

  return true
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Your own app's initialization code here

  [Appcues.shared setup];
  [Appcues.shared anonymous];

  return YES;
}
```

#### Show Flows in your App

In order for the Appcues SDK to know what screen a user is on and to find all the flows that qualify for that screen, a screen needs to be identified. Add the following code to the screen where you want to check for flows. We recommended adding this code after the view finishes appearing - i.e. the corresponding `UIViewController`'s `viewDidAppear` method.

You can also watch a video of how to do enable flows [here](https://appcues.wistia.com/medias/3hdrm9xfre).

<i>Swift</i>
```swift
import Appcues

override func viewDidAppear(_ animated: Bool) {
  super.viewDidAppear(animated)

  Appcues.shared.showEligibleFlowsOn(viewController: self, named: "HomeScreen")
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (void)viewDidAppear:(BOOL)animated {
  [super viewDidAppear:animated];

  [Appcues.shared showEligibleFlowsOnViewController:self named:@"HomeScreen"];
}
```

#### Launch Appcues Mobile SDK Editor

Before adding flows to your app, a screen needs to be sent from the device to the Mobile Web Editor. The Mobile SDK Editor can be launched from anywhere in your code, after the SDK is set up.

<i>Swift</i>
```swift
import Appcues

func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
  // Your own app's initialization code here

  Appcues.shared.setup()
  Appcues.shared.launchEditor()

  return true
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Your own app's initialization code here

  [Appcues.shared setup];
  [Appcues.shared launchEditor];

  return YES;
}
```

Once the Appcues Mobile SDK Editor is launched, it can be seen in the upper right corner of your app.
<img height=500
src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/AppcuesMobileSDKEditor.png" alt="Appcues Mobile SDK Editor" />

If you launch the Mobile SDK Editor for the first time, you will be prompted to login. The code can be found in the Mobile Web, more detailed instructions [here](https://appcues.wistia.com/medias/f7hwhvx8in).

#### Send Custom Events to Appcues 

The targeting of your flows can be strengthened by enabling tracking of your users's behaviors and actions. Call the `track(events:)` method whenever an event should be sent to Appcues. The time at which the event occurred, as well as information about the user who experienced the event, is automatically recorded.

One example would be an auction app that wishes to show a message of congratulations after a user creates their first auction:

<i>Swift</i>
```swift
import Appcues

func createAuction() {
  let createdAuctionEvent = AppcuesEvent(name: "Created auction")
  let events = [createdAuctionEvent]
  Appcues.shared.track(events: events)
}
```

<i>Objective-C</i>
```objective-c
@import Appcues;

- (void)createAuction {
  AppcuesEvent *createdAuctionEvent = [[AppcuesEvent alloc] initWithName:@"Created auction" attributes:@{}];
  [Appcues.shared trackWithEvents:@[createdAuctionEvent]];
}
```

#### Add AccessibilityIdentifiers to your App

In order to ensure tooltip placement accuracy, it is highly recommended to add [accessibilityIdentifiers](https://developer.apple.com/documentation/uikit/uiaccessibilityidentification/1623132-accessibilityidentifier) to your views.

You can see a detailed walkthrough of how to add accessibilityIdentifiers to your app [here](https://appcues.wistia.com/medias/kdyikd64q7).

## Contact

You can reach the Appcues team at any time by emailing [support@appcues.com](mailto:support@appcues.com).

## License

Appcues is licensed under the [Appcues SDK License](https://github.com/appcues/ios-sdk-releases/blob/master/LICENSE).
