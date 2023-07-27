#include "Game.hpp"
#include "AssetManager.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
EntityManager manager;
SDL_Renderer *Game::renderer = nullptr;
AssetManager *Game::assetManager;
Game::Game()
{
    this->isRunning = true;
    assetManager = new AssetManager(&manager);
}

Game::~Game()
{
}

bool Game::IsRunning() const
{
    return this->isRunning;
}

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

    Game::renderer = SDL_CreateRenderer(window, -1, 0);
    if (!Game::renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
    LoadLevel(0);

    isRunning = true;
    ticksSinceLastFrame = SDL_GetTicks();
    return;
}
void Game::LoadLevel(int levelNumber)
{
    /*
     * start including new assets to the assetsmanager list
     */
    std::string textureFilePath =
        "/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());

    /*
     * start including new entities and also components to them
     */

    Entity &newEntity(manager.AddEntity("tank"));
    newEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    newEntity.addComponent<SpriteComponent>("tank-image");

    manager.DisplayAllEntities();
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
    manager.Update(deltaTime_ms);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(Game::renderer, 21, 21, 21, 255);
    SDL_RenderClear(Game::renderer);

    if (manager.HasNoEntities())
    {
        return;
    }
    manager.Render();

    SDL_RenderPresent(Game::renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
