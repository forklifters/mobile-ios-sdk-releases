<img width=443 src="https://uploads-ssl.webflow.com/5b227a6bd898e26d54ce18ac/5b76d242d0e5786ec310dd4d_Appcues-Logo-2018-Rebrand.svg" alt="Appcues Logo" />

[![ios 10+](https://img.shields.io/badge/iOS-10%2B-lightgrey.svg)](https://swift.org)
![cocoapods](https://img.shields.io/cocoapods/v/Appcues.svg)
[![carthage](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)
![license](https://img.shields.io/cocoapods/l/Appcues.svg)

# Appcues iOS SDK Releases

This repository contains binary distributions of the iOS SDK released by [Appcues](https://www.appcues.com/mobile/ios).

If you have any questions, comments, or issues related to any products distributed via this repository, please contact the team. [Contact](#Contact).

## Appcues iOS SDK

The Appcues iOS SDK is an iOS Framework that is compatible with Objective-C and Swift projects that target **iOS 10** and higher.

The SDK & Appcues Studio can be used together to build, edit, publish, and target Flows that show to Users of your App.

After performing a one time installation of the SDK into your App, you can use the SDK to send Snapshots of your App to Appcues Studio. There you can use the Snapshots to create Screens that define specific parts of your App that you can build Flows on. These Flows can then be targeted to specific Users of your App & updated at any time, without submitting App updates to the App Store.

Before installing the SDK, make sure to:

1. Create a mobile Appcues account by contacting sales@appcues.com

2. Navigate to your Mobile Studio account:

   <img src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/MobileStudio_Flows_Page.png" alt="Mobile Studio Flows Page" />

End-to-end integration of the SDK into your app involves these steps:

1. [Add the SDK as a Dependency of your App](#Add-the-SDK-as-a-Dependency-of-your-App)

   - [Add the SDK using CocoaPods](#Add-the-SDK-using-CocoaPods)
   - [Add the SDK using Carthage](#Add-the-SDK-using-Carthage)
   - [Add the SDK without a Dependency Manager](#Add-the-SDK-without-a-Dependency-Manager)

2. [One Time App Configuration](#One-Time-App-Configuration)

   - [Create a URL Scheme](#Create-a-URL-Scheme)
   - [Initialize the SDK](#Initialize-the-SDK)

3. [Configuring your App to show Flows to your Users](#Configuring-your-App-to-show-Flows-to-your-Users)

   - [Identify a User and Record User Profile Updates](#Identify-a-User-and-Record-User-Profile-Updates)
   - [Identify an Anonymous User and Record User Profile Updates](#Identify-an-Anonymous-User-and-Record-User-Profile-Updates)
   - [Automatically Recorded User Profile Auto-Properties](#Automatically-Recorded-User-Profile-Auto-Properties)
   - [Send User Activities to show Flows](#Send-User-Activities-to-show-Flows)

4. [Launch the Appcues SDK Editor](#Launch-the-Appcues-SDK-Editor)

5. [Upload a Screen to Appcues Studio](#Upload-a-Screen-to-Appcues-Studio)

6. [Create a Screen](#Create-a-Screen)

7. [Add a Flow to the Screen](#Add-a-Flow-to-the-Screen)

   - [Add a Modal Step to the Flow](#Add-a-Modal-Step-to-the-Flow)
   - [Add a Tooltip Step to the Flow](#Add-a-Tooltip-Step-to-the-Flow)
   - [Flow Styling](#Flow-Styling)

8. [Target the Flow to Users](#Target-the-Flow-to-Users)

9. [Publish the Flow](#Publish-the-Flow)

The following steps are optional:

10. [Record User Events](#Record-User-Events-Optional)
11. [Implement Deep Linking](#Implement-Deep-Linking-Optional)

## Add the SDK as a Dependency of your App

The SDK can be added as a dependency of your application by using a dependency manager such as CocoaPods or Carthage, or by embedding the framework directly via Xcode.

#### Add the SDK using CocoaPods

The recommended path for installation is [CocoaPods](http://cocoapods.org/). CocoaPods provides a simple, versioned dependency management system that automates the tedious and error prone aspects of manually configuring libraries and frameworks. You can add the SDK to your project via CocoaPods with these steps:

Install Cocoapods:

```sh
$ sudo gem install cocoapods
$ pod setup
```

Next create a `Podfile` in the root of your project directory:

```sh
$ pod init
```

Add the following to your `Podfile` where `YourAppTarget` is replaced by your App's main target in Xcode:

```ruby
target "YourAppTarget" do
  inherit! :search_paths

  # ... Your App's other dependencies

  pod "Appcues"

  # We always recommend you use the latest SDK version,
  # but optionally, you can point to a specific version with:

  # pod "Appcues", "0.18.4"
end
```

Complete the installation by executing:

```sh
$ pod update
```

#### Add the SDK using Carthage

[Carthage](https://github.com/Carthage/Carthage) is an alternative dependency management system that is supported via the [Carthage Binary JSON Spec](https://github.com/Carthage/Carthage/blob/master/Documentation/Artifacts.md#binary-project-specification). To install via Carthage, add a `Cartfile` to your project with these contents:

```sh
binary "https://raw.githubusercontent.com/appcues/ios-sdk-releases/master/Appcues.framework.json"
```

and run:

```sh
$ carthage update
```

You can then complete the installation by following the default [Carthage Setup Instruction](https://github.com/Carthage/Carthage#quick-start).

#### Add the SDK without a Dependency Manager

If you wish to install Appcues directly into your application without using a dependency manager, download the `Appcues.framework` artifact from this repository and add it to your application:

1. Add the framework to the _Embedded Binaries_ section of your App's Target in Xcode, instructing Xcode to copy items into your destination group's folder.

<img src="https://s3-us-west-2.amazonaws.com/appcues-public/mobile/readme+assets/ManualFrameworkInstall.png" alt="Install Framework" />

2. The framework distribution includes Simulator Architectures so that you can build and run it in an iOS Simulator, but these need to be removed when archiving for submission to App Store Connect. To do this, a script is included in the framework to strip these architectures, but must be configured on your project so that it runs whenever you archive your App for a release.

Add the below script to your target's _Build Phases_, by selecting your project, then the main App Target in the Targets list, then the _Build Phases_ tab, selecting the `+` button, selecting _New Run Script Phase_, and pasting the below code in the script content. Make sure this script is ordered below the _Embedded Frameworks_ build phase.

```ruby
bash "$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH/Appcues.framework/strip_frameworks.sh"
```

#### Verifying SDK Dependency Installation

Add the following import to your `UIApplicationDelegate` class. This import also needs to be included in any other source files that need to access the SDK:

<i>Swift</i>

```swift
import Appcues
```

<i>Objective-C</i>

```objective-c
@import Appcues;
```

After this, do a clean build, run your project and confirm that no build errors occur.

## One Time App Configuration

The following configuration of your App only needs to be done once for a successful SDK integration.

#### Create a URL Scheme

You will need to add a URL Scheme to your App's `Info.plist` to allow for launching the Appcues SDK Editor in Safari or another mobile browser.

##### 1. Find URL Scheme

To find your URL Scheme item, go to the "Mobile IDs" section in [Appcues Studio](https://studio.appcues.com/settings/account). If you have already claimed an id, you'll find your App Bundle Id and the corresponding Mobile Id in this section.

If you have not yet paired a device for your app, you'll find the Mobile Id under "Unclaimed Mobile ID".

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/Studio_MobileIds.png" alt="Example Mobile Ids" />

Your URL Scheme consists of a Mobile Id with an `appcues-` prefix.

From the example above, your URL Scheme for an unclaimed app would be:
appcues-c9fbbfa0-279c-490d-9cd8-eccdf2558635

##### 2. Add new Editor URL type

In your app's `Info.plist`, click the plus icons to have the `URL types` entry added in the following format where:

- `Document Role` is `Editor`
- `URL Identifier` is `com.appcues.scheme`
- `URL Schemes` has item found in the step above.

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/URLSchemeAPIKey.png" alt="Example Default App Info.plist" />

##### 3. Hook the Appcues SDK into your `UIApplicationDelegate`'s `application:open:options:` function

Here are some code snippets to start you off:

<i>Swift</i>

```swift
func application(_ app: UIApplication,
                open url: URL,
                options: [UIApplication.OpenURLOptionsKey: Any] = [:]) -> Bool {

  let yourAppHandlesTheURL = ... // Your App's URL handling code here
  let appcuesHandlesTheURL = Appcues.shared.application(app, openURL: url, options: options)

  return yourAppHandlesTheURL || appcuesHandlesTheURL
}
```

<i>Objective-C</i>

```objective-c
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {

  BOOL yourAppHandlesTheURL = ... // Your App's URL handling code here
  BOOL appcuesHandlesTheURL = [Appcues.shared application:app openURL:url options:options];

  return yourAppHandlesTheURL || appcuesHandlesTheURL
}
```

#### Initialize the SDK

In your `UIApplicationDelegate`, initialize the SDK by calling `Appcues.setup(mobileId:)` at the end of the `application(_:didFinishLaunchingWithOptions:)` function. Ensure this is done before any access to the SDK via `Appcues.shared`.

Your Mobile Id can be found under the `Mobile IDs` section on
https://studio.appcues.com/settings/account

<i>Swift</i>

```swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {

  // Your App's initialization code here

  Appcues.setup(mobileId: "your-mobile-id-here")

  return true
}
```

<i>Objective-C</i>

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

  // Your App's initialization code here

  [Appcues setupWithMobileId: @"your-mobile-id-here"];

  return YES;
}
```

### Configuring your App to show Flows to your Users

These steps need to be taken whenever you need to change the way you capture data about your Users that will be used to target your Flows to them.

In general, this involves identifying a User, recording User Profile Updates that are needed for Flow targeting, and sending these User activities to Appcues, so that Flows that User is qualified to see is shown to them.

#### Identify a User and Record User Profile Updates

Users have to be identified to see Flows. To identify a User, use the `identifyUserWithId(userId:)` function.

Once a User is identified, additional properties about the User can be recorded and then sent for Flow Targeting. To record User Profile Updates, use `record(userProfileUpdate:)`. Note that this data will be saved locally in memory by the SDK, but won't be sent to Appcues until you call `sendActivities(completion:)` ([Send User Activities to show Flows](Send-User-Activities-to-show-Flows)), after which it will be cleared from memory.

<i>Swift</i>

```swift
func application(
  _ application: UIApplication,
  didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?
  ) -> Bool {

  // Your App's initialization code here

  Appcues.setup(mobileId: "your-mobile-id-here")

  let userId = "TestUser1"
  let customProperties = ["name": user.name, "email": user.email]
  let userProfileUpdate = AppcuesUserProfileUpdate(customProperties: customProperties)
  Appcues.shared.identifyUserWithId(userId: userId)
  Appcues.shared.record(userProfileUpdate: userProfileUpdate)

  return true
}
```

<i>Objective-C</i>

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

  // Your App's initialization code here

  [Appcues setupWithMobileId: @"your-mobile-id-here"];

  NSString *userId = "TestUser1"
  NSDictionary *customProperties = @{ @"name": user.name, @"email": user.email };
  AppcuesUserProfileUpdate *userProfileUpdate = [[AppcuesUserProfileUpdate alloc] initWithCustomProperties: customProperties];

  [Appcues.shared identifyUserWithId: userId];
  [Appcues.shared recordUserProfileUpdate: userProfileUpdate];

  return YES;
}
```

#### Identify an Anonymous User and Record User Profile Updates

_Note: Do not add this call if you are already using `Appcues.shared.identifyUserWithId(userId:)` to identify Users._

Uniquely identifying Users will give you the most control over Flow Targeting, but the `identifyAnonymousUser()` function can be used when Flows are not targeted to a specific User or for initial testing.

<i>Swift</i>

```swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

  // Your own app's initialization code here

  Appcues.setup(mobileId: "your-mobile-id-here")

  let customProperties = ["name": "TestName", "email": "testemail@email.com"]
  let userProfileUpdate = AppcuesUserProfileUpdate(customProperties: customProperties)

  Appcues.shared.identifyAnonymousUser()
  Appcues.shared.record(userProfileUpdate: userProfileUpdate)

  return true
}
```

<i>Objective-C</i>

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

  // Your own app's initialization code here

  [Appcues setupWithMobileId: @"your-mobile-id-here"];

  NSDictionary *customProperties = @{ @"name": "TestName", @"email": @"testemail@email.com" };
  AppcuesUserProfileUpdate *userProfileUpdate =
    [[AppcuesUserProfileUpdate alloc] initWithCustomProperties: customProperties];

  [Appcues.shared identifyAnonymousUser];
  [Appcues.shared recordUserProfileUpdate: userProfileUpdate];

  return YES;
}
```

#### Automatically Recorded User Profile Auto-Properties

Once a User is identified, the SDK automatically sends some User Properties to the Appcues Platform. This information is:

- `appcues_app_domain_version`: The bundle version of the App - as determined from the App's unique bundle identifier. For example: "2.1.0".
- `appcues_app_domain_build_version`: The bundle build version of your app - as determined from the App's unique bundle identifier. For example: "1".
- `appcues_device_type`: "iPhone", "iPad" or "iPod touch"
- `appcues_device_os_version`: The iOS version that the device or simulator is running on. For example: "12.1".
- `appcues_device_language`: The device or simulator language. For example: "en" for English.
- `appcues_device_is_simulator`: true if your App is running on a simulator, otherwise false.
- `appcues_sdk_version`: The version of the Appcues iOS SDK that your App is using. For example: "0.17.4".

#### Send User Activities to show Flows

You App will need to call the `sendActivities(completion:)` function any time you want to upload User Profile data previously recorded with `record(userProfileUpdate:)` or `record(userEvents:)` to Appcues and have qualified Flows show in response.

We recommend you do this when you know your App's UI is ready to show Flows and you have recorded User Profile properties relevant for the Flow. Make sure to not make the `sendActivities(completion:)` call to early before all the UI elements have been laid out, otherwise Appcues can not guarantee that the screen targeting would qualify and expected flows might not appear.

For example, you can make this call on the `viewDidAppear` life-cycle function of `UIViewController`s in your App:

<i>Swift</i>

```swift
override func viewDidAppear(_ animated: Bool) {
  super.viewDidAppear(animated)

  Appcues.shared.sendActivities()
}
```

<i>Objective-C</i>

```objective-c
- (void)viewDidAppear:(BOOL)animated {
  [super viewDidAppear:animated];

  [Appcues.shared sendActivities];
}
```

### Launch the Appcues SDK Editor

To create Flows on Appcues Studio, you have to first define the Screens that describe specific UI portions of your App which you can show Flows on.

To create these Screens, you use the SDK Editor to take a Snapshot of your App, so that you can describe what parts of the UI identify the Screen.

To access the SDK Editor take the steps [here](https://docs.appcues.com/article/675-pairing).

If you encounter errors in the pairing process, please check out our [FAQ](#FAQ).

### Upload a Screen to Appcues Studio

After the SDK Editor is launched, Snapshots of your App can be sent to Appcues Studio from which you can define your App's Screens.

We recommend that you use a real iOS Device that is supported by your App to do this. A Simulator can be used as well, but depending on how you have configured your App, a Simulator build may not include the same UI data as a Device build which may result in Flows not showing to your Users on real Devices.

In Appcues Studio, select Upload Screen:

<img src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/MobileStudio_UploadScreen.gif" alt="Mobile Studio Upload Screen" />

Following the instructions on Appcues Studio, tap the Appcues SDK Editor Button and then select the option to _Send Screen_ when prompted.

<img src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/readme+assets/AuthoringMode_Menu.png" alt="Authoring Mode Menu" />

Once a Snapshot is uploaded to Appcues Studio, you can use it to create a uniquely identified Screen.

### Create a Screen

After receiving the Snapshot, Appcues Studio should show the Screen creation page, where you can select elements in the Snapshot which uniquely identify the Screen.

Elements that are highlighted green are unique on the Snapshot and make good candidates for Screen identification. Elements highlighted yellow are not unique. They can still be used for Screen identification, but will not be as accurate as the unique elements and may result in Screens not being detected if your App changes where they are located on future App releases.

The elements are identified via iOS's accessibility system. For best results, please follow Apple's documentation on accessibility when building your App: https://developer.apple.com/documentation/uikit/accessibility/.

In particular, Appcues relies on observing meaningful [accessibilityLabel](https://developer.apple.com/documentation/objectivec/nsobject/1615181-accessibilitylabel) and [accessibilityTraits](https://developer.apple.com/documentation/uikit/accessibility/uiaccessibility/accessibility_traits) data for your `UIView` elements to work correctly. If you use built in iOS controls these values will always follow Apple's recommended accessibility conventions, but custom controls should be designed with these conventions in mind as well.

In the example below, a Screen is defined by three conditions:

- A navigation item title with the text "Home"
- A Tab item button that is selected
- A label with the text "Discover"

As long as they are qualified by Flow Targeting, Flows built on this Screen will show to your App's Users when they navigate to this part of your App.

Note that Screens can be as specific or as generic as your App requires. You can define a Screen that has no conditions and Flows built on it will show anywhere in your App. You can define a Screen that is very specific with very detailed conditions and this Screen will only be detected on the part of your App that has the specific elements in the conditions. The only rule to keep in mind is, you can't define two Screens with the same elements since Screens have to be uniquely identified.

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_PickElements.gif"
alt="Mobile Studio Pick Elements" />

Before saving the Screen, don't forget to choose a meaningful name for it:

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_NameScreen.gif"
alt="Mobile Studio Save Screen" />

Once a Screen is defined, you can test that the screen targeting works by going to the screen on your device, tap the SDK Editor Button and select Screen match. If the elements you selected for your Screen is visible on the device, the name of the Screen should appear in this list.

### Add a Flow to the Screen

After the Screen is defined, a Flow can be built on top of it. Currently, Appcues supports creating Flows with Modal and Tooltip Steps.

#### Add a Modal Step to the Flow

To add a Modal Step to your Flow, click the `+` button and select Modal:

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_AddModal.gif"
alt="Mobile Studio Add Modal Step" />

Content can be changed directly in the Modal.

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_AddContentModal.gif"
alt="Mobile Studio Add Modal Content" />

#### Add a Tooltip Step to the Flow

To add a Tooltip Step to your Flow, click the `+` button and then select Tooltip. Hover over the Screen and select the Screen element to attach it to.

You can only attach Tooltips to elements that are a part of the Screen definition - i.e. the elements you chose when [creating the Screen](#Create-a-Screen).

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_AddTooltip.gif"
alt="Mobile Studio Add Tooltip" />

Content can be changed directly in the tooltip.

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_AddContentTooltip.gif"
alt="Mobile Studio Add Tooltip Content" />

#### Flow Styling

Flow styling can be configured on both the Flow and Step level.

Flow styling is set for all Steps in the Flow. Changing this styling in any Step results in changing it for all Steps in the Flow. Flow styling includes:

- Border radius
- Drop Shadow
- Backdrop

Step styling is set individually per Step, and includes:

- Text font
- Text color
- Text alignment
- Background color

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_Styling.png"
alt="Mobile Studio Styling" />

Once a Flow has been created, you can preview the flow on your device by tapping the SDK Editor Button and select Preview flow. A list will appear with all flows that would show for that specific Screen on your device. The list shows flows without user and event targeting.

### Target the Flow to Users

Once a Flow has been created it can be targeted to certain Users. For testing purposes, we recommend that you target the Flow to a specific test User, before broadening the targeting to reach more Users.

<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_Target.gif"
alt="Mobile Studio Targeting" />

### Publish the Flow

Once a Flow is published, it will be loaded by the Appcues SDK after any user of your App re-foregrounds it. At that point the Flow will start showing in your App to qualified Users based on the targeting rules you specify.

You can verify that targeting works by checking that the Flows you have created show where you expect on your Device. If your Device is logged into the SDK Editor, don't forget to select the "Enable Flows" option. Otherwise, if you are logged out of the Editor and are using the App normally, Flows will show as long as:

- The App has been configured with the correct `sendActivities(completion)` calls. ([Sending User Activities to Show Flows](#Send-User-Activities-to-Show-Flows))
- You navigate to the Screen(s) that the Flow is added to.
- The targeting rules of the Flow match the User Profile data that was sent by the App.

Note: To see recently published flows, make sure to re-foreground your app after publishing it.

### Record User Events (Optional)

The targeting of your flows can be strengthened by enabling tracking of your users' behaviors and actions. Call the `record(userEvents:)` function whenever an event should be recorded. The time at which the event occurred, as well as information about the user who experienced the event, is automatically recorded.

Just like with `record(userProfileUpdate:)`, the User Event data is only sent to Appcues when `sendActivities(completion:)` is called. [Sending User Activities to Show Flows](#Sending-User-Activities-to-Show-Flows)

One example of using User Events would be an Auction App that wishes to show a message of congratulations after a User creates their first Auction:

<i>Swift</i>

```swift
func createAuction() {
  let createdAuctionEvent = AppcuesEvent(name: "Created Auction")
  Appcues.shared.record(userEvents: [createdAuctionEvent])
}
```

<i>Objective-C</i>

```objective-c
- (void)createAuction {
  AppcuesEvent *createdAuctionEvent = [[AppcuesEvent alloc] initWithName:@"Created auction" attributes:@{}];
  [Appcues.shared recordUserEvents:@[createdAuctionEvent]];
}
```

### Implement Deep Linking (Optional)

The Appcues SDK supports redirects to other screens in your app once a flow completes.

When a flow completes, the Appcues SDK delegates to
the [UIApplicationDelegates](https://developer.apple.com/documentation/uikit/uiapplicationdelegate) instance method `application(\_:open:options:)` and it's here the redirect logic should be implemented.

<i>Swift</i>

```swift
func application(_ app: UIApplication,
                open url: URL,
                options: [UIApplication.OpenURLOptionsKey: Any] = [:]) -> Bool {

  let yourAppHandlesTheURL = ... // Your App's URL handling code here
  let appcuesHandlesTheURL = Appcues.shared.application(app, openURL: url, options: options)

  return yourAppHandlesTheURL || appcuesHandlesTheURL
}
```

<i>Objective-C</i>

```objective-c
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {

  BOOL yourAppHandlesTheURL = ... // Your App's URL handling code here
  BOOL appcuesHandlesTheURL = [Appcues.shared application:app openURL:url options:options];

  return yourAppHandlesTheURL || appcuesHandlesTheURL
}
```

## FAQ

For commonly asked questions, see [here](https://docs.appcues.com/article/525-faq).

## Contact

You can reach the Appcues team at any time by emailing [support@appcues.com](mailto:support@appcues.com).

If you are reporting a bug or have a specific question about behavior on a test device, please reproduce the issue and then provide the exact time UTC you reproduced the issue, your associated Appcues' Account ID as well as the associated iPhone's Device Name (iPhone Settings > General > About > Name).

Account ID can be found in Appcues Studio Settings:
<img
src="https://appcues-public.s3-us-west-2.amazonaws.com/mobile/assets/MobileStudio_FindAccountId.gif"
alt="Mobile Studio Find AccountId" />

## License

Appcues is licensed under the [Appcues SDK License](https://github.com/appcues/ios-sdk-releases/blob/master/LICENSE).
