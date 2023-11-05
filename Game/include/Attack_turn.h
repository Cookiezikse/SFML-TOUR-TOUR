#pragma once

#include "turnTurn.h"
#include "SoundManager.h"

// Afficher les pv actuels/pv totaux et le type de chacun avec leurs niveaux (si il y a)
// Système de changement de capacités, pouvoir avoir son propre nom et voila

class AttackMenu {

private:
    std::vector<sf::Text> options;
    sf::Font font;
    int selectedIndex = 0;

public:
    SoundManager soundManager;
    class PokemonInfos Pokemon;
    // Mettre tout ceci dans une classe pour le combat en général avec toutes fonctions que j'utilise
    // Attack et Character c'est bon

    AttackMenu() {
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {  // Chargez votre propre police ici
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }
    }

    int run(sf::RenderWindow& window);

    void Damage_pi(int damage, const Character P, Turn_turn Turn, sf::RenderWindow& window, sf::Font font);
};

