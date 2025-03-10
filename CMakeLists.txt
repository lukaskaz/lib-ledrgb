cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
project(ledrgb)

include(cmake/flags.cmake)
include(cmake/dependencies.cmake)

option(USE_RPI4 "Use rpi4 hardware" OFF)
option(USE_RPI5 "Use rpi5 hardware" OFF)
option(RUN_TESTS "Creates and runs unit tests for the project" OFF)

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(examples)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} libws2811)
target_link_libraries(${PROJECT_NAME} ws2811)
