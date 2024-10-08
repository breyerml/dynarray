cmake_minimum_required(VERSION 3.30)
project(dynarray
        VERSION 1.1.0
        DESCRIPTION "Implementation of a runtime fixed-size array."
        LANGUAGES CXX)

add_executable(dynarray examples.cpp dynarray.hpp)

# set the latest CXX standard if it is newer than C++11
set(CPP_UTIL_UNSUPPORTED_CXX_STANDARDS 98)
list(FIND CPP_UTIL_UNSUPPORTED_CXX_STANDARDS ${CMAKE_CXX_STANDARD_LATEST} CPP_UTIL_UNSUPPORTED_CXX_STANDARDS_INDEX)
if(CPP_UTIL_UNSUPPORTED_CXX_STANDARDS_INDEX EQUAL -1)
    message(STATUS "Setting C++ standard to ${CMAKE_CXX_STANDARD_LATEST}.")
    set_property(TARGET dynarray PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD_LATEST})
else()
    message(FATAL_ERROR "At least C++11 must be supported by the used compiler, but the latest supported standard is ${CMAKE_CXX_STANDARD_LATEST}!")
endif()

# enable testing
option(CPP_UTIL_ENABLE_TESTS "Enable testing using Catch2" OFF)
if (CPP_UTIL_ENABLE_TESTS)
    message(STATUS "Enabled testing using Catch2.")
    enable_testing()
    add_subdirectory(tests)
endif ()