# Codetronik's LLVM Obfuscation Pass

## Build for iOS Application

### Edit your Xcode project
- Project Setting -> Apple Clang -> Custom Compiler Flags -> Other C Flags -> Release
```-fno-legacy-pass-manager -fpass-plugin=/codetronik-pass/Release/libCodetronikPass.dylib -DCMAKE_OSX_ARCHITECTURES=arm64```

## Build for Android Application
