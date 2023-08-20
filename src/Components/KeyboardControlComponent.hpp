#pragma once

#include "../EntityManager.hpp"
#include "../Game.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include <SDL_events.h>
#include <string>

class KeyboardControlComponent : public Component
{
  public:
    std::string upKey;
    std::string downKey;
    std::string rightKey;
    std::string leftKey;
    std::string shootKey;
    TransformComponent *transform;
    SpriteComponent *sprite;

    KeyboardControlComponent()
    {
    }

    KeyboardControlComponent(std::string upKey, std::string downKey, std::string rightKey, std::string leftKey,
                             std::string shootKey)
    {
        this->upKey = GetSDLKeyStringCode(upKey);
        this->downKey = GetSDLKeyStringCode(downKey);
        this->rightKey = GetSDLKeyStringCode(rightKey);
        this->leftKey = GetSDLKeyStringCode(leftKey);
        this->shootKey = GetSDLKeyStringCode(shootKey);
    }

    std::string GetSDLKeyStringCode(std::string key)
    {
        if (key.compare("up") == 0)
            return "1073741906";
        if (key.compare("down") == 0)
            return "1073741905";
        if (key.compare("left") == 0)
            return "1073741904";
        if (key.compare("right") == 0)
            return "1073741903";
        if (key.compare("space") == 0)
            return "32";
        return std::to_string(static_cast<int>(key[0]));
    }

    void Initialize() override
    {
        transform = owner->GetComponet<TransformComponent>();
        sprite = owner->GetComponet<SpriteComponent>();
    }

    void Update(float deltatime) override
    {
        if (Game::event->type == SDL_KEYDOWN)
        {
            std::string keycode = std::to_string(Game::event->key.keysym.sym);
            if (keycode.compare(upKey) == 0)
            {
                transform->velocity.y = -50;
                transform->velocity.x = 0;
                sprite->Play("UpAnimation");
            }
            if (keycode.compare(rightKey) == 0)
            {
                transform->velocity.y = 0;
                transform->velocity.x = 50;
                sprite->Play("RightAnimation");
            }
            if (keycode.compare(leftKey) == 0)
            {
                transform->velocity.y = 0;
                transform->velocity.x = -50;
                sprite->Play("LeftAnimation");
            }
            if (keycode.compare(downKey) == 0)
            {
                transform->velocity.y = 50;
                transform->velocity.x = 0;
                sprite->Play("DownAnimation");
            }
            if (keycode.compare(shootKey) == 0)
            {
                // TODO: shoot projectile when shoot key is pressed
            }
        }

        if (Game::event->type == SDL_KEYUP)
        {
            std::string keycode = std::to_string(Game::event->key.keysym.sym);
            if (keycode.compare(upKey) == 0)
            {
                transform->velocity.y = 0;
            }
            if (keycode.compare(rightKey) == 0)
            {
                transform->velocity.x = 0;
            }
            if (keycode.compare(leftKey) == 0)
            {
                transform->velocity.x = 0;
            }
            if (keycode.compare(downKey) == 0)
            {
                transform->velocity.y = 0;
            }
            if (keycode.compare(shootKey) == 0)
            {
                // TODO:...
            }
        }
    }

    void Render() override
    {
    }
};
