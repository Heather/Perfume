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
 - It's possible to run QtQuick application from Visual Studio, to do it you must add path to Qt5 bin (where dlls located) to it's environment.
 - for 64 build use something alike: `cmake ../Perfume -G"Visual Studio 11 Win64"`

TODO
====

 - ...

Server
======

``` cpp
  int operator()() {
    LOG4CPLUS_INFO(logger_, "Running server class");

    //Remove shared memory on construction and destruction
    struct shm_remove
    {
      shm_remove() {  shared_memory_object::remove("Patchouli"); }
      ~shm_remove(){  shared_memory_object::remove("Patchouli"); }
    } remover;

    //Create a managed shared memory segment
    managed_shared_memory segment(create_only, "Patchouli", 65536);

    //Allocate a portion of the segment (raw memory)
    managed_shared_memory::size_type free_memory = segment.get_free_memory();
    void * shptr = segment.allocate(1024/*bytes to allocate*/);

    segment.construct<sharedString>( "sharedString" )(app_name, segment.get_segment_manager());

    // launch a work thread
    boost::thread thread(&server::worker, this);

    ctx_.find<boost::application::wait_for_termination_request>()->wait();
```

Client
======

``` cpp
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/resources/logo.png"));
    trayIcon->show();

    root->connect(trayIcon, &QSystemTrayIcon::activated,
      [root] (QSystemTrayIcon::ActivationReason reason) {
        switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
          ((QQuickWindow *)root)->showNormal();
          break;
        case QSystemTrayIcon::MiddleClick:
          ((QQuickWindow *)root)->hide();
          break;
        default:
          ;
        }
    });

    //Open managed segment
    managed_shared_memory segment(open_only, "Patchouli");

    std::pair<sharedString * , size_t > p= segment.find<sharedString>("sharedString");
    ((QQuickWindow *)root)->setTitle( p.first->c_str() );
```
 
Credits
=======

 - based on https://github.com/snikulov/boost.app.cmake
