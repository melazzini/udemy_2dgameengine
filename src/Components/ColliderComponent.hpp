#pragma once
#include "../Component.hpp"
#include "../Entity.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>
#include <string>

class ColliderComponent : public Component
{
  public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent *transform;

    ColliderComponent(std::string colliderTag, int x, int y, int w, int h)
    {
        this->colliderTag = colliderTag;
        this->collider.x = x;
        this->collider.y = y;
        this->collider.w = w;
        this->collider.h = h;
    }

    void Initialize() override
    {
        if (owner->HasComponent<TransformComponent>())
        {
            transform = owner->GetComponet<TransformComponent>();
            sourceRectangle = {0, 0, transform->width, transform->height};
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltatime) override
    {
        collider.x = transform->position.x;
        collider.y = transform->position.y;
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;
    }

    void Render() override
    {
    }
};
