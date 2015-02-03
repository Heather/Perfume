Qt5 QtQuick Boost CMAKE Application template
--------------------------------------------

``` shell
cmake ../Perfume
```

Notes:
======

 - It's possible to run QtQuick application from Visual Studio, to do it you must add path to Qt5 bin (where dlls located) to it's environment.
 - for 64 build use something alike: `cmake ../Perfume -G"Visual Studio 11 Win64"`

Credits
=======

 - based on https://github.com/snikulov/boost.app.cmake
