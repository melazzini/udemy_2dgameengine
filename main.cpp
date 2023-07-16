#include "Constants.hpp"
#include "Game.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    Game *game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGH);

    while (game->IsRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();
}
