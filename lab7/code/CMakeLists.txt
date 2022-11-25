cmake_minimum_required(VERSION 3.5)

project(libman_system)

set(SOURCES
    src/main.cpp
    src/libman.cpp
    src/avltree.cpp
    )

add_executable(libman_system ${SOURCES})

target_include_directories(libman_system
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)