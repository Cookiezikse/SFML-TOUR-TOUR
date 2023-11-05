#include <iostream>
#include "Sprite.h"
#include "Components/MusicComponent.h"
#include "SFML/Graphics.hpp"
#include "Scene.h"

Sprite::Sprite(std::string newTexture, int maxHealth, float scale) : maxHealth(maxHealth), currHealth(maxHealth)
{
	if (texture.loadFromFile("assets/sprites/" + newTexture + ".png")) {
		sprite = new sf::Sprite(texture);
		sprite->setScale(scale, scale);
	}
	if (!attackTexture.loadFromFile("assets/sprites/" + newTexture + "_attack.png")) {

	}
}

Sprite::~Sprite()
{
	delete sprite;
	sprite = nullptr;
}

void Sprite::moveBack(int direction) {
	if (GetOwner()) {
		switch (direction) {
		case 0:
			GetOwner()->SetPosition(Maths::Vector2f(oldPosition.x, GetOwner()->GetPosition().y));
			break;
		case 1:
			GetOwner()->SetPosition(Maths::Vector2f(GetOwner()->GetPosition().x, oldPosition.y));
			break;
		default:
			break;
		}
	}
}

void Sprite::setOldPosition(Maths::Vector2f position) {
	oldPosition = position;
}

Maths::Vector2f Sprite::getOldPosition() {
	return oldPosition;
}

float Sprite::getOldXPosition() {
	return oldPosition.x;
}

float Sprite::getOldYPosition() {
	return oldPosition.y;
}

void Sprite::Attack() {
	isAttacking = true;
	sprite->setTexture(attackTexture);
	count = 0;
}

void Sprite::Kill() {
	owner->setActive(false);
	owner->GetOwner()->DeleteGameObject(owner);
	delete owner;
	owner = nullptr;
}

void Sprite::Update() {
	if (isAttacking) {
		++count;
		if (count / 2 >= sprite->getTexture()->getSize().x / sprite->getTexture()->getSize().y) {
			sprite->setTexture(texture);
			isAttacking = false;
		}
		sprite->setTextureRect(sf::IntRect((count / 2) * sprite->getTexture()->getSize().y, 0, sprite->getTexture()->getSize().y, sprite->getTexture()->getSize().y));
	}
	if (count > anim_speed && isAttacking == false) {
		Animation.x++;
		if (Animation.x * 32 >= texture.getSize().x) {
			Animation.x = 0;
		}
		sprite->setTextureRect(sf::IntRect(Animation.x * 32, Animation.y * 32, 32, 32));
		count = 0;
	}
}

void Sprite::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto ownerPos = GetOwner()->GetPosition();
	sprite->setPosition(ownerPos.x, ownerPos.y);

	_window->draw(*sprite);
}
