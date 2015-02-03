cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

#Rplace it with your actual QT prefix path
if (WIN32)
    set (CMAKE_PREFIX_PATH "F:\\Qt\\5.4\\msvc2012_opengl")
endif()

set(PROJECT_NAME Perfume)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

project(${PROJECT_NAME} CXX)

if (NOT DEPS_LOCATION)
    set(DEPS_LOCATION "${CMAKE_BINARY_DIR}/deps")
endif()
add_subdirectory(ext/log4cplus)
include_directories(${DEPS_LOCATION}/include)
link_directories(${DEPS_LOCATION}/lib)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

add_subdirectory (src)
