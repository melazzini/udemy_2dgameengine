set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED) 

find_package(SDL2_image REQUIRED)

find_package(SDL2_ttf REQUIRED)

find_package(fmt REQUIRED)

find_package(Lua53 REQUIRED)

add_library(
            game Game.cpp Entity.cpp EntityManager.cpp AssetManager.cpp TextureManager.cpp Map.cpp Collision.cpp ./Components/ColliderComponent.hpp ./Components/TransformComponent.hpp 
            ./Components/SpriteComponent.hpp ./Components/TextLabelComponent.hpp 
            Animation.cpp ./Components/KeyboardControlComponent.hpp ./Components/TileComponent.hpp FontManager.cpp) 

set_target_properties(game PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIRS})
    
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} fmt::fmt ${LUA53_LIBRARIES})
