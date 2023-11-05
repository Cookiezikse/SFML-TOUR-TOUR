#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp> // Include JSON library

using json = nlohmann::json;

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap();
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::string& levelFile);
    void setView(const sf::Vector2i& cameraPosition, sf::Vector2u tileSize);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void initializeSubMaps();
    sf::Vector2i getPlayerPosition();

private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::vector<TileMap> subMaps; // Declare subMaps here as a vector of TileMap
};
