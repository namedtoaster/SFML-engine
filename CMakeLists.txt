cmake_minimum_required(VERSION 3.1)
project(SFMLEngine)

## Use C++11
set (CMAKE_CXX_STANDARD 11)

## In most cases better set in the CMake cache
set(SFML_DIR "./SFML/build")

## Find SFML
find_package(SFML 2.5 COMPONENTS audio graphics REQUIRED)

## Add includes
include_directories(include)

## Add source files
file(GLOB SOURCES "src/*.cpp")
add_executable(SFMLEngine ${SOURCES})

## Link the program to SFML
target_link_libraries(SFMLEngine sfml-graphics sfml-audio)
