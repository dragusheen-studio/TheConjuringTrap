set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(DEPS_PATH "${CMAKE_SOURCE_DIR}/deps_windows")

set(SDL2_ROOT "${DEPS_PATH}/SDL2-2.30.2/x86_64-w64-mingw32")
set(SDL2_IMAGE_ROOT "${DEPS_PATH}/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_MIXER_ROOT "${DEPS_PATH}/SDL2_mixer-2.8.0/x86_64-w64-mingw32")

set(CMAKE_PREFIX_PATH 
    "${SDL2_ROOT}"
    "${SDL2_IMAGE_ROOT}"
    "${SDL2_MIXER_ROOT}"
)

include_directories(
    "${SDL2_ROOT}/include"
    "${SDL2_IMAGE_ROOT}/include"
    "${SDL2_MIXER_ROOT}/include"
)

link_directories(
    "${SDL2_ROOT}/lib"
    "${SDL2_IMAGE_ROOT}/lib"
    "${SDL2_MIXER_ROOT}/lib"
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
