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
    assetManager->AddTexture(
        "tank-image",
        std::string(
            "/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/images/tank-big-right.png")
            .c_str());
    assetManager->AddTexture(
        "chopper-image",
        std::string(
            "/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/images/chopper-spritesheet.png")
            .c_str());

    assetManager->AddTexture(
        "radar-image",
        std::string("/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/images/radar.png")
            .c_str());

    /*
     * start including new entities and also components to them
     */

    Entity &tankEntity(manager.AddEntity("tank"));
    tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    tankEntity.addComponent<SpriteComponent>("tank-image");

    Entity &chopperEntity(manager.AddEntity("tank"));
    chopperEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);

    Entity &radarEntity(manager.AddEntity("radar"));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);

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
