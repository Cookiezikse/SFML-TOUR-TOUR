#pragma once
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

#include "Menu.h"
#include "Player.h"
#include "Map.h"
#include "SettingsMenu.h"
#include "Pause.h"
#include "Attack_turn.h"
#include "Success.h"
#include "Enemy.h"


class Game {
private:
    sf::RenderWindow window;

    Player player;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;


    std::vector<Enemy> enemies;
    sf::Texture enemyTexture;

    TileMap mMap;
    sf::Vector2i cameraPosition = { 1, 1 };  // Position initiale de la caméra au centre

    Menu mainMenu;  // Instancie le Menu de demarrage

    Pause pause;    // Instancie le Menu Pause
    bool isPaused;

    AttackMenu Turn_per_turn;


    // Gestion du Son
    sf::Sound navigateSound_enter;
    sf::Sound navigateSound;
    std::vector<sf::Sound*> allSounds = { &navigateSound_enter, &navigateSound };

    SettingsMenu settingsMenu;
public:
    Game();

    void run();

    void moveCamera(const sf::Vector2i& movement);

    void gameLoop();

    void handleEvents();

    void update();

    void render();

    void createEnemies() {
        // Créer des ennemis aux quatre emplacements choisis
        sf::Vector2f enemyPosition1(50.f, 50.f); // Proche du coin en haut à gauche
        sf::Vector2f enemyPosition2(WINDOW_WIDTH - 50.f, 50.f); // Proche du coin en haut à droite
        sf::Vector2f enemyPosition3(50.f, WINDOW_HEIGHT - 50.f); // Proche du coin en bas à gauche
        sf::Vector2f enemyPosition4(WINDOW_WIDTH - 50.f, WINDOW_HEIGHT - 50.f); // Proche du coin en bas à droite

        // Utilisez la fonction emplace_back pour ajouter des ennemis directement dans le vecteur sans copier
        enemies.emplace_back(enemyTexture, enemyPosition1);
        enemies.emplace_back(enemyTexture, enemyPosition2);
        enemies.emplace_back(enemyTexture, enemyPosition3);
        enemies.emplace_back(enemyTexture, enemyPosition4);
    }

    void draw(sf::RenderWindow& window) {
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
    }
};
