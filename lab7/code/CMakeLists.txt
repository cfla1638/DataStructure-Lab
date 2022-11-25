cmake_minimum_required(VERSION 3.5)

project(library_system)

set(SOURCES
    src/main.cpp
    )

add_executable(library_system ${SOURCES})

target_include_directories(library_system
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)