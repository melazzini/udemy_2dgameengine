#pragma once

#include "Component.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include <vector>
class EntityManager
{
  private:
    std::vector<Entity *> entities;

  public:
    void ClearData();
    void Update(float deltaTime);
    void Render();
    bool HasNoEntities();
    Entity &AddEntity(std::string entityName, LayerType layer);
    std::vector<Entity *> GetEntities() const;
    std::vector<Entity *> GetEntitiesByLayer(LayerType layer) const;
    unsigned int GetEntityCount();
    void DisplayAllEntities() const;
    CollisionType CheckCollisions() const;
};
