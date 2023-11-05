#include "Map.h"
#include <iostream>


TileMap::TileMap() {
    sf::Vector2u tileSize(32, 32); 

    if (!this->load("assets/tiles/tiles.png", tileSize, "assets/tiles/main_map.json")) {
        std::cerr << "Erreur lors du chargement du tileset ou de la carte JSON." << std::endl;
        initializeSubMaps();
    }
}

void TileMap::initializeSubMaps() {
    // Configuration de taille de tuile basée sur les paramètres souhaités ou JSON
    sf::Vector2u tileSize(32, 32); 

    // Initialiser 9 sous-cartes pour une grille de 3x3
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            TileMap newMap;
            std::string mapPath = "assets/tiles/map_" + std::to_string(i * 3 + j) + ".json";
            if (!newMap.load("assets/tiles/tiles.png", tileSize, mapPath)) {
                std::cerr << "Erreur lors du chargement de la sous-carte à l'index [" << i << "][" << j << "]" << std::endl;
            }
            else {
                subMaps.push_back(newMap); 
            }
        }
    }
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const std::string& levelFile) {
    if (!m_tileset.loadFromFile(tileset)) {
        std::cerr << "Erreur lors du chargement du tileset: " << tileset << std::endl;
        return false;
    }

    std::ifstream mapf(levelFile);
    json j = json::parse(mapf);

    // Extraction des données de la carte depuis le fichier JSON
    std::vector<int> tiles = j["layers"][0]["data"];
    int width = j["width"];
    int height = j["height"];

    std::cout << "Dimensions de la carte: " << width << "x" << height << std::endl; // Affiche les dimensions de la carte

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int tileNumber = tiles[i + j * width] - 1;

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);



            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // Définition des coins de chaque tuile avec la nouvelle taille
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // Mapping des coordonnées de texture avec la nouvelle taille
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    std::cout << "Carte chargee avec succes." << std::endl;
    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dessinez la carte principale
    states.transform *= getTransform(); 
    states.texture = &m_tileset;
    target.draw(m_vertices, states);

    // Dessinez chaque sous-carte
    for (const auto& subMap : subMaps) {
        subMap.draw(target, states);
    }

}

void TileMap::setView(const sf::Vector2i& cameraPosition, sf::Vector2u tileSize) {
    // Déplacement de la vue pour afficher la carte en fonction de la position de la caméra
    float newLeft = static_cast<float>(cameraPosition.x * tileSize.x);
    float newTop = static_cast<float>(cameraPosition.y * tileSize.y);
    setPosition(-newLeft, -newTop);
}