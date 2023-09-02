# LLVM Obfuscation Pass for ARM64

It is currently being developed to protect iOS apps. So I haven't tested it on Android yet.

## Features

- [Anti Code Decompile](https://github.com/codetronik/CodetronikPass/blob/main/doc/AntiFunctionDecompile.md)

## Build for iOS  (on Mac)

### Compile LLVM
Download the same version as clang of your Xcode. Check your version [here](https://en.wikipedia.org/wiki/Xcode)<br>
Xcode 14.3.1 uses clang-1403.0.22.14.1 and is included in swift-5.8.1 branch.

```sh
$ git clone -b swift-5.8.1-RELEASE --depth 1 --single-branch https://github.com/llvm/llvm-project.git
$ cd llvm-project
$ cmake -S llvm -B Release -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_NEW_PASS_MANAGER=ON -DLLVM_ENABLE_PROJECTS="clang" 
$ cd Release
$ make -j16
```

### Compile Pass Plugin
```sh
$ git clone https://github.com/codetronik/CodetronikPass
$ cd CodetronikPass
$ cmake -B Release -DLLVM_DIR=/YOURPATH/llvm-project/Release/lib/cmake -DCMAKE_OSX_ARCHITECTURES=arm64
$ cd Release
$ make -j16
```

## Build for Android (on Windows)

### Compile LLVM
[How to compile LLVM Pass for Android using Visual Studio](https://github.com/codetronik/CodetronikPass/blob/main/doc/CompileLLVM.md)

5. patch the ndk
```sh
$ xcopy /E NDKPATH\toolchains\llvm\prebuilt\windows-x86_64\lib64 NDKPATH\toolchains\llvm\prebuilt\windows-x86_64\lib
$ copy bin\clang.exe NDKPATH\toolchains\llvm\prebuilt\windows-x86_64\bin
```

### Compile Pass Plugin
- using Clang

- using VC
```sh
$ git clone https://github.com/codetronik/CodetronikPass
$ cd CodetronikPass
$ cmake -B project -DLLVM_DIR=d:\custom-llvm\lib\cmake
$ project\CodetronikPass.sln
```
Change the project settings to Release x64 and build.

## Clang option

### Visual Studio

### Xcode
Project Setting -> Apple Clang -> Custom Compiler Flags -> Other C Flags -> Release  
> -fno-legacy-pass-manager -fpass-plugin=/YOURPATH/CodetronikPass/Release/libCodetronikPass.dylib -DCMAKE_OSX_ARCHITECTURES=arm64

## Output
- dynamic library

## Issues
Be sure to optimize using the -Ox option. Otherwise, pass cannot be applied.

## Test Environment
- C++, Objective C++ / iPhone 12 mini / Xcode 14.3.1
