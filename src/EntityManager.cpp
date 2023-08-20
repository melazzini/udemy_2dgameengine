#include "EntityManager.hpp"
#include "Collision.hpp"
#include "Components/ColliderComponent.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void EntityManager::ClearData()
{
    for (auto &entity : entities)
    {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities()
{
    return entities.size() == 0;
}

void EntityManager::Update(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render()
{
    for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++)
    {
        for (auto entity : GetEntitiesByLayer(LayerType(layerNum)))
        {
            entity->Render();
        }
    }
}

Entity &EntityManager::AddEntity(std::string entityName, LayerType layer)
{
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity *> EntityManager::GetEntities() const
{
    return entities;
}
std::vector<Entity *> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity *> filteredEntities;
    std::copy_if(std::begin(entities), std::end(entities), std::back_inserter(filteredEntities),
                 [layer](const Entity *entity) { return entity->layer == layer; });

    return filteredEntities;
}

unsigned int EntityManager::GetEntityCount()
{
    return entities.size();
}

void EntityManager::DisplayAllEntities() const
{
    for (auto entity : entities)
    {
        std::cout << fmt::format("Entity Name: {}", entity->name) << std::endl;
        entity->ListAllComponents();
    }
}

CollisionType EntityManager::CheckCollisions() const
{
    // WE CAN IMPROVE THE LOGIC OF THIS FUNCTION OURSELFS AFTER FINISHING THE COURSE

    for (auto iter{std::begin(entities)}; iter != std::end(entities); iter++)
    {
        if (!(*iter)->HasComponent<ColliderComponent>())
        {
            continue;
        }
        auto next = iter + 1;
        auto colliderEntity = std::find_if(next, std::end(entities), [iter](Entity *other) {
            if (other->HasComponent<ColliderComponent>())
            {
                auto colliderComponent = other->GetComponet<ColliderComponent>();
                if (Collision::CheckRectangleCollision(colliderComponent->collider,
                                                       (*iter)->GetComponet<ColliderComponent>()->collider))
                {
                    return true;
                }
            }
            return false;
        });

        if (colliderEntity != std::end(entities))
        {
            auto colliderTag1 = (*colliderEntity)->GetComponet<ColliderComponent>()->colliderTag;
            auto colliderTag2 = (*iter)->GetComponet<ColliderComponent>()->colliderTag;

            if ((colliderTag1 == "player" && colliderTag2 == "enemy") ||
                (colliderTag1 == "enemy" && colliderTag2 == "player"))
            {
                return CollisionType::PLAYER_ENEMY_COLLISION;
            }
        }
    }

    return CollisionType::NO_COLLISION;
}
