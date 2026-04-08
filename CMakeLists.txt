cmake_minimum_required(VERSION 3.14)
project(TheConjuringTrap)

# ----- GLOBAL SETTINGS -----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# ----- OPTIONS -----
option(BUILD_GAME "Build the main game executable" ON)
option(BUILD_TESTS "Build the unit tests" ON)

# ----- DEPENDENCIES -----
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(src)

# ----- SOURCES -----
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
list(REMOVE_ITEM GAME_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

# ----- TARGET: GAME -----
if(BUILD_GAME)
    if(WIN32)
        add_executable(TheConjuringTrap WIN32 ${GAME_SOURCES} src/main.cpp)
        target_link_libraries(TheConjuringTrap mingw32 SDL2::SDL2main SDL2::SDL2 SDL2_image SDL2_mixer)
        target_include_directories(TheConjuringTrap PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
    else()
        add_executable(TheConjuringTrap ${GAME_SOURCES} src/main.cpp)
        target_link_libraries(TheConjuringTrap SDL2::SDL2 SDL2_image SDL2_mixer)
    endif()

    target_link_libraries(TheConjuringTrap SDL2::SDL2 SDL2_image SDL2_mixer)

    add_custom_command(TARGET TheConjuringTrap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:TheConjuringTrap>/assets")
endif()

# ----- TARGET: TESTS -----
if(BUILD_TESTS)
    enable_testing()
    if(POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()

    include(FetchContent)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
    add_executable(UnitTests ${GAME_SOURCES} ${TEST_SOURCES})
    target_link_libraries(UnitTests gtest_main SDL2::SDL2 SDL2_image SDL2_mixer)
	set_target_properties(UnitTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

    include(GoogleTest)
    gtest_discover_tests(UnitTests)
endif()
