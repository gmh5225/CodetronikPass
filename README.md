# LLVM Obfuscation Pass for ARM64

It is currently being developed to protect iOS apps. So I haven't tested it on Android yet.

## Features

- [Anti Code Decompile](https://github.com/codetronik/CodetronikPass/blob/main/doc/AntiFunctionDecompile.md)

## Build for iOS  (Build on Mac)

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

## Build for Android (Build on Windows)

### Compile LLVM
1. open the manifest.xml from the path ```/NDKPATH/toolchains/llvm/prebuilt/windows-x86_64/``` and find string ```project path="toolchain/llvm-project"``` and check the revision.
2. install [CMake](https://cmake.org/download/)
3. install Visual Studio 2022 and open "Developer Command Prompt for VS 2022"
4. download and compile Clang.
```
git clone https://android.googlesource.com/toolchain/llvm-project
cd llvm-project
git checkout YOUR_NDK_LLVM_PROJECT_REVISION
cmake -S llvm -B Release -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_NEW_PASS_MANAGER=ON -DLLVM_ENABLE_PROJECTS="clang" -G "NMake Makefiles"
cd Release
nmake
```
## Clang option
### Xcode
Project Setting -> Apple Clang -> Custom Compiler Flags -> Other C Flags -> Release  
> -fno-legacy-pass-manager -fpass-plugin=/YOURPATH/CodetronikPass/Release/libCodetronikPass.dylib -DCMAKE_OSX_ARCHITECTURES=arm64

## Output
- dynamic library

## Issues
Be sure to optimize using the -Ox option. Otherwise, pass cannot be applied.

## Test Environment
- C++ / iPhone 12 mini / Xcode 14.3.1
