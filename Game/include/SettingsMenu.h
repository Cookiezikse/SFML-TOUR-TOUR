#pragma once
#include "Menu.h"

class SettingsMenu {
private:
    sf::Font font;
    std::vector<sf::Text> settingsOptions;
    int selectedIndex = 0;
    float volume = 100.0f;  // Le volume par défaut à 100%
    std::vector<sf::Sound*> sounds;  // Pointeurs vers tous les sons
    std::vector<std::shared_ptr<Character>> P1;


public:
    SettingsMenu() {
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        std::string strOptions[] = { "Volume: 100%", "Effacer Sauvegarde" };
        for (int i = 0; i < 2; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(strOptions[i]);
            text.setCharacterSize(40);
            text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60); // Position du texte
            settingsOptions.push_back(text);
        }
    }
    void updateVolumeText() {
        settingsOptions[0].setString("Volume: " + std::to_string(static_cast<int>(volume)) + "%");

    }

    int run(sf::RenderWindow& window) {
        Turn_turn turn;
        while (window.isOpen()) {
            window.clear(sf::Color::White);

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedIndex = (selectedIndex - 1 + 2) % 2;
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        selectedIndex = (selectedIndex + 1) % 2;
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        return selectedIndex;
                    }
                }
                if (selectedIndex == 0) {  // Si l'option "Volume" est sélectionnée
                    if (event.key.code == sf::Keyboard::Right) {
                        volume = std::min(100.0f, volume + 10.0f);
                        sf::Listener::setGlobalVolume(volume);
                        updateVolumeText();
                    }
                    else if (event.key.code == sf::Keyboard::Left) {
                        volume = std::max(0.0f, volume - 10.0f);
                        sf::Listener::setGlobalVolume(volume);
                        updateVolumeText();
                    }
                }
                else if (selectedIndex == 1) {  // Si l'option "Volume" est sélectionnée
                    if (event.key.code == sf::Keyboard::Enter) {
                        auto character = std::make_shared<Character>("Sacha", 10, 10, 10, 10, 10, 1, 5, 7,8, "Normal", 100);
                        P1.push_back(character);
                        P1.push_back(character);
                        turn.ReplacePlayerFile(P1);
                    }
                }

                else if (event.key.code == sf::Keyboard::Enter) {
                    return selectedIndex;
                }
            
            }


            window.clear();
            for (int i = 0; i < 2; i++) {
                if (i == selectedIndex) {
                    settingsOptions[i].setFillColor(sf::Color::Red);
                }
                else {
                    settingsOptions[i].setFillColor(sf::Color::White);
                }
                window.draw(settingsOptions[i]);
            }

            window.display();
        }

        return -1;
    }
};
