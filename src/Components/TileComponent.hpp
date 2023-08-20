#pragma once
#include "../AssetManager.hpp"
#include "../Component.hpp"
#include "../Game.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

class TileComponent : public Component
{
  public:
    SDL_Texture *texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    glm::vec2 position;

    TileComponent(int sourceRectangleX, int sourceRectangleY, int x, int y, int tileSize, int tileScale,
                  std::string assetTextureId)
    {
        texture = Game::assetManager->GetTexture(assetTextureId);
        this->sourceRectangle.x = sourceRectangleX;
        this->sourceRectangle.y = sourceRectangleY;
        this->sourceRectangle.w = tileSize;
        this->sourceRectangle.h = tileSize;
        this->destinationRectangle.x = x;
        this->destinationRectangle.y = y;
        this->destinationRectangle.w = tileSize * tileScale;
        this->destinationRectangle.h = tileSize * tileScale;
        this->position.x = x;
        this->position.y = y;
    }

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void Update(float deltatime) override
    {
        destinationRectangle.x = position.x - Game::camera.x;
        destinationRectangle.y = position.y - Game::camera.y;
    }

    void Render() override
    {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
    }
};
