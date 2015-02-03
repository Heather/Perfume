cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME Patchouli)
set(SRC_FILES main.cpp)

project(${PROJECT_NAME} CXX)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost
   COMPONENTS thread system date_time chrono regex
   filesystem atomic program_options unit_test_framework REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL "Boost not found")
endif()
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#Boost.Application setup
set(BOOST_APP_ROOT "../../hdr/application")
get_filename_component(__abs_path ${BOOST_APP_ROOT} ABSOLUTE)
file(TO_CMAKE_PATH ${__abs_path} BOOST_APP_ROOT_PATH)

include_directories(../../hdr)
include_directories(${BOOST_APP_ROOT}/include)
include_directories(${BOOST_APP_ROOT}/example)
if (Boost_VERSION LESS 105600)
    include_directories(../../hdr/type_index/include)
endif()
add_definitions(-DBOOST_APPLICATION_FEATURE_NS_SELECT_BOOST)

include_directories (.)
add_executable( ${PROJECT_NAME} ${SRC_FILES} )
if(MSVC)
    set(EXT_LOG4CPLUS_NAME debug "log4cplusSD" optimized "log4cplusS" CACHE STRING "Log4cplus Libraries")
endif()
target_link_libraries(${PROJECT_NAME} ${EXT_LOG4CPLUS_NAME})
target_link_libraries(${PROJECT_NAME}
        ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY} ${Boost_CHRONO_LIBRARY}
        ${Boost_REGEX_LIBRARY} ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_ATOMIC_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${LIBZMQ_LIBRARIES}
	)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()
