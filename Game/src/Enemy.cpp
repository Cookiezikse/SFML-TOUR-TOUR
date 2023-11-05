#include "Enemy.h"



Enemy::Enemy(Enemy&& other) noexcept
    : // Initialisation de tous les membres via la liste d'initialisation
    sprite(std::move(other.sprite)),
    movementClock(std::move(other.movementClock))
{
    // Le corps du constructeur (si nécessaire pour une logique supplémentaire)
}

Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (this != &other) {
        sprite = std::move(other.sprite);
        movementClock = std::move(other.movementClock);
        // ... (assignation des autres membres)
    }
    return *this;
}

void Enemy::update() {
    if (movementClock.getElapsedTime() > movementCooldown) {
        // Déplacez l'ennemi à une nouvelle position aléatoire dans la grille 3x3
        sprite.setPosition(dis(gen) * gridWidth / 3.0f, dis(gen) * gridHeight / 3.0f);
        movementClock.restart();
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBoundingBox() const {
    return sprite.getGlobalBounds();
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Enemy::checkCollision(const sf::Sprite& playerSprite) const {
    return sprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds());
}

void Enemy::triggerCombat(sf::RenderWindow& window) {
    AttackMenu attackmenu;
    attackmenu.run(window);
}

void Enemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}
