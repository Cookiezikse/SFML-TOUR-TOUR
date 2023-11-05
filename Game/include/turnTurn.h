#pragma once
#include "PokemonType.h"
#include "Attack.h"
#include "Character.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <sstream>


//Ajouter système niveaux et que l'attaque du premier se fait et ensuite on dit si c'est efficace ou pas et si crit 
// Et faire sys fichier de sauvegarde pour le player
// faire aussi sys succès (jouer l'attaque GREEEEEEN, battre son premier pokemon etc)
// Faire une fonction qui permet d'afficher le truc de critique, raté et status et efficace


class Turn_turn {
public:
    void ShowMoves(sf::Font font, const std::vector <std::shared_ptr<Attack>> attack, const Character& character, int selectedIndex, sf::RenderWindow& window, PokemonInfos Pokemon, bool showAttacks);

    void characterPrint_enemy(const sf::Font font, const Character& character, sf::RenderWindow& window, PokemonInfos Pokemon);

    // A mettre en graphique
    void capacitePrint(const sf::Font font, const std::vector <std::shared_ptr<Attack>> attack, const Character& character, int selectedIndex, sf::RenderWindow& window, PokemonInfos Pokemon, bool showAttacks);

    void drawInfo(const sf::Font font, const std::string string, sf::RenderWindow& window, int CharacterSize, int width_divide, int width_multiply, int height, const sf::Color Color = sf::Color::White);

    //Lire le fichier characters.txt pour les ennemies
    void ReadCharacterDataFromFile(std::vector<std::shared_ptr<Character>>& character_list, const std::string filepath);

    //Lire les attaques dans le fichier attacks.txt et les met dans le vector
    void ReadAttackDataFromFile(std::vector<std::shared_ptr<Attack>>& attack_list);

    int CalculDamage(Attack& attack, const Character& attacker, Character& defenser, PokemonInfos Pokemon);

    void StatusApply(Attack& attack, Character& defenser, PokemonInfos Pokemon);

    bool CalculPrecision(Attack& attack);

    void ReplacePlayerFile(std::vector<std::shared_ptr<Character>>& character);
};


