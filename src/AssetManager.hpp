#pragma once
#include "EntityManager.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <map>
#include <string>

class AssetManager
{
  private:
    EntityManager *manager;
    std::map<std::string, SDL_Texture *> textures;
    std::map<std::string, TTF_Font *> fonts;

  public:
    AssetManager(EntityManager *manager);
    ~AssetManager();
    void ClearData();
    void AddTexture(std::string textureId, const char *filePath);
    SDL_Texture *GetTexture(std::string textureId);
    void AddFont(std::string fontId, const char *filePath, int fontSize);
    TTF_Font *GetFont(std::string fontId);
};
