set(PROJECT_NAME Cedarwood)

set(SRC_FILES main.cpp)
set(QML_FILES 
    main.qml
    MainForm.ui.qml
)

source_group("QML" FILES ${QML_FILES})

cmake_policy(SET CMP0020 NEW)

project(${PROJECT_NAME} CXX)

find_package(Qt5Core REQUIRED)
find_package(Qt5Declarative)
find_package(Qt5 COMPONENTS Quick Qml Core Network Declarative)
if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

include_directories (.
    ${QT_INCLUDES}
    ${QT_QTDECLARATIVE_INCLUDE_DIR}
)
add_definitions(${QT_DEFINITIONS})

qt5_add_resources(RESOURCES qml.qrc)

add_executable( ${PROJECT_NAME} WIN32 
    ${SRC_FILES}
    ${QML_FILES}
    ${RESOURCES} 
)

if(MSVC)
    set(EXT_LOG4CPLUS_NAME debug "log4cplusSD" optimized "log4cplusS" CACHE STRING "Log4cplus Libraries")
    set_target_properties(${PROJECT} PROPERTIES
        WIN32_EXECUTABLE YES
        LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()
target_link_libraries(${PROJECT_NAME} ${EXT_LOG4CPLUS_NAME})
target_link_libraries(${PROJECT_NAME}
        ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY} ${Boost_CHRONO_LIBRARY}
        ${Boost_REGEX_LIBRARY} ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_ATOMIC_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${LIBZMQ_LIBRARIES}
	)
target_link_libraries(${PROJECT_NAME} Qt5::WinMain ${QT_LIBRARIES} ${QMLDBG_LIBRARIES})

if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

qt5_use_modules( ${PROJECT_NAME} Quick Qml Core Network Declarative )