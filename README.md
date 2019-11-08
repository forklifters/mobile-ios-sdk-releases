<img width=443 src="https://uploads-ssl.webflow.com/5b227a6bd898e26d54ce18ac/5b76d242d0e5786ec310dd4d_Appcues-Logo-2018-Rebrand.svg" alt="Appcues Logo" />

[![ios 10+](https://img.shields.io/badge/iOS-10%2B-lightgrey.svg)](https://swift.org)
![cocoapods](https://img.shields.io/cocoapods/v/Appcues.svg)
[![carthage](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)
![license](https://img.shields.io/cocoapods/l/Appcues.svg)
[![tests](https://app.bitrise.io/app/156d3d483952dfb9/status.svg?token=fqKNRwYACUlwJGHPMNe3Dg&branch=master)](https://app.bitrise.io/app/156d3d483952dfb9)

# Appcues iOS SDK Releases

This repository contains binary distributions of the iOS SDK released by [Appcues](https://www.appcues.com/mobile/ios).

If you have any questions, comments, or issues related to any products distributed via this repository then please contact the team by emailing [support@appcues.com](mailto:support@appcues.com).

## Appcues iOS SDK

The Appcues iOS SDK allows iOS app developers to build, publish, and test onboarding flows, without submitting to the app store. The SDK is a framework that is compatible with Objective-C and Swift projects that target **iOS 10** and higher.

In order to use Appcues you must register an account on https://studio.appcues.com/mobile, and install the SDK into your iOS app. You can then use the SDK in conjunction with the mobile web editor to set up flows that will be targeted to live users of your app.

Before installing Appcues, make sure that you

1. [Create and join an Appcues Account](https://appcues.wistia.com/medias/i2ss29oa71)
2. [Navigate to the Mobile Web Editor](https://appcues.wistia.com/medias/efeq7u4yt7)

Fully integrating the SDK into your app involves these steps:

1. [Installation](#Installation)
   - [CocoaPods](#CocoaPods-Installation)
   - [Carthage](#Carthage-Installation)
   - [Manual Installation](#Direct-Framework-Installation)
2. [Setup Appcues](#Setup-Appcues)
3. [Pair Appcues Mobile SDK to Appcues Web](#Pair-Appcues-Mobile-SDK-to-Appcues-Web)
4. [Identify Users in your App](#Identify-Users-in-your-App)
5. [Identify Screens in your App](#Show-Flows-in-your-App)
6. [Launch the Appcues Mobile SDK Editor](#Pair-Appcues-Mobile-SDK-to-Appcues-Web)

The following steps are optional:

- [Send Custom Events to Appcues](#Send-Custom-Events-to-Appcues-optional)

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

and add the following to your `Podfile` :

```ruby
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

<img src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/ManualFrameworkInstall.png" alt="Install Framework" />

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
  Appcues.shared.setupWithKeyWindow(UIApplication.shared.keyWindow!)

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

#### Pair Appcues Mobile SDK to Appcues Web

Before adding flows to your app, a snapshot of your app needs to be sent from the device to the Mobile Web Editor. We recommend you use a real iOS device that is supported by your app to do this. You can use a Simulator device as well, but if you do, you should active the Accessibility Inspector (Xcode -> Open Developer Tool -> Accessibility Inspector) before you start sending snapshots of your app to the editor and build flows.

Take the following steps to access the Mobile SDK Editor within your app:

1. Set up an Appcues URL scheme:

Add the following entry to your app's Info.plist:

Your app's `Info.plist` will have a format similar to this:

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/InfoPListDefault.png" alt="Example Default App Info.plist" />

Add an entry by pressing the (+) button in Xcode's UI:

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/InfoPListWithURLSchemes.png"
alt="Example App Info.plist with updated URL Schemes" />

By default we recommend you use your app's `$(PRODUCT_NAME)` for the scheme name. You can view your app's `$(PRODUCT_NAME)` in your project's build settings:

<img
src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/ProductNameBuildSetting.png"
alt="Example App PRODUCT_NAME Build Setting" />

2. Hook the Appcues SDK into your `UIApplicationDelegate`'s `application:open:options:` method.

<i>Swift</i>

```swift
import Appcues

func application(_ app: UIApplication,
                open url: URL,
                options: [UIApplication.OpenURLOptionsKey: Any] = [:]) -> Bool {
  let appcuesHandlesOpenURL = Appcues.shared.application(app, openURL: url, options: options)
  // your application's code here
  let yourAppHandlesOpenURL = ...
  return yourAppHandlesOpenURL || appcuesHandlesOpenURL
}
```

<i>Objective-C</i>

```objective-c
@import Appcues;

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
  BOOL appcuesHandlesOpenURL = [Appcues.shared application:app openURL:url options:options];
  // your application's code here
  BOOL yourAppHandlesOpenURL = ...

  return yourAppHandlesOpenURL || appcuesHandlesOpenURL
}
```

2. Log into https://studio.appcues.com/mobile and generate a one time password [code](https://appcues.wistia.com/medias/f7hwhvx8in).

3. With the scheme example above, you will be able to launch the Appcues SDK Editor within your app by entering the following URL in Safari:

<img
src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/SafariURLEntry.png"
alt="Safari URL Entry" />

<img
src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/SafariAppLaunchPrompt.png"
alt="Safari App Launch Prompt" />

4. Accept the launch prompt and the Appcues Editor will be launched within your app. You can log into the Editor by entering the code which was generated from Appcues Web. If the code you entered is incorrect or expired, you will be prompted to generate another code. Otherwise the Appcues Editor button will show on top of your app on the top right corner of the screen.

<img height=500
src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/AppcuesMobileSDKEditor.png" alt="Appcues Mobile SDK Editor" />

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
  let user = AppcuesUser(userId: user.userId, attributes: userAttributes)
  Appcues.shared.identifyUser(user)

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
  AppcuesUser *user = [[AppcuesUser alloc] initWithUserId:user.id attributes:userAttributes];
  [Appcues.shared identifyUser:user];

  return YES;
}
```

Once a user is identified, the SDK automatically sends some user information to Appcues. This information is:

- `OS version` the iOS version that the device or simulator is running on. For instance, "12.1".
- `App version` the version of your app. For instance, "2.1.0".
- `Build version` the build version of your app. For instance, "1".
- `Device type` "iPhone", "iPad" or "Pod touch"
- `Day of week` the day of where the device or simulator is. For instance, "Monday", "Tuesday", "Wednesday" etc.
- `Device language` the local device or simulator language. For instance, "en" for English .
- `Simulator` true if your app is running on a simulator, otherwise false.
- `Appcues version` the Appcues Mobile sdk version your app is running. For instance, "0.3.0".

##### Using Appcues with Anonymous Users

_Do not add this call if you already have `Appcues.shared.identify()` implemented._

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

  Appcues.shared.showEligibleFlows()
}
```

<i>Objective-C</i>

```objective-c
@import Appcues;

- (void)viewDidAppear:(BOOL)animated {
  [super viewDidAppear:animated];

  [Appcues.shared showEligibleFlows];
}
```

#### Send Custom Events to Appcues (optional)

The targeting of your flows can be strengthened by enabling tracking of your users's behaviors and actions. Call the `track(events:)` method whenever an event should be sent to Appcues. The time at which the event occurred, as well as information about the user who experienced the event, is automatically recorded.

One example would be an auction app that wishes to show a message of congratulations after a user creates their first auction:

<i>Swift</i>

```swift
import Appcues

func createAuction() {
  let createdAuctionEvent = AppcuesEvent(name: "Created auction")
  let events = [createdAuctionEvent]
  Appcues.shared.trackEvents(events)
}
```

<i>Objective-C</i>

```objective-c
@import Appcues;

- (void)createAuction {
  AppcuesEvent *createdAuctionEvent = [[AppcuesEvent alloc] initWithName:@"Created auction" attributes:@{}];
  [Appcues.shared trackEvents:@[createdAuctionEvent]];
}
```

## Contact

You can reach the Appcues team at any time by emailing [support@appcues.com](mailto:support@appcues.com).

## License

Appcues is licensed under the [Appcues SDK License](https://github.com/appcues/ios-sdk-releases/blob/master/LICENSE).
