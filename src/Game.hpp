#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include "../lib/lua/sol.hpp"

class AssetManager;
class Game
{
  private:
    bool isRunning;
    SDL_Window *window;
    uint32_t ticksSinceLastFrame;

  public:
    Game();
    ~Game();
    static SDL_Renderer *renderer;
    static AssetManager *assetManager;
    static SDL_Event *event;
    static SDL_Rect camera;
    void LoadLevel(int levelNumber);
    void LoadLevelWithLua(int levelNumber);
    void HandleCameraMovement();
    void CheckCollisions();
    void ProcessGameOver();
    void ProcessNextLevel();

    bool IsRunning() const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};
