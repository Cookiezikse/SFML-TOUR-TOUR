#include "Menu.h"

int Menu::run(sf::RenderWindow& window) {
    window.clear();

    // Joue la musique d'ambiance
    soundManager.playMenuMusic();


    while (window.isOpen()) {
        window.clear(sf::Color::White);

        // Dessine le fond du menu en premier
        window.draw(menuBackgroundSprite);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    soundManager.playNavigateSound();
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    soundManager.playNavigateSound();
                    selectedIndex = (selectedIndex + 1) % options.size();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    soundManager.playNavigateEnterSound();
                    return selectedIndex;
                }
            }
        }

        window.clear();
        for (int i = 0; i < 4; i++) {
            if (i == selectedIndex) {
                options[i].setFillColor(sf::Color::Red);
            }
            else {
                options[i].setFillColor(sf::Color::White);
            }
            window.draw(options[i]);
        }
        window.display();
    }
    return -1;
}

