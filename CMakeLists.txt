cmake_minimum_required(VERSION 3.10)
project(TheConjuringTrap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(TheConjuringTrap ${SOURCES})

target_link_libraries(TheConjuringTrap SDL2::SDL2 SDL2_image SDL2_mixer)
