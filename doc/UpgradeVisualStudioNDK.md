## How to apply the latest NDK to Visual Studio

If you are currently using Visual Studio 2022 Version 17.7.2, your ndk version is r23c.<br>
You can upgrade this to the latest LTS version (r25c) or the latest beta version. (r26 RC1)

Download [r25c](https://dl.google.com/android/repository/android-ndk-r25c-windows.zip) / [r26-rc1](https://dl.google.com/android/repository/android-ndk-r26-rc1-windows.zip)

## Apply to r25c
1. cd ```C:/Microsoft/AndroidNDK```
2. rename the directory on ```android-ndk-r23c``` to ```android-ndk-r23c_org```
3. download & extract ```android-ndk-r25c-windows.zip``` and rename the directory ```android-ndk-r25c``` to ```android-ndk-r23c```


## Apply to r26-rc1
1. cd ```C:/Microsoft/AndroidNDK```
2. rename the directory on ```android-ndk-r23c``` to ```android-ndk-r23c_org```
3. download & extract ```android-ndk-r26-rc1-windows.zip``` and ```android-ndk-r25c-windows.zip``` and rename the directory ```android-ndk-r26-beta2``` to ```android-ndk-r23c```
4. patch 
```sh
$ xcopy /E /I C:\Microsoft\AndroidNDK\android-ndk-r23c\toolchains\llvm\prebuilt\windows-x86_64\lib C:\Microsoft\AndroidNDK\android-ndk-r23c\toolchains\llvm\prebuilt\windows-x86_64\lib64
$ xcopy /E /I C:\Microsoft\AndroidNDK\android-ndk-r25c\sources\cxx-stl\llvm-libc++ C:\Microsoft\AndroidNDK\android-ndk-r23c\sources\cxx-stl\llvm-libc++
$ xcopy /E /I C:\Microsoft\AndroidNDK\android-ndk-r25c\sources\cxx-stl\llvm-libc++abi C:\Microsoft\AndroidNDK\android-ndk-r23c\sources\cxx-stl\llvm-libc++abi
```
