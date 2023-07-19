#pragma once
#include "../Component.hpp"
#include "../Game.hpp"
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <cmath>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class TransformComponent : public Component
{
  public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;
    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
    {
        position = glm::vec2(posX, posY);
        velocity = glm::vec2(velX, velY);
        width = w;
        height = h;
        scale = s;
    }
    void Initialize() override
    {
    }

    void Update(float deltaTime) override
    {
        position.x += velocity.x * deltaTime / 1000;
        position.y += velocity.y * deltaTime / 1000;
    }

    void Render() override
    {
        SDL_Rect transformRectange = {(int)position.x, (int)position.y, width, height};
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(Game::renderer, &transformRectange);
    }
};
