cmake_minimum_required(VERSION 3.1)

project(SFMLEngine)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
#set(SFML_DIR "~/SFML/install")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(SFMLEngine src/main.cpp)
target_link_libraries(SFMLEngine sfml-graphics sfml-audio)
