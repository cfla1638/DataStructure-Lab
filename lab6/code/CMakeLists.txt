cmake_minimum_required(VERSION 3.5)

project(graph)

set(SOURCES
    src/main.cpp
    src/graph.cpp)

add_executable(graph ${SOURCES})

target_include_directories(graph
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)