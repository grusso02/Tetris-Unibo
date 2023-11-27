cmake_minimum_required(VERSION 3.26)
project(Tetris_Unibo)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp src/* lib/*)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})