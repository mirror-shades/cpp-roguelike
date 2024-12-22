#include <SFML/Graphics.hpp>
#include "render.h"
#include "map.h"
#include "player.h"

sf::Font font;

void Render::loadFont()
{
    if (!font.loadFromFile("assets/Consolas.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
}

void Render::drawBackground(sf::RenderWindow &window)
{
    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setFillColor(sf::Color::Black);
    window.draw(background);
}

void Render::drawPlayer(sf::RenderWindow &window, Player &player)
{
    drawSymbol(window, '@', player.x, player.y);
}

void Render::drawSymbol(sf::RenderWindow &window, const char symbol, int x, int y)
{
    sf::Text text(symbol, font);
    text.setCharacterSize(Map::SQUARE_SIZE);
    text.setPosition(x * Map::SQUARE_SIZE, y * Map::SQUARE_SIZE);
    window.draw(text);
}

void Render::drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y)
{
    // Draw background
    sf::RectangleShape background(sf::Vector2f(Map::SQUARE_SIZE, Map::SQUARE_SIZE));
    // this magic is needed to convert the color from 0xRRGGBB to sf::Color for SFML
    // this format is a split hex value, (0x00, 0x00, 0x00) for black, ect
    const sf::Color squareColor = sf::Color(
        (static_cast<int>(tile.color) >> 5) * 32,         // Red   (bits 5-7)
        ((static_cast<int>(tile.color) >> 2) & 0x7) * 32, // Green (bits 2-4)
        (static_cast<int>(tile.color) & 0x3) * 64         // Blue  (bits 0-1)
    );
    background.setFillColor(squareColor);
    background.setPosition(x * Map::SQUARE_SIZE, y * Map::SQUARE_SIZE);
    window.draw(background);
    this->drawSymbol(window, tile.symbol, x, y);
}

void Render::drawMap(sf::RenderWindow &window, Tile map[Map::MAP_WIDTH][Map::MAP_HEIGHT])
{
    drawBackground(window);
    for (int j = 0; j < Map::MAP_HEIGHT; j++)
    {
        for (int i = 0; i < Map::MAP_WIDTH; i++)
        {
            drawTile(window, map[i][j], i, j);
        }
    }
}