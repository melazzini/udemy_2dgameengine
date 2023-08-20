#include "FontManager.hpp"
#include "Game.hpp"
#include <SDL_render.h>
#include <SDL_ttf.h>

TTF_Font *FontManager::LoadFont(const char *filePath, int fontSize)
{
    return TTF_OpenFont(filePath, fontSize);
}

void FontManager::Draw(SDL_Texture *texture, SDL_Rect position)
{
    SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}
