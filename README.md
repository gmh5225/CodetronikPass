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

## Build for Android (on Linux)
Downloading a prebuilt clang from AOSP makes it easy to compile a pass without having to compile llvm.

### Download AOSP Clang
1. Open ```/NDKPATH/toolchains/llvm/prebuilt/linux-x86_64/AndroidVersion.txt``` and check your Clang revision ```rXXXXXXXX```
2. Open the URL ```https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86/+refs``` then find and click the link ```ndk-rXX-release```
3. find and click your revision. then download and unzip tgz
```sh
// This is an example of using ndk-r25c.
$ wget https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86/+archive/refs/heads/ndk-r25-release/clang-r450784d1.tar.gz
$ tar xvzf clang-r450784d1.tar.gz -C clang_aosp
```

### Fix AOSP Clang's cmake
Open ```/YOUR_CLANG_AOSP_PATH/lib64/cmake/LLVMExports.cmake``` then Find the code below and delete it. 
```
# Loop over all imported files and verify that they actually exist
foreach(target ${_IMPORT_CHECK_TARGETS} )
  foreach(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    if(NOT EXISTS "${file}" )
      message(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
  endforeach()
  unset(_IMPORT_CHECK_FILES_FOR_${target})
endforeach()
unset(_IMPORT_CHECK_TARGETS)
```

### Compile Pass Plugin
```sh
$ git clone https://github.com/codetronik/CodetronikPass
$ cd CodetronikPass
$ cmake -B Release -DLLVM_DIR=/YOUR_CLANG_AOSP_PATH/lib64/cmake -DCOMPILER=/YOUR_CLANG_AOSP_PATH/bin/clang
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
