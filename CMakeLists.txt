cmake_minimum_required(VERSION 3.20)

project(Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/raylib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gd/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pong/*.cpp"
)

add_executable(Game ${SOURCES})

target_link_libraries(Game PRIVATE raylib)