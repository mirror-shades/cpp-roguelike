#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "map.h"
#include "player.h"

class Render
{
public:
    void loadFont();
    void drawMap(sf::RenderWindow &window, Tile map[Map::MAP_WIDTH][Map::MAP_HEIGHT]);
    void drawPlayer(sf::RenderWindow &window, Player &player);

private:
    void drawBackground(sf::RenderWindow &window);
    void drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y);
    void drawSymbol(sf::RenderWindow &window, char symbol, int x, int y);
};
