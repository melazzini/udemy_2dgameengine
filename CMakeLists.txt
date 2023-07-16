cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(2d-game-engine VERSION 1.0 LANGUAGES CXX)

add_executable(app main.cpp)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(src)

target_include_directories(app PRIVATE "${SDL2_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(app PRIVATE "${SDL2_LIBRARIES}" glm::glm game)
