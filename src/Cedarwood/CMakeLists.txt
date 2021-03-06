if (CMAKE_VERSION VERSION_LESS 2.8.3)
  message(FATAL_ERROR "Qt 5 requires at least CMake version 2.8.3")
endif()

set(project_policies
  CMP0028
  CMP0043
  CMP0071
  )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

set(PROJECT_NAME Cedarwood)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

SET(HEADERS
  stdafx.h
  qmain.h
)
set(SRC_FILES
  main.cpp
  qmain.cpp
)
set(QML_FILES
  main.qml
  MainForm.ui.qml
  Button.qml
  CheckBox.qml
  StockChart.qml
  StockInfo.qml
  StockListModel.qml
  StockListView.qml
  StockModel.qml
  StockSettingsPanel.qml
  StockView.qml
  ObjectModel.qml
)
set(RES_FILES
  resources/logo.png
  resources/logo.ico
  resources/left.png
)

set(ICO
  resources/ico.rc
)

source_group("QML" FILES ${QML_FILES})

cmake_policy(SET CMP0020 NEW)

project(${PROJECT_NAME} CXX)

find_package(Qt5 COMPONENTS Quick Qml Core Network Widgets REQUIRED)
find_package(Qt5QuickCompiler)
message("--   Qt5_FOUND: ${Qt5_FOUND}")
message("--   Qt5Quick_FOUND: ${Qt5Quick_FOUND}")
if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

include_directories (.
  ${QT_INCLUDES}
  ${QT_QTDECLARATIVE_INCLUDE_DIR}
)
add_definitions(${QT_DEFINITIONS})

#qt5_add_resources(RESOURCES qml.qrc)
qtquick_compiler_add_resources(RESOURCES qml.qrc)

add_executable( ${PROJECT_NAME} WIN32
  ${SRC_FILES}
  ${HEADERS}
  ${QML_FILES}
  ${RESOURCES}
  ${ICO}
)

if(MSVC)
  set_target_properties(${PROJECT} PROPERTIES
    WIN32_EXECUTABLE YES
    LINK_FLAGS "/ENTRY:mainCRTStartup"
  )
endif()

if(UNIX)
  target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${QMLDBG_LIBRARIES} pthread rt)
else()
  target_link_libraries(${PROJECT_NAME} Qt5::WinMain ${QT_LIBRARIES} ${QMLDBG_LIBRARIES})
endif()

qt5_use_modules( ${PROJECT_NAME} Quick Qml Core Network Widgets )
