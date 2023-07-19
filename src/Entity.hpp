#pragma once
#include "Component.hpp"
#include <string>
#include <vector>

class EntityManager;

class Entity
{
  private:
    EntityManager &manager;
    bool isActive;
    std::vector<Component *> components;

  public:
    std::string name;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    template <typename T, typename... Args> T &addComponent(Args &&...args)
    {
        T *component = new T{std::forward<Args>(args)...};
        component->owner = this;
        components.push_back(component);
        component->Initialize();
        return *component;
    }
};
