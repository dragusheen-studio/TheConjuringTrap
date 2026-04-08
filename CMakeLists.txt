cmake_minimum_required(VERSION 3.14)
project(TheConjuringTrap)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- OPTIONS DE COMPILATION ---
option(BUILD_GAME "Build the main game executable" ON)
option(BUILD_TESTS "Build the unit tests" ON)

# --- DEPENDANCES COMMUNES ---
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(src)

# --- GESTION DES SOURCES ---
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
list(REMOVE_ITEM GAME_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

# ==========================================
# CIBLE 1 : LE JEU PRINCIPAL
# ==========================================
if(BUILD_GAME)
    message(STATUS "Building Main Game (TheConjuringTrap)")
    
    # WIN32 évite d'ouvrir une console CMD en arrière-plan sur Windows
    if(WIN32)
        add_executable(TheConjuringTrap WIN32 ${GAME_SOURCES} src/main.cpp)
    else()
        add_executable(TheConjuringTrap ${GAME_SOURCES} src/main.cpp)
    endif()

    target_link_libraries(TheConjuringTrap SDL2::SDL2 SDL2_image SDL2_mixer)

    # --- ETAPE DE PROD : COPIE DES ASSETS ---
    # On copie le dossier assets là où le .exe (ou binaire Linux) est généré
    add_custom_command(TARGET TheConjuringTrap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:TheConjuringTrap>/assets"
        COMMENT "Synchronisation du dossier assets pour la distribution...")
endif()

# ==========================================
# CIBLE 2 : LES TESTS UNITAIRES
# ==========================================
if(BUILD_TESTS)
    message(STATUS "Building Unit Tests (UnitTests)")
    enable_testing()

    # Correction du warning CMP0135
    if(POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()

    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # On empêche GTest d'installer des fichiers partout dans ton système
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

    add_executable(UnitTests ${GAME_SOURCES} ${TEST_SOURCES})
    target_link_libraries(UnitTests gtest_main SDL2::SDL2 SDL2_image SDL2_mixer)

    # Force l'exécutable des tests à aller dans le dossier build/UnitTests pour plus de clarté
    set_target_properties(UnitTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

    include(GoogleTest)
    gtest_discover_tests(UnitTests)
endif()
