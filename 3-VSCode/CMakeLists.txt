cmake_minimum_required(VERSION 3.16)

project(AlienAttack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/../2-CodeBlocks/*.cpp"
)

file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/../2-CodeBlocks/*.h"
)

add_executable(AlienAttack ${GAME_SOURCES} ${GAME_HEADERS})

target_include_directories(AlienAttack PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/../2-CodeBlocks"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_link_libraries(AlienAttack PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)

if(MSVC)
    target_compile_definitions(AlienAttack PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
