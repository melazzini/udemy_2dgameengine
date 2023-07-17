#include "Game.hpp"
#include "Constants.hpp"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>

Game::Game()
{
    this->isRunning = true;
}

Game::~Game()
{
}

bool Game::IsRunning() const
{
    return this->isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(100.0f, 100.0f);

void Game::Initialize(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGH,
                              SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    isRunning = true;
    ticksSinceLastFrame = SDL_GetTicks();
    return;
}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT: {
        isRunning = false;
        break;
    }
    case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            isRunning = false;
            break;
        }
    }
    default:
        break;
    }
}

void Game::Update()
{
    auto ticks = SDL_GetTicks();
    auto deltaTime_ms = (ticks - ticksSinceLastFrame);
    ticksSinceLastFrame = ticks;

    if (deltaTime_ms < MIN_DELTA_TIME)
    {
        SDL_Delay(MIN_DELTA_TIME - deltaTime_ms);
    }
    deltaTime_ms = MIN_DELTA_TIME;
    projectilePos = glm::vec2(projectilePos.x + projectileVel.x * deltaTime_ms / 1000,
                              projectilePos.y + projectileVel.y * deltaTime_ms / 1000);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile{(int)projectilePos.x, (int)projectilePos.y, 100, 100};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
