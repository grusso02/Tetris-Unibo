cmake_minimum_required(VERSION 3.0)
project(Tetris_Unibo)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp
                    src/example.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})