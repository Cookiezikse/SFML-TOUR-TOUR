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

#include "PokemonType.h"

class Character {
private:
    PokemonInfos::Status status;

    std::string name;
    std::string type;
    int maxHp;
    int hp;
    int defense;
    int defenseSpecial;
    int attack;
    int attackSpecial;
    int capa1;
    int capa2;
    int capa3;
    int capa4;
    int speed;

public:
    Character(const std::string& name, int hp, int defense, int defenseSpecial, int attack, int attackSpecial, int capa1, int capa2, int capa3, int capa4, const std::string& type, int speed)
        : name(name), hp(hp), defense(defense), defenseSpecial(defenseSpecial), attack(attack), attackSpecial(attackSpecial), capa1(capa1), capa2(capa2), capa3(capa3), capa4(capa4), type(type), speed(speed), maxHp(hp), status(PokemonInfos::NORMAL) {}

    const std::string& getName() const;
    const std::string& getType() const;
    void changeName(const std::string& name_changed);
    int getHp() const;
    int getDefense() const;
    int getAttack() const;
    int getAttackSpecial() const;
    int getDefenseSpecial() const;
    bool IsAlive() const;
    int getmaxHp() const;
    int getCapa1() const;
    int getCapa2() const;
    int getCapa3() const;
    int getCapa4() const;
    int getSpeed() const;

    void setStatus(PokemonInfos::Status newStatus);

    void cureStatus();

    void handleStatus();

    std::string getStatus();

    void takeDamage(int damage_all);

    int capa(int number) const;
};