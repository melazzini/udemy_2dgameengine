add_library(game Game.cpp)
target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(game ${SDL2_LIBRARIES})
