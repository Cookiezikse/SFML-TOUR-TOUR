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

class Attack {
public:
    Attack(const std::string& name, const std::string& type, int damage, int precision, int use, bool special)
        : name(name), type(type), damage(damage), precision(precision), use(use), special(special) {}

    const std::string& getName() const;
    const std::string& getType() const;
    int getDamage() const;
    int getPrecision() const;
    int getUse() const;
    void Used();
    bool isSpecial() const;

private:
    std::string name;
    std::string type;
    int damage;
    int precision;
    int use;
    bool special;
};