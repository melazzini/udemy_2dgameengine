#pragma once

#include "../Animation.hpp"
#include "../AssetManager.hpp"
#include "../Component.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>
#include <SDL_timer.h>
#include <fmt/core.h>
#include <iostream>
#include <map>

class SpriteComponent : public Component
{
  private:
    SDL_Texture *texture;
    SDL_Rect sourcerectangle;
    SDL_Rect destinationRectangle;
    TransformComponent *transform;
    bool isAnimated;
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned animationIndex = 0;

  public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char *filePath)
    {
        isAnimated = false;
        isFixed = false;
        SetTexture(filePath);
    }

    SpriteComponent(const char *filePath, int numFrames, int animationSpeed, bool hasDirections, bool isFixed)
    {
        this->isAnimated = true;
        this->animationSpeed = animationSpeed;
        this->numFrames = numFrames;
        this->isFixed = isFixed;

        if (hasDirections)
        {
            Animation downAnimation = Animation(0, numFrames, animationSpeed);
            Animation rightAnimation = Animation(1, numFrames, animationSpeed);
            Animation leftAnimation = Animation(2, numFrames, animationSpeed);
            Animation upAnimation = Animation(3, numFrames, animationSpeed);

            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("UpAnimation", upAnimation);

            this->animationIndex = 0;
            this->currentAnimationName = "DownAnimation";
        }
        else
        {
            Animation singleAnimation = Animation(0, numFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex = 0;
            this->currentAnimationName = "SingleAnimation";
        }

        Play(this->currentAnimationName);
        SetTexture(filePath);
    }

    void Play(std::string animationName)
    {
        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
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
        if (isAnimated)
        {
            sourcerectangle.x = sourcerectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
        }
        sourcerectangle.y = animationIndex * transform->height;
        destinationRectangle.x = (int)transform->position.x - (isFixed ? 0 : Game::camera.x);
        destinationRectangle.y = (int)transform->position.y - (isFixed ? 0 : Game::camera.y);
        destinationRectangle.w = (int)transform->width * transform->scale;
        destinationRectangle.h = (int)transform->height * transform->scale;
    }

    void Render() override
    {
        TextureManager::Draw(texture, sourcerectangle, destinationRectangle, spriteFlip);
    }
};
