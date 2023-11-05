#pragma once
#include <SFML/Graphics.hpp>

#include "Menu.h"


class Pause {
private:
    sf::Font font;
    sf::Text title;  // Titre "Pause"
    std::vector<sf::Text> options;
    int selectedIndex = 0;

public:
    Pause() {}
    Pause(sf::Font& menuFont) {
        font = menuFont;
        std::string fontPath = "assets/fonts/monogram.ttf";

        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        // Créez le texte "Pause" (titre)
        title.setFont(font);
        title.setString("Pause");
        title.setCharacterSize(60);
        title.setPosition(WINDOW_WIDTH / 2 - 60, 100);

        std::string strOptions[] = { "Reprendre", "Recommencer", "Quitter" };
        for (int i = 0; i < 3; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(strOptions[i]);
            text.setCharacterSize(40);
            text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60);
            options.push_back(text);
        }
    }

    void setSelectedIndex(int index);

    int run(sf::RenderWindow& window);
};