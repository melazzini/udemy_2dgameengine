#include "Game.hpp"
#include "AssetManager.hpp"
#include "Components/ColliderComponent.hpp"
#include "Components/KeyboardControlComponent.hpp"
#include "Components/ProjectileEmitterComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TextLabelComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <fmt/core.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

using fmt::format;
EntityManager manager;
SDL_Renderer *Game::renderer = nullptr;
AssetManager *Game::assetManager;
SDL_Event *Game::event{};
SDL_Rect Game::camera{0, 0, WINDOW_WIDTH, WINDOW_HEIGH};
Map *map;
Entity *player = nullptr;

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

    if (TTF_Init() != 0)
    {
        std::cerr << "Error initializing SDL2_TTF" << std::endl;
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
    event = new SDL_Event;
    return;
}
void Game::LoadLevelWithLua(int levelNumber)
{
    /*
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file(
        format("/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/scripts/{}.lua", levelName));
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];
    *
     * LOAD ASSETS WITH LUA
     *
    unsigned int assetIndex = 0;
    while (true)
    {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if (existsAssetIndexNode == sol::nullopt)
        {
            break;
        }
        else
        {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType == "texture")
            {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str());
            }
        }
    }

    *
     * LOAD MAP WITH LUA
     *
    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];

    map = new Map(mapTextureId, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));
    map->LoadMap(mapFile, static_cast<int>(levelMap["mapSizeX"]), static_cast<int>(levelMap["mapSizeY"]));
    */
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/scripts/" + levelName + ".lua");

    /*********************************************/
    /* LOADS ASSETS FROM LUA CONFIG FILE         */
    /*********************************************/
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];

    unsigned int assetIndex = 0;
    while (true)
    {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if (existsAssetIndexNode == sol::nullopt)
        {
            break;
        }
        else
        {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0)
            {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str());
            }
        }
        assetIndex++;
    }

    /*********************************************/
    /* LOADS MAP FROM LUA CONFIG FILE            */
    /*********************************************/
    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];

    map = new Map(mapTextureId, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));

    map->LoadMap(mapFile, static_cast<int>(levelMap["mapSizeX"]), static_cast<int>(levelMap["mapSizeY"]));
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

    assetManager->AddTexture(
        "jungle-tiletexture",
        "/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/tilemaps/jungle.png");

    assetManager->AddFont("charriot-font",
                          "/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/fonts/charriot.ttf",
                          14);

    assetManager->AddTexture(
        "projectile-image",
        "/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/images/bullet-enemy.png");

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("/home/francisco/Projects/gameEngines/SDL_UDEMY/udemy_2dgameengine/assets/tilemaps/jungle.map", 25,
                 20);

    /*
     * start including new entities and also components to them
     */

    Entity &tankEntity(manager.AddEntity("tank", LayerType::ENEMY_LAYER));
    tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    tankEntity.addComponent<SpriteComponent>("tank-image");
    tankEntity.addComponent<ColliderComponent>("enemy", 0, 0, 32, 32);

    Entity &chopperEntity(manager.AddEntity("chopper", LayerType::PLAYER_LAYER));
    chopperEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    chopperEntity.addComponent<KeyboardControlComponent>("up", "down", "right", "left", "space");
    chopperEntity.addComponent<ColliderComponent>("player", 240, 106, 32, 32);
    player = &chopperEntity;

    Entity &radarEntity(manager.AddEntity("radar", LayerType::UI_LAYER));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity &labelLevelName(manager.AddEntity("LabelLevelName", LayerType::UI_LAYER));
    labelLevelName.addComponent<TextLabelComponent>(10, 10, "First Level ... ", "charriot-font", WHITE_COLOR);

    Entity &projectile(manager.AddEntity("projectile", LayerType::PROJECTILE_LAYER));
    projectile.addComponent<TransformComponent>(150 + 16, 495 + 16, 0, 0, 4, 4, 1);
    projectile.addComponent<SpriteComponent>("projectile-image");
    projectile.addComponent<ColliderComponent>("projectile", 150 + 16, 495 + 16, 4, 4);
    projectile.addComponent<ProjectileEmitterComponent>(50,  // speed
                                                        270, // angle
                                                        200, // range, number of px before it destroys itself
                                                        true // shoot in loop
    );

    manager.DisplayAllEntities();
}

void Game::ProcessInput()
{
    SDL_PollEvent(event);
    switch (event->type)
    {
    case SDL_QUIT: {
        isRunning = false;
        break;
    }
    case SDL_KEYDOWN: {
        if (event->key.keysym.sym == SDLK_ESCAPE)
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
    HandleCameraMovement();
    CheckCollisions();
}

void Game::HandleCameraMovement()
{
    auto transform = player->GetComponet<TransformComponent>();
    camera.x = transform->position.x - WINDOW_WIDTH / 2;
    camera.y = transform->position.y - WINDOW_HEIGH / 2;
    camera.x = (camera.x > 0) ? (camera.x < WINDOW_WIDTH ? camera.x : WINDOW_WIDTH) : 0;
    camera.y = (camera.y > 0) ? (camera.y < WINDOW_HEIGH ? camera.y : WINDOW_HEIGH) : 0;
}

void Game::CheckCollisions()
{
    auto collitionTagType = manager.CheckCollisions();
    if (collitionTagType == CollisionType::PLAYER_ENEMY_COLLISION ||
        collitionTagType == CollisionType::PLAYER_PROJECTILE_COLLISTION)
    {
        ProcessGameOver();
    }
    else if (collitionTagType == CollisionType::PLAYER_LEVEL_COMPLETE_COLLISION)
    {
        ProcessNextLevel();
    }
}

void Game::ProcessGameOver()
{
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}

void Game::ProcessNextLevel()
{
    std::cout << "Next Level" << std::endl;
    isRunning = false;
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
