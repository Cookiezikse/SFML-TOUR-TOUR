#include "turnTurn.h"

void Turn_turn::ShowMoves(sf::Font font, const std::vector <std::shared_ptr<Attack>> attack, const Character& character, int selectedIndex, sf::RenderWindow& window, PokemonInfos Pokemon, bool showAttacks) {
    Turn_turn::capacitePrint(font, attack, character, selectedIndex, window, Pokemon, showAttacks);
}

void Turn_turn::characterPrint_enemy(const sf::Font font, const Character& character, sf::RenderWindow& window, PokemonInfos Pokemon) {
    drawInfo(font, character.getName(), window, 40, 12, 7, 100);
    drawInfo(font, std::to_string(character.getHp()) + " / " + std::to_string(character.getmaxHp()), window, 40, 30, 25, 100, sf::Color::Green);
    drawInfo(font, character.getType(), window, 40, 12, 9, 100, Pokemon.TypeToColor(character.getType()));
}

void Turn_turn::capacitePrint(const sf::Font font, const std::vector <std::shared_ptr<Attack>> attack, const Character& character, int selectedIndex, sf::RenderWindow& window, PokemonInfos Pokemon, bool showAttacks) {

    //Affiche le type (diff couleurs pour chaque type si possible) de l'attaque avec sa use
    if (showAttacks) {
        for (int i = 0; i < 4; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(attack[i]->getName());
            text.setCharacterSize(40);
            text.setPosition(1200 / 8, 500 + i * 30); //WINDOW_WIDTH
            if (i == selectedIndex) {
                text.setFillColor(sf::Color::Red);
                drawInfo(font, std::to_string(attack[i]->getUse()), window, 40, 12, 5, 500 + i * 30, sf::Color::Red);
                drawInfo(font, attack[i]->getType(), window, 40, 12, 4, 500 + i * 30, sf::Color::Red);
            }
            else {
                text.setFillColor(sf::Color::White);
                drawInfo(font, std::to_string(attack[i]->getUse()), window, 40, 12, 4, 500 + i * 30);
            }
            window.draw(text);
        }
    }
    drawInfo(font, character.getName(), window, 40, 9, 1, 430);
    drawInfo(font, character.getType(), window, 40, 4, 1, 430, Pokemon.TypeToColor(character.getType()));
    drawInfo(font, std::to_string(character.getHp()) + " / " + std::to_string(character.getmaxHp()), window, 40, 30, 11, 430, sf::Color::Green);
}

void Turn_turn::drawInfo(const sf::Font font, const std::string string, sf::RenderWindow& window, int CharacterSize, int width_divide, int width_multiply, int height, const sf::Color Color) {
    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(40);
    text.setPosition(1200 / width_divide * width_multiply, height); //Mettre la position avec des paramêtres //WINDOW_WIDTH
    text.setFillColor(Color);
    window.draw(text);
}

void Turn_turn::ReadCharacterDataFromFile(std::vector<std::shared_ptr<Character>>& character_list, const std::string filepath ){
    std::ifstream file(filepath); // "assets/Datas/characters.txt"

    if (!file.is_open()) {
        std::cout << "Error: Unable to open the character file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type;
        int hp, defense, defenseSpecial, attack, attackSpecial, capa1, capa2, capa3, capa4, speed;
        char comma;
        if (iss >> std::quoted(name) >> comma >> hp >> comma >> defense >> comma >> defenseSpecial >> comma >> attack >> comma >> attackSpecial >> comma >> capa1 >> comma >> capa2 >> comma >> capa3 >> comma >> capa4 >> comma >> std::quoted(type) >> comma >> speed) { //AJOUTER DEF SPE
            auto character = std::make_shared<Character>(name, hp, defense, defenseSpecial, attack, attackSpecial, capa1, capa2, capa3, capa4, type, speed);
            character_list.push_back(character);
        }
        else {
            std::cout << "Error reading line: " << line << std::endl;
        }
    }
    file.close();
}

void Turn_turn::ReadAttackDataFromFile(std::vector<std::shared_ptr<Attack>>& attack_list) {
    std::ifstream file("assets/Datas/attacks.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the attack file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type;
        int damage, precision, use;
        char comma;
        bool special;

        if (iss >> std::quoted(name) >> comma >> std::quoted(type) >> comma >> damage >> comma >> precision >> comma >> use >> comma >> special) {
            auto attack = std::make_shared<Attack>(name, type, damage, precision, use, special);
            attack_list.push_back(attack);
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }
    file.close();
}

void Turn_turn::ReplacePlayerFile(std::vector<std::shared_ptr<Character>>& character) {
    std::string filename = "assets/Datas/player.txt";
    std::ifstream fileIn(filename);
    std::string data;
    char comma =',' ;

    // Write data to the file
    std::ofstream fileOut(filename);
    if (fileOut.is_open()) {
        fileOut << 
            std::quoted(character[0]->getName()) << 
            comma << 
            character[0]->getmaxHp() << 
            comma << 
            character[0]->getAttack() << 
            comma << 
            character[0]->getAttackSpecial() << 
            comma << 
            character[0]->getDefense() << 
            comma << 
            character[0]->getDefenseSpecial() <<
            comma << 
            character[0]->getCapa1() <<
            comma << 
            character[0]->getCapa2() << 
            comma << 
            character[0]->getCapa3() << 
            comma << 
            character[0]->getCapa4() << 
            comma << 
            std::quoted(character[0]->getType()) << 
            comma << 
            character[0]->getSpeed();
        fileOut.close();
    }
    else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
};

int Turn_turn::CalculDamage(Attack& attack, const Character& attacker, Character& defenser, PokemonInfos Pokemon) {

    // si fait Attack attack sans le & change la valeur mais d'un autre truc ? Parce que change pas la valeur juste ici
    attack.Used();
	std::cout << "Attack name : " << attack.getName() << std::endl;
    std::cout << "Use attack : " << attack.getUse() << std::endl;
    //std::cout << attacker.getName() << std::endl;
    if (CalculPrecision(attack)) {
        std::cout << 0 << std::endl;
        return 0;
    }
	std::cout << "Attacker attack" << attacker.getAttack() << std::endl;
    std::cout << "Attacker name" << attacker.getName() << std::endl;

    int damage = 0;
    int damage_attack = attack.getDamage();
    int attacker_attack = attacker.getAttack();
    int defenser_defense = defenser.getDefense();
    const std::string& type_attack = attack.getType();
    const std::string& type_defenser = defenser.getType();

    int attack_type = Pokemon.TypeToIndex(type_attack);
    int defender_type = Pokemon.TypeToIndex(type_defenser);

    float damageMultiplier = Pokemon.typeChart[static_cast<int>(attack_type)][static_cast<int>(defender_type)];

    

    //faire un truc en fonction de si c'est l'attaque spé ou l'attaque normal
    //Faire un attaque.isSpecial() si false etc...

    if (attack.isSpecial()) {
        damage = (0.5 * attacker.getAttackSpecial() * (damage_attack / defenser.getDefenseSpecial() + 1) * damageMultiplier) + 1;
    }
    else {
        damage = (0.5 * attacker_attack * (damage_attack / defenser_defense + 1) * damageMultiplier) + 1;
    }
    std::srand(std::time(nullptr));
    int random_variable = std::rand() % 99 + 1;
    if (random_variable <= 10) {
        std::cout << "CRITIQUE";
        damage += damage;
    }
    StatusApply(attack, defenser, Pokemon);
    return damage;
}

void Turn_turn::StatusApply(Attack& attack, Character& defenser, PokemonInfos Pokemon) {
    if (Pokemon.TypeToIndex(attack.getType()) == PokemonInfos::Poison) {
        std::srand(std::time(nullptr));
        int random_variable = std::rand() % 99 + 1;
        if (random_variable <= 25) {
            defenser.setStatus(Pokemon.POISONED);
        }

    }
    else if (Pokemon.TypeToIndex(attack.getType()) == PokemonInfos::Fire) {
        std::srand(std::time(nullptr));
        int random_variable = std::rand() % 99 + 1;
        if (random_variable <= 15) {
            defenser.setStatus(Pokemon.BURNED);
        }

    }
}

bool Turn_turn::CalculPrecision(Attack& attack) {
    int random = std::rand() % 99 + 1;
    if (random <= attack.getPrecision()) {
        return false;
    }
    else {
        return true;
    }
}