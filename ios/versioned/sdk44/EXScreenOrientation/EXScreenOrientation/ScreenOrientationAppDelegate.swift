// Copyright 2018-present 650 Industries. All rights reserved.

import ABI44_0_0ExpoModulesCore

public class ScreenOrientationAppDelegate: ExpoAppDelegateSubscriber {
  public func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
    if let screenOrientationRegistry = ModuleRegistryProvider.getSingletonModule(for: ABI44_0_0EXScreenOrientationRegistry.self) as? ABI44_0_0EXScreenOrientationRegistry {
      screenOrientationRegistry.updateCurrentScreenOrientation()
    }
    return true
  }
}
