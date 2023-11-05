#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Sprite : public Component
{
public:
	Sprite(std::string texture, int maxHealth, float scale);
	~Sprite() override;

	enum Direction {DOWN,UP,RIGHT,LEFT};
	int anim_speed = 10;
	int count = 0;
	
	//void moveLeft();
	//void moveRight();
	//void moveUp();
	//void moveDown();

	void moveBack(int direction);

	sf::Vector2i getAnimation() { return Animation; }
	void setAnimation(int y) {
		Animation.y = y;
	}

	sf::Sprite* getSprite() { return sprite; }

	void setOldPosition(Maths::Vector2f position);
	Maths::Vector2f getOldPosition();
	float getOldXPosition();
	float getOldYPosition();


	int getMaxHealth() { return maxHealth; }
	int getCurrentHealth() { return currHealth; }

	void setCurrentHealth(int health) { currHealth = health; }

	void Attack();
	void Kill();
	void incrementCount() { if (!isAttacking) count++; }

	void setAttacking(bool attacking) { isAttacking = attacking; }
	bool getAttacking() { return isAttacking; }

	void Update() override;
	void Render(sf::RenderWindow* _window) override;

private:
	sf::Texture texture;
	sf::Texture attackTexture;
	sf::Sprite* sprite = nullptr;
	sf::Vector2i Animation = sf::Vector2i (1, DOWN);
	Maths::Vector2f oldPosition;
	int maxHealth;
	int currHealth;
	bool isAttacking = false;
};
