#include "Pause.h"

void Pause::setSelectedIndex(int index) {
    selectedIndex = index;
}

int Pause::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Dessinez le titre "Pause"
        window.draw(title);

        for (size_t i = 0; i < options.size(); i++) {
            if (i == selectedIndex) {
                options[i].setFillColor(sf::Color::Red);
            }
            else {
                options[i].setFillColor(sf::Color::White);
            }
            window.draw(options[i]); // Dessinez les options dans la fenêtre
        }

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            selectedIndex = (selectedIndex + 1) % options.size();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            return selectedIndex;
        }
    }

    return -1;
}