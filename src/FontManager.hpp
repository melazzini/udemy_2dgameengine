#pragma once

#include <SDL_rect.h>
#include <SDL_ttf.h>
class FontManager
{
  public:
    static TTF_Font *LoadFont(const char *filePath, int fontSize);
    static void Draw(SDL_Texture *texture, SDL_Rect position);
};
