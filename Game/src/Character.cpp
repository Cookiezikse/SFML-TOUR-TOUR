#include "Character.h"


const std::string& Character::getName() const { return name; }
const std::string& Character::getType() const { return type; }
void Character::changeName(const std::string& name_changed) { name = name_changed; }
int Character::getHp() const { return hp; }
int Character::getDefense() const { return defense; }
int Character::getAttack() const { return attack; }
int Character::getAttackSpecial() const { return attackSpecial; }
int Character::getDefenseSpecial() const { return defenseSpecial; }
bool Character::IsAlive() const { return hp > 0; }
int Character::getmaxHp() const { return maxHp; }
int Character::getCapa1() const { return capa1; }
int Character::getCapa2() const { return capa2; }
int Character::getCapa3() const { return capa3; }
int Character::getCapa4() const { return capa4; }
int Character::getSpeed() const { return speed; }

void Character::setStatus(PokemonInfos::Status newStatus) {
    status = newStatus;
}

void Character::cureStatus() {
    status = PokemonInfos::NORMAL;
}

void Character::handleStatus() {
    if (status == PokemonInfos::POISONED) {
        int poisonDamage = hp / 8;
        hp -= poisonDamage;
        if (hp < 0) {
            hp = 0;
        }
    }
    else if (status == PokemonInfos::BURNED) {
        int burnDamage = maxHp / 8;
        hp -= burnDamage;
        if (hp < 0) {
            hp = 0;
        }
        std::cout << "burned";
    }
    else if (status == PokemonInfos::ASLEEP) {
        //RIP
    }
}

std::string Character::getStatus() {
    switch (status) {
    case PokemonInfos::NORMAL: return "Normal";
    case PokemonInfos::POISONED: return "Poisoned";
    case PokemonInfos::BURNED: return "Burned";
    case PokemonInfos::ASLEEP: return "ASLEEP";
    default: return "Inconnu";
    }
}

void Character::takeDamage(int damage_all) {
    hp -= damage_all;
    std::cout << std::endl;
	std::cout << damage_all << std::endl;
    std::cout << hp << std::endl;
    if (hp < 0) {
        hp = 0;
        std::cout << name << " is dead!" << std::endl;
    }
}

int Character::capa(int number) const {
    if (number >= 1 && number <= 4) {
        switch (number) {
        case 1:
            return capa1;
        case 2:
            return capa2;
        case 3:
            return capa3;
        case 4:
            return capa4;
        }
    }
}