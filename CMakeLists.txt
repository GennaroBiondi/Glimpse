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

# ── Install targets ────────────────────────────────────────────────────────────

add_custom_target(glimpse-install
    COMMAND cp ${CMAKE_BINARY_DIR}/image_viewer $ENV{HOME}/.local/bin/glimpse
    DEPENDS image_viewer
    COMMENT "Installing glimpse to ~/.local/bin"
)

add_custom_target(glimpse-install-release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMAND cp ${CMAKE_BINARY_DIR}/image_viewer $ENV{HOME}/.local/bin/glimpse
    COMMENT "Installing optimized glimpse to ~/.local/bin"
)

add_custom_target(glimpse-install-system
    COMMAND sudo cp ${CMAKE_BINARY_DIR}/image_viewer /usr/local/bin/glimpse
    DEPENDS image_viewer
    COMMENT "Installing glimpse to /usr/local/bin"
)

add_custom_target(glimpse-install-system-release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMAND sudo cp ${CMAKE_BINARY_DIR}/image_viewer /usr/local/bin/glimpse
    COMMENT "Installing optimized glimpse to /usr/local/bin"
)
