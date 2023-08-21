#pragma once
#include "../EntityManager.hpp"
#include "TransformComponent.hpp"
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class ProjectileEmitterComponent : public Component
{
  private:
    TransformComponent *transform;
    glm::vec2 origin;
    int speed;
    int range;
    float angleRad;
    bool shouldLoop;

  public:
    ProjectileEmitterComponent(int speed, int range, int angle, bool shouldLoop)
    {
        this->speed = speed;
        this->range = range;
        this->angleRad = glm::radians(static_cast<float>(angle));
        this->shouldLoop = shouldLoop;
    }

    void Initialize() override
    {
        transform = owner->GetComponet<TransformComponent>();
        origin = glm::vec2(transform->position.x, transform->position.y);
        transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
    }

    void Update(float deltatime) override
    {
        if (glm::distance(transform->position, origin) > range)
        {
            if (shouldLoop)
            {
                transform->position.x = origin.x;
                transform->position.y = origin.y;
            }
            else
            {
                owner->Destroy();
            }
        }
    }

    void Render() override
    {
    }
};
