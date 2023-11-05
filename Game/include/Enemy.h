#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Attack_turn.h"

class Enemy {
private:
    sf::Sprite sprite;
    sf::Clock movementClock;
    sf::Time movementCooldown = sf::milliseconds(500);
    int gridWidth;
    int gridHeight;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    Enemy(const sf::Texture& texture, sf::Vector2f initialPosition);

    // Définition explicite des opérations de déplacement pour être sûr
    Enemy(Enemy&& other) noexcept;
    Enemy& operator=(Enemy&& other) noexcept;

    // Suppression des opérations de copie
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;


    void update();

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBoundingBox() const;

    sf::FloatRect getBounds() const;

    bool checkCollision(const sf::Sprite& playerSprite) const;

    void triggerCombat(sf::RenderWindow& window); // Placeholder pour la logique de combat

    void setPosition(float x, float y);
};
    