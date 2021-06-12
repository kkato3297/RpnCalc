### for iOS

If cause error as below,
```
iphoneos is not an iOS SDK
```

do below command
```
sudo xcode-select -switch /Applications/Xcode.app/Contents/Developer
```

Generate RpnCalc Xcode project
```
mkdir xcode
cd xcode
cmake \
    -G Xcode \
    -DTARGET_PLATFORM=PLATFORM_IOS \
    -DTARGET_FORMAT=STATIC_LIBRARY \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_IOS_SDK_ROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS14.4.sdk \
    ..
```

Build
```
xcodebuild \
    -project RpnCalc.xcodeproj \
    -sdk iphonesimulator \
    -scheme RpnCalc \
    -configuration Release
# xcodebuild \
    -project RpnCalc.xcodeproj \
    -sdk iphoneos \
    -scheme RpnCalc \
    -configuration Release
```

After build
```
cd RpnCalc
mkdir Release
lipo \
    -output ./Release/libRpnCalc.a \
    -create \
    ./src/Release-iphoneos/libRpnCalc.a \
    ./src/Release-iphonesimulator/libRpnCalc.a
```