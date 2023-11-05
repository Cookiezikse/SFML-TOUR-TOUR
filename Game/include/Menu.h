#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Attack_turn.h"
#include "SoundManager.h"


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex = 0;
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackgroundSprite;


    // Gestion du Son
    SoundManager soundManager; // Instanciation du gestionnaire de son

public:
    Menu() {
        // Gestion d'erreurs de Police
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        // Liste du Menu
        std::string strOptions[] = { "Play", "Settings", "Quit", "Test Fight"};
        for (int i = 0; i < 4; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(strOptions[i]);
            text.setCharacterSize(40);
            text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60);
            options.push_back(text);
        }

    }

    std::vector<sf::Sound*> getAllSounds() {
        return soundManager.getAllSounds();
    }

    int run(sf::RenderWindow& window);
};

