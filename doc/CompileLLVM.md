## How to compile LLVM Pass for Android in Visual Studio

1. Install Visual Studio 2022 including [NDK](https://learn.microsoft.com/en-us/cpp/cross-platform/install-visual-cpp-for-cross-platform-mobile-development?view=msvc-170) and [Clang](https://learn.microsoft.com/en-us/cpp/build/clang-support-msbuild?view=msvc-170)
2. [Upgrade NDK](https://github.com/codetronik/CodetronikPass/blob/main/doc/UpgradeVisualStudioNDK.md) to r26-rc1 with Clang 17.0.2<br>
The reason is that Visual Studio sdk does not support Clang 16 or lower versions.
3. change your system locale to English. (other than English, errors may occur during compilation.) 
4. You must build it twice, one for 32-bit and one for 64-bit.<br>
   open ```x86 Native Tools Command Prompt for VS 2022``` // for x86 llvm<br>
   open ```x64 Native Tools Command Prompt for VS 2022``` // for x64 llvm
5. open ```C:\Microsoft\AndroidNDK\android-ndk-r23c\toolchains\llvm/prebuilt\windows-x86_64\manifest_8481493.xml``` and find string ```project path="toolchain/llvm-project"``` and check the revision.
6. download and compile llvm. Make sure to fix ```DLLVM_VERSION_PATCH``` to your ndk's Clang version.
```
$ cd f:\
$ git clone https://android.googlesource.com/toolchain/llvm-project
$ cd llvm-project
$ git checkout d9f89f4d16663d5012e5c09495f3b30ece3d2362
$ cmake -S llvm -B Release[BITS] -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_NEW_PASS_MANAGER=ON -DLLVM_ENABLE_PROJECTS="clang;lld" -DLLVM_VERSION_PATCH=2 -G "NMake Makefiles"
$ cd Release
$ nmake
```
7. install llvm
xcopy /E f:\llvm-project\Release\bin d:\custom-llvm\bin\
xcopy /E f:\llvm-project\Release\include d:\custom-llvm\lib\clang\17\include\
xcopy /E /Y f:\llvm-project\llvm\include d:\custom-llvm\lib\clang\17\include\
xcopy /E f:\llvm-project\Release\lib d:\custom-llvm\lib\

### Make the project
