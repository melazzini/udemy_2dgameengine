#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_render.h>
#include <SDL_video.h>

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
    void LoadLevel(int levelNumber);

    bool IsRunning() const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};
