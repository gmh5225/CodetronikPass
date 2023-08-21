# Codetronik's LLVM Obfuscation Pass

## Build for iOS Application

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

### Edit your Xcode project
Project Setting -> Apple Clang -> Custom Compiler Flags -> Other C Flags -> Release  
```-fno-legacy-pass-manager -fpass-plugin=/YOURPATH/CodetronikPass/Release/libCodetronikPass.dylib -DCMAKE_OSX_ARCHITECTURES=arm64```

## Build for Android Application
