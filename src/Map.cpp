#include "Map.hpp"
#include "Components/TileComponent.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include <fstream>
#include <iostream>

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize)
{
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filepath, int mapSizeX, int mapSizeY)
{
    std::fstream mapFile;
    mapFile.open(filepath);
    for (int y = 0; y < mapSizeY; y++)
    {
        for (int x = 0; x < mapSizeX; ++x)
        {
            char c;
            mapFile.get(c);
            int sourceRectY = atoi(&c) * tileSize;
            mapFile.get(c);
            int sourceRectX = atoi(&c) * tileSize;
            AddTile(sourceRectX, sourceRectY, x * (tileSize * scale), y * (tileSize * scale));
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int sourceX, int sourceY, int x, int y)
{
    Entity &newTile{manager.AddEntity("Tile", LayerType::TILEMAP_LAYER)};
    newTile.addComponent<TileComponent>(sourceX, sourceY, x, y, tileSize, scale, textureId);
}
