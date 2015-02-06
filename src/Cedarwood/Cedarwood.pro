TEMPLATE = app

QT += qml quick widgets
QMAKE_CXXFLAGS += -std=c++11 -Wall -O2

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    stdafx.h

SOURCES += main.cpp

unix:!macx|win32: LIBS += -L$$PWD/../../../../boost/stage/lib/ -llibboost_filesystem-vc110-mt-1_57 -llibboost_date_time-vc110-mt-gd-1_57

INCLUDEPATH += $$PWD/../../../../boost
DEPENDPATH += $$PWD/../../../../boost

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../boost/stage/lib/libboost_filesystem-vc110-mt-1_57.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../boost/stage/lib/liblibboost_filesystem-vc110-mt-1_57.a
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../boost/stage/lib/libboost_date_time-vc110-mt-gd-1_57.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../boost/stage/lib/libboost_date_time-vc110-mt-gd-1_57.a
