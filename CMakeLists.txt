cmake_minimum_required(VERSION 3.14)
project(TheConjuringTrap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- OPTIONS DE COMPILATION ---
option(BUILD_GAME "Build the main game executable" ON)
option(BUILD_TESTS "Build the unit tests" ON)

# --- DEPENDANCES COMMUNES ---
find_package(SDL2 REQUIRED)
include_directories(src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# On récupère toutes les sources SAUF le main.cpp
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
list(REMOVE_ITEM GAME_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")


# ==========================================
# CIBLE 1 : LE JEU PRINCIPAL
# ==========================================
if(BUILD_GAME)
    message(STATUS "Building Main Game (TheConjuringTrap)")
    add_executable(TheConjuringTrap ${GAME_SOURCES} src/main.cpp)
    target_link_libraries(TheConjuringTrap SDL2::SDL2 SDL2_image SDL2_mixer)
endif()


# ==========================================
# CIBLE 2 : LES TESTS UNITAIRES
# ==========================================
if(BUILD_TESTS)
    message(STATUS "Building Unit Tests (UnitTests)")
    enable_testing()

    # Téléchargement automatique de Google Test
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)

    # On récupère les fichiers de tests dans les sous-dossiers
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

    # L'exécutable des tests
    add_executable(UnitTests ${GAME_SOURCES} ${TEST_SOURCES})
    target_link_libraries(UnitTests gtest_main SDL2::SDL2 SDL2_image SDL2_mixer)

    include(GoogleTest)
    gtest_discover_tests(UnitTests)
endif()
