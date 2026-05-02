cmake_minimum_required(VERSION 3.16)

project(ImageViewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(image_viewer ${SOURCES})

target_include_directories(image_viewer PRIVATE src)

target_link_libraries(image_viewer
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
)
