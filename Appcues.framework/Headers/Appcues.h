#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

FOUNDATION_EXPORT double AppcuesVersionNumber;

FOUNDATION_EXPORT const unsigned char AppcuesVersionString[];

NS_ASSUME_NONNULL_BEGIN

@interface AppcuesEvent : NSObject

@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, strong, readonly) NSDictionary<NSString *, id> *attributes;

- (AppcuesEvent *)initWithName:(NSString *)name attributes:(NSDictionary<NSString *,id> *)attributes;

@end

@interface AppcuesUser : NSObject

@property (nonatomic, copy, readonly) NSString *userID;
@property (nonatomic, strong, readonly) NSDictionary<NSString *, id> *attributes;

- (AppcuesUser *)initWithUserID:(NSString *)userID attributes:(NSDictionary<NSString *, id> *)attributes;

@end

/*!
 @class Appcues

 @brief The Appcues SDK

 @discussion Represents the public facing interface for the Appcues SDK.
 */
@interface Appcues : NSObject

/*!
 Singleton instance of Appcues.
 */
@property (class, nonatomic, readonly, strong) Appcues *shared
NS_SWIFT_NAME(shared);

/*!
 Sets up `Appcues` for integration with your app. Call this method after your `UIApplicationDelegate`'s
 `application(application:didFinishLaunchingWithOptions:)` method - after your app's `UIWindow` is made
 `makeKeyAndVisible`.

 @pre The app's main `UIWindow` should be made `makeKeyAndVisible` before calling this method.
 */
- (void)setup
NS_SWIFT_NAME(setup());

/*!
 Sets up `Appcues` for integration with your app. This method should be used as a fallback for applications that
 have more complex `UIWindow` usage - such as those that use multiple `UIWindows`. Here you can provide your app's
 `key` `UIWindow`. `Appcues` will use this window for the rest of its functionality.

 @param keyWindow The `UIApplicationDelegate`'s `keyWindow`.
 */
- (void)setupWithKeyWindow:(UIWindow *)keyWindow
NS_SWIFT_NAME(setupWithKeyWindow(_:));

/*!
 Used to allow `Appcues` to hook into the `UIApplicationDelegate`'s `application:open:options:` method.

 @pre `Appcues` SDK integration requires calling this method in your `UIApplicationDelegate` as follows:
 ```
 func application(_ app: UIApplication,
                  open url: URL,
                  options: [UIApplication.OpenURLOptionsKey: Any] = [:]) -> Bool {
   let result = Appcues.shared.application(app, open: url, options: options)
   // your application's code here
   return result
 }
 ```
 @pre The following URL scheme entry is added to the app's Info.plist:
 ```
<key>CFBundleURLTypes</key>
<array>
  <dict>
    <key>CFBundleTypeRole</key>
    <string>Editor</string>
    <key>CFBundleURLName</key>
    <string>com.appcues.scheme</string>
    <key>CFBundleURLSchemes</key>
    <array>
      <string>$(PRODUCT_NAME)</string>
    </array>
  </dict>
</array>
 ```
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options
NS_SWIFT_NAME(application(_:openURL:options:));

/*!
 Identifies an `AppcuesUser` for flow targeting.

 @param user The `AppcuesUser` to track, identified by an id and optional custom attributes.
 */
- (void)identifyUser:(AppcuesUser *)user
NS_SWIFT_NAME(identifyUser(_:));

/*!
 Identifies an "anonymous" `AppcuesUser`. This user is identified via a unique UUID which is generated by the SDK.
 */
- (void)anonymous
NS_SWIFT_NAME(anonymous());

/*!
 Tracks the given list of `AppcuesEvent`s so that they can be used for flow targeting.

 @param events List of `AppcuesEvent`s to track, each identified by a name and optional custom attributes.
 */
- (void)trackEvents:(NSArray<AppcuesEvent *> *)events
NS_SWIFT_NAME(trackEvents(_:));

/*!
 Attempts to show eligible flows for the screen.

 @param  name  A unique name that identifies the screen.
 */
- (void)showEligibleFlowsForScreenName:(NSString *)name
NS_SWIFT_NAME(showEligibleFlowsForScreenName(_:));

@end

NS_ASSUME_NONNULL_END
