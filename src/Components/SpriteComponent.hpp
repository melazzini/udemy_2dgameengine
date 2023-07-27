#pragma once

#include "../AssetManager.hpp"
#include "../Component.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
  private:
    SDL_Texture *texture;
    SDL_Rect sourcerectangle;
    SDL_Rect destinationRectangle;
    TransformComponent *transform;

  public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char *filePath)
    {
        SetTexture(filePath);
    }
    void SetTexture(std::string textureId)
    {
        texture = Game::assetManager->GetTexture(textureId);
    }

    void Initialize() override
    {
        transform = owner->GetComponet<TransformComponent>();
        sourcerectangle.x = 0;
        sourcerectangle.y = 0;
        sourcerectangle.w = transform->width;
        sourcerectangle.h = transform->height;
    }

    void Update(float deltaTime) override
    {
        destinationRectangle.x = (int)transform->position.x;
        destinationRectangle.y = (int)transform->position.y;
        destinationRectangle.w = (int)transform->width * transform->scale;
        destinationRectangle.h = (int)transform->height * transform->scale;
    }

    void Render() override
    {
        TextureManager::Draw(texture, sourcerectangle, destinationRectangle, spriteFlip);
    }
};
