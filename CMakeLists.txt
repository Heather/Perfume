cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

#Rplace it with your actual QT prefix path
if (WIN32)
    set (CMAKE_PREFIX_PATH "F:\\Qt\\5.4\\msvc2012_opengl")
    set (BOOST_ROOT "F:\\P\\thridparty\\boost")
endif()

set(PROJECT_NAME Perfume)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

project(${PROJECT_NAME} CXX)

if (NOT DEPS_LOCATION)
    set(DEPS_LOCATION "${CMAKE_BINARY_DIR}/deps")
endif()
include_directories(${DEPS_LOCATION}/include)
link_directories(${DEPS_LOCATION}/lib)
link_directories(${DEPS_LOCATION}/lib64)

#if (WIN32)
#    # ...
#else()
#    find_package(Threads REQUIRED)
#endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

set(Boost_USE_STATIC_LIBS     ON)
set(Boost_USE_MULTITHREADED   ON)
find_package(Boost
   COMPONENTS thread system date_time chrono regex
   filesystem atomic program_options unit_test_framework REQUIRED)
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")
if (NOT Boost_FOUND)
    message(FATAL "Boost not found")
endif()
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#Boost.Application setup
set(BOOST_APP_ROOT "hdr/application")
get_filename_component(__abs_path ${BOOST_APP_ROOT} ABSOLUTE)
file(TO_CMAKE_PATH ${__abs_path} BOOST_APP_ROOT_PATH)

include_directories(hdr)
include_directories(${BOOST_APP_ROOT}/include)
include_directories(${BOOST_APP_ROOT}/example)
if (Boost_VERSION GREATER 105700)
    include_directories(${Boost_INCLUDE_DIR}/libs/asio/include)
    include_directories(${Boost_INCLUDE_DIR}/libs/interprocess/include)
    include_directories(${Boost_INCLUDE_DIR}/libs/lambda/include)
    include_directories(${Boost_INCLUDE_DIR}/libs/thread/include)
    include_directories(${Boost_INCLUDE_DIR}/libs/uuid/include)
    include_directories(${Boost_INCLUDE_DIR}/libs/program_options/include)
endif()
if (Boost_VERSION LESS 105600)
    include_directories(hdr/type_index/include)
endif()
add_definitions(-DBOOST_APPLICATION_FEATURE_NS_SELECT_BOOST)

add_subdirectory(ext/log4cplus)
add_subdirectory (src)
