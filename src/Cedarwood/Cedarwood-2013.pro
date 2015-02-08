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

INCLUDEPATH += $$PWD/../../../boost
DEPENDPATH += $$PWD/../../../boost

INCLUDEPATH += $$PWD/../../../boost/libs/asio/include
INCLUDEPATH += $$PWD/../../../boost/libs/interprocess/include
INCLUDEPATH += $$PWD/../../../boost/libs/lambda/include
INCLUDEPATH += $$PWD/../../../boost/libs/thread/include
INCLUDEPATH += $$PWD/../../../boost/libs/uuid/include
INCLUDEPATH += $$PWD/../../../boost/libs/program_options/include

unix:!macx|win32: LIBS += -L$$PWD/../../../boost/stage/lib/ -lboost_filesystem-vc120-mt-1_58
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../boost/stage/lib/boost_filesystem-vc120-mt-1_58.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../boost/stage/lib/libboost_filesystem-vc120-mt-1_58.a

unix:!macx|win32: LIBS += -L$$PWD/../../../boost/stage/lib/ -llibboost_date_time-vc120-mt-1_58
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../boost/stage/lib/libboost_date_time-vc120-mt-1_58.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../boost/stage/lib/liblibboost_date_time-vc120-mt-1_58.a
