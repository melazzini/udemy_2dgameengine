#include "AssetManager.hpp"
#include "EntityManager.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"
#include <SDL_ttf.h>
#include <cstdlib>

AssetManager::AssetManager(EntityManager *manager) : manager(manager)
{
}

void AssetManager::ClearData()
{
    textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char *filePath)
{
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture *AssetManager::GetTexture(std::string textureId)
{
    return textures[textureId];
}

void AssetManager::AddFont(std::string fontId, const char *filePath, int fontSize)
{
    auto newFont = FontManager::LoadFont(filePath, fontSize);
    fonts[fontId] = newFont;
}

TTF_Font *AssetManager::GetFont(std::string fontId)
{
    return fonts.at(fontId);
}
