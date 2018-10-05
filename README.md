Qt5 QtQuick Boost Interprocess CMAKE Application Template
---------------------------------------------------------

 - Boost Application runs as Service on Windows, as Daemon on Linux, can self install / uninstall / run from console
 - Plugin system support via Boost.DLL
 - Modern CMAKE system for crossIDE building
 - log4cpp as modern logging system for C++
 - Qt5 QtQuick Application with Tray icon as GUI part
 - Boost interprocess for sharing memory between them

How to build:
-------------

``` shell
git submodule update --init --recursive
cd build
cmake ..
make
```

Notes:
======

 - boost build example `b2 toolset="msvc" --build-type=complete stage`
 - for example `b2 toolset="msvc-12.0" --build-type=complete --without-context --without-coroutine stage` should just work on windows
 - It's possible to run QtQuick application from Visual Studio, to do it you must add path to Qt5 bin (where dlls located) to it's environment.
 - for 64 build use something alike: `cmake ../Perfume -G"Visual Studio 11 Win64"`
 - I have no idea currently how to friend modular boost (git version) with CMake but randomly I used to get it
