add_library(game Game.cpp Entity.cpp EntityManager.cpp ./Components/TransformComponent.hpp)
target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(game ${SDL2_LIBRARIES})
