#pragma once
#include "Component.hpp"
#include "Constants.hpp"
#include <fmt/core.h>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

class EntityManager;

class Entity
{
  private:
    EntityManager &manager;
    bool isActive;
    std::vector<Component *> components;
    std::map<const std::type_info *, Component *> componentTypeMap;

  public:
    std::string name;
    LayerType layer;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name, LayerType layer);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    template <typename T, typename... Args> T &addComponent(Args &&...args)
    {
        T *component = new T{std::forward<Args>(args)...};
        component->owner = this;
        components.push_back(component);
        componentTypeMap[&typeid(*component)] = component;
        component->Initialize();
        return *component;
    }

    template <typename T> T *GetComponet()
    {
        return static_cast<T *>(componentTypeMap[&typeid(T)]);
    }

    void ListAllComponents() const
    {
        for (auto component_i : componentTypeMap)
        {
            // std::cout << fmt::format("Component<{}>", typeid(*component_i).name()) << std::endl;
            std::cout << fmt::format("Component<{}>", component_i.first->name()) << std::endl;
        }
    }

    template <typename TComponent> bool HasComponent() const
    {
        return componentTypeMap.find(&typeid(TComponent)) != componentTypeMap.end();
    }
};
