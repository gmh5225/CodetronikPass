# LLVM Obfuscation Pass for ARM64


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

### Xcode's Clang option
Project Setting -> Apple Clang -> Custom Compiler Flags -> Other C Flags -> Release  
> -fno-legacy-pass-manager -fpass-plugin=/libCodetronikPass.dylib -DCMAKE_OSX_ARCHITECTURES=arm64

## Build for Android (on Windows)

### Compile LLVM
[How to compile LLVM Pass for Android using Visual Studio](https://github.com/codetronik/CodetronikPass/blob/main/doc/CompileLLVM.md)


### Compile Pass Plugin
```sh
$ git clone https://github.com/codetronik/CodetronikPass
$ notepad.exe CodetronikPass\windows\Directory.build.props
```
Modify ```LLVMINstallDir``` then open ```CodetronikPass.sln``` and build.

### Visual Studio's Clang option
Project Setting -> Configuration Properties -> C/C++ -> Command Line -> Additional Options
> -fpass-plugin=/libCodetronikPass.so

## Issues
Be sure to optimize using the -Ox option. Otherwise, pass cannot be applied.

## Test Environment
- C++, Objective C++ / iPhone 12 mini / Xcode 14.3.1
- C++ / Visual Studio 2022
