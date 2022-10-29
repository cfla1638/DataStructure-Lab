cmake_minimum_required(VERSION 3.5)

project(huffmancoder)

set(SOURCES
	src/binstream.cpp
	src/huffmancoder.cpp
	src/main.cpp
)

add_executable(huffmancoder ${SOURCES})

target_include_directories(huffmancoder
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)