#pragma once

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class PokemonInfos {
public:
    //Liste tous les types de Pokemon possibles
    enum Status {
        NORMAL, POISONED, BURNED, ASLEEP
    };

    enum PokemonType {
        Normal, Fire, Water, Grass, Electric, Ice, Fighting, Poison, Ground, Flying, Psychic, Bug, Rock, Ghost, Steel, Dark, Fairy, Dragon, Unknown
    };

    PokemonType TypeToIndex(const std::string& typeName) {
        if (typeName == "Water")            return Water;
        else if (typeName == "Fire")        return Fire;
        else if (typeName == "Grass")       return Grass;
        else if (typeName == "Electric")    return Electric;
        else if (typeName == "Normal")      return Normal;
        else if (typeName == "Ice")         return Ice;
        else if (typeName == "Fighting")    return Fighting;
        else if (typeName == "Poison")      return Poison;
        else if (typeName == "Flying")      return Flying;
        else if (typeName == "Psychic")     return Psychic;
        else if (typeName == "Bug")         return Bug;

        else if (typeName == "Rock")        return Rock;
        else if (typeName == "Ghost")       return Ghost;
        else if (typeName == "Steel")       return Steel;
        else if (typeName == "Dark")        return Dark;
        else if (typeName == "Fairy")       return Fairy;
        else if (typeName == "Dragon")      return Dragon;
        else {
            return Unknown; // Return an invalid type
        }
    }

    float typeChart[19][19] = {
        //            Normal  Fire  Water  Grass  Electric  Ice  Fighting  Poison  Ground  Flying  Psychic  Bug  Rock  Ghost  Steel  Dark  Fairy  Dragon Unknown
        /* Normal */    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0},
        /* Fire */      { 1.0,   0.5,  0.5,   2.0,   1.0,     2.0, 1.0,     1.0,   1.0,    1.0,   1.0,    2.0, 0.5,   1.0,  2.0,  1.0,  1.0,   0.5, 0.0 },
        /* Water */     { 1.0,   2.0,  0.5,   0.5,   1.0,     1.0, 1.0,     1.0,   2.0,    1.0,   1.0,    1.0, 2.0,   1.0,  1.0,  1.0,  1.0,   1.0, 0.0 },
        /* Grass */     { 1.0,   0.5,  2.0,   0.5,   1.0,     1.0, 1.0,     0.5,   2.0,    0.5,   1.0,    2.0, 0.5,   1.0,  0.5,  1.0,  1.0,   0.5, 0.0 },
        /* Electric */  { 1.0,  1.0,  2.0,   0.5,   0.5,     1.0, 1.0,     1.0,   0.0,    2.0,   1.0,    1.0, 1.0,   1.0,  1.0,  1.0,  1.0,   0.5, 0.0 },
        /* Ice */       { 1.0,   0.5,  0.5,   2.0,   1.0,     0.5, 1.0,     1.0,   2.0,    2.0,   1.0,    1.0, 2.0,   1.0,  0.5,  1.0,  1.0,   2.0, 0.0 },
        /* Fighting */  { 2.0,  1.0,  1.0,   1.0,   1.0,     2.0, 1.0,     0.5,   1.0,    0.5,   0.5,    0.5, 2.0,   0.0,  1.0,  2.0,  2.0,   0.5, 0.0 },
        /* Poison */    { 1.0,   1.0,  1.0,   2.0,   1.0,     1.0, 1.0,     0.5,   0.5,    1.0,   1.0,    1.0, 0.5,   0.5,  1.0,  1.0,  2.0,   1.0, 0.0 },
        /* Ground */    { 1.0,   2.0,  1.0,   0.5,   2.0,     1.0, 1.0,     2.0,   1.0,    0.0,   1.0,    0.5, 2.0,   1.0,  1.0,  1.0,  1.0,   1.0, 0.0 },
        /* Flying */    { 1.0,   1.0,  1.0,   2.0,   0.5,     2.0, 2.0,     1.0,   1.0,    1.0,   1.0,    0.5, 1.0,   1.0,  1.0,  1.0,  1.0,   1.0, 0.0 },
        /* Psychic */   { 1.0,   1.0,  1.0,   1.0,   1.0,     1.0, 2.0,     2.0,   1.0,    1.0,   0.5,    1.0, 1.0,   1.0,  1.0,  0.0,  1.0,   1.0, 0.0 },
        /* Bug */       { 1.0,   2.0,  1.0,   0.5,   1.0,     1.0, 0.5,     1.0,   0.5,    0.5,   2.0,    1.0, 1.0,   0.5,  1.0,  2.0,  0.5,   1.0, 0.0 },
        /* Rock */      { 1.0,   0.5,  2.0,   2.0,   1.0,     2.0, 0.5,     0.5,   2.0,    0.5,   1.0,    2.0, 1.0,   1.0,  2.0,  1.0,  1.0,   1.0, 0.0 },
        /* Ghost */     { 0.0,   1.0,  1.0,   1.0,   1.0,     1.0, 1.0,     1.0,   1.0,    1.0,   2.0,    1.0, 1.0,   1.0,  1.0,  1.0,  0.5,   1.0, 0.0 },
        /* Steel */     { 0.5,   2.0,  1.0,   0.5,   0.5,     2.0, 1.0,     1.0,   2.0,    0.5,   0.5,    0.5, 2.0,   1.0,  0.5,  1.0,  0.5,   0.5, 0.0 },
        /* Dark */      { 1.0,   1.0,  1.0,   1.0,   1.0,     1.0, 2.0,     1.0,   1.0,    1.0,   2.0,    1.0, 1.0,   1.0,  1.0,  1.0,  0.5,   1.0, 0.0 },
        /* Fairy */     { 1.0,   1.0,  1.0,   1.0,   1.0,     1.0, 0.5,     2.0,   1.0,    1.0,   1.0,    0.5, 1.0,   1.0,  2.0,  1.0,  2.0,   2.0, 0.0 },
        /* Dragon */    { 1.0,   1.0,  1.0,   1.0,   0.5,     2.0, 1.0,     1.0,   1.0,    1.0,   1.0,    1.0, 1.0,   1.0,  1.0,  1.0,  2.0,   2.0, 0.0 }
    };

    // Function to convert type name to an index

    sf::Color TypeToColor(const std::string& typeName) {
        if (typeName == "Water")            return sf::Color::Blue;
        else if (typeName == "Fire")        return sf::Color::Red;
        else if (typeName == "Grass")       return sf::Color::Green;
        else if (typeName == "Electric")    return sf::Color::Yellow;
        else if (typeName == "Normal")      return sf::Color::White;
        else if (typeName == "Ice")         return sf::Color::Cyan;
        else if (typeName == "Fighting")    return sf::Color(131, 32, 32);//Marron
        else if (typeName == "Poison")      return sf::Color::Magenta;
        else if (typeName == "Flying")      return sf::Color(104, 114, 178); //BLeu clair bizzare
        else if (typeName == "Psychic")     return sf::Color(152, 22, 148); // Violet
        else if (typeName == "Bug")         return sf::Color(43, 243, 70);
        else if (typeName == "Rock")        return sf::Color(179, 87, 25);
        else if (typeName == "Ghost")       return sf::Color(149, 144, 140);
        else if (typeName == "Steel")       return sf::Color(218, 214, 212);
        else if (typeName == "Dark")        return sf::Color(63, 52, 44);
        else if (typeName == "Fairy")       return sf::Color(255, 4, 239);
        else if (typeName == "Dragon")      return sf::Color(81, 108, 246);
        else {
            std::cerr << "Unknown type: " << typeName << std::endl;
            return sf::Color::White; // Return an invalid type
        }
    }
};


