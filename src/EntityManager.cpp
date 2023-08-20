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

std::string EntityManager::CheckCollisions(Entity &myEntity) const
{
    ColliderComponent *myCollider = myEntity.GetComponet<ColliderComponent>();
    for (auto otherEntity : entities)
    {
        if (otherEntity == &myEntity || otherEntity->name == "Tile")
        {
            continue;
        }
        if (otherEntity->HasComponent<ColliderComponent>())
        {
            if (Collision::CheckRectangleCollision(otherEntity->GetComponet<ColliderComponent>()->collider,
                                                   myCollider->collider))
            {
                return otherEntity->GetComponet<ColliderComponent>()->colliderTag;
            }
        }
    }
    return "";
}
