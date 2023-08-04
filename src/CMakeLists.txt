set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(fmt REQUIRED)

add_library(game Game.cpp Entity.cpp EntityManager.cpp AssetManager.cpp TextureManager.cpp ./Components/TransformComponent.hpp 
    ./Components/SpriteComponent.hpp Animation.cpp ./Components/KeyboardControlComponent.hpp)

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARY} fmt::fmt)
