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
cmake ../Perfume
```

Notes:
======

 - boost build example `b2 toolset="msvc" --build-type=complete stage`
 - for example `b2 toolset="msvc-12.0" --build-type=complete --without-context --without-coroutine stage` should just work on windows
 - It's possible to run QtQuick application from Visual Studio, to do it you must add path to Qt5 bin (where dlls located) to it's environment.
 - for 64 build use something alike: `cmake ../Perfume -G"Visual Studio 11 Win64"`
 - I have no idea currently how to friend modular boost (git version) with CMake but randomly I used to get it

TODO
====

 - ...

Server
======

<img align="left" src="http://cdn.flaticon.com/png/256/30983.png">

``` cpp
LOG4CPLUS_INFO(logger_, "Running server class");
managed_shared_memory segment
   (create_only, "Patchouli", 65536);

managed_shared_memory::size_type free_memory = 
                         segment.get_free_memory();

void * shptr = segment.allocate(1024);
segment.construct<sharedString>( "sharedString" )
        (app_name, segment.get_segment_manager());

boost::thread thread(&server::worker, this);
```

Client
======

<img align="right" src="http://cdn.flaticon.com/png/256/33804.png">

``` cpp
root->connect(trayIcon, &QSystemTrayIcon::activated,
  [root] (QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
      ((QQuickWindow *)root)->showNormal();
      break;
    }
});
managed_shared_memory segment(open_only, "Patchouli");
std::pair<sharedString * , size_t > p
  = segment.find<sharedString>("sharedString");
((QQuickWindow *)root)->setTitle( p.first->c_str() );
```
 
Credits
=======

 - based on https://github.com/snikulov/boost.app.cmake
