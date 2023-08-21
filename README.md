# Codetronik's LLVM Obfuscation Pass

## Build for iOS Application

### Compile LLVM
```sh
$ git clone -b swift-5.8.1-RELEASE --depth 1 --single-branch https://github.com/llvm/llvm-project.git
$ cd llvm-project
$ cmake -S llvm -B Release -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_NEW_PASS_MANAGER=ON -DLLVM_ENABLE_PROJECTS="clang" 
$ cd Release
$ make -j16
```

### Compile Pass Plugin
```sh
$ cmake -B Release -DLLVM_DIR=/llvm-project/Release/lib/cmake -DCMAKE_OSX_ARCHITECTURES=arm64
$ cd Release
$ make -j16
```

### Edit your Xcode project
Project Setting -> Apple Clang -> Custom Compiler Flags -> Other C Flags -> Release  
```-fno-legacy-pass-manager -fpass-plugin=/codetronik-pass/Release/libCodetronikPass.dylib -DCMAKE_OSX_ARCHITECTURES=arm64```


## Build for Android Application
