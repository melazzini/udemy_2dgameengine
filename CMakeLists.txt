cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(2d-game-engine VERSION 1.0 LANGUAGES CXX)

add_executable(app main.cpp)

find_package(glm REQUIRED)

add_subdirectory(src)

target_include_directories(app PRIVATE  "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(app PRIVATE glm::glm game)
