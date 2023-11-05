#include "Attack_turn.h"

int AttackMenu::run(sf::RenderWindow& window) {
    std::vector<std::shared_ptr<Attack>> attackOptions;
    std::vector<std::shared_ptr<Character>> characterOptions;
	std::vector<std::shared_ptr<Character>> P1;
    std::vector<std::shared_ptr<Attack>> attacks_player;
    std::vector<std::shared_ptr<Attack>> attacks_enemy;
    Turn_turn Turn;

    Turn.ReadAttackDataFromFile(attackOptions);

    Turn.ReadCharacterDataFromFile(characterOptions,"assets/Datas/characters.txt");
    Turn.ReadCharacterDataFromFile(P1,"assets/Datas/player.txt");
    //P1[0]->changeName("Jaja");
    //Turn.ReadCharacterDataFromFile(P1, "assets/Datas/player.txt");
    //P1[0]->getHp();
    //Character P1("Jaja", 500, 999, 20, 20, 20, 3, 5, 6, 12, "Psychic", 100); //Faire read le file pour mettre les données du player
    //Character P2("L'ane Trotro", 100, 999, 10, 50, 20, 1, 2, 3, 4, "Dragon", 70);//Faire read le file pour mettre les données d'un ennemi
    
    /*
    for (int i = 0; i < characterOptions.size(); i++) {
		if (characterOptions[i]->getName() == "Bongo") {
            P1.push_back(characterOptions[i]);
            break;
		}
    }
    */
    std::srand(std::time(nullptr));
    int random_variable = std::rand() % 30 + 1;
    std::vector<std::shared_ptr<Character>> P2;
    P2.push_back(characterOptions[random_variable]);

    // L'attaque fait max 11 dégats
    // Ne prends pas la bonne attaque et ducoup attaque simple ?


    //Mettre les attaques que peut faire le player 
    for (int i = 0; i < 4; i++) {
        attacks_player.push_back(attackOptions[P1[0]->capa(i + 1)]);
    }
    //Mettre les attaques que peut faire l'enemy
    for (int i = 0; i < 4; i++) {
        attacks_enemy.push_back(attackOptions[P2[0]->capa(i)]);
    }
	int damage_p1 = 0;
    int damage_p2 = 0;
    bool active_1 = true;
    bool active_2 = true;
    bool end = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    soundManager.playNavigateEnterSound();
                    
                    if (!active_1) {
                        active_1 = true;
                        active_2 = false;
                        if (P1[0]->getSpeed() < P2[0]->getSpeed()) {
                            if (P2[0]->IsAlive()) {
                                damage_p1 = Turn.CalculDamage(*attacks_enemy[1], *P1[0], *P2[0], Pokemon);
                                P2[0]->takeDamage(damage_p1);
                                P2[0]->handleStatus();
                            }
                        }
                        else {
                            if (P1[0]->IsAlive()) {
								damage_p2 = Turn.CalculDamage(*attacks_player[selectedIndex], *P2[0], *P1[0], Pokemon);
                                P1[0]->takeDamage(damage_p2);
                                P1[0]->handleStatus();
                            }
                        }
                    }
                    else if (!active_2) {
                        active_2 = true;
                    }
                    
                    if (end) {
                        return 0;
                    }
                }
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (P1[0]->IsAlive() && P2[0]->IsAlive() && active_1 == true && active_2 == true) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Q) {
                        soundManager.playNavigateSound();
                        selectedIndex = (selectedIndex - 1 + attacks_player.size()) % attacks_player.size();
                    }
                    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {
                        soundManager.playNavigateSound();
                        selectedIndex = (selectedIndex + 1) % attacks_player.size();
                    }
                    else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::X) {
                        soundManager.playNavigateEnterSound();
                        if (attacks_player[selectedIndex]->getUse() > 0) {
                            active_1 = false;
                            if (P1[0]->getSpeed() < P2[0]->getSpeed()) {
                                damage_p2 = Turn.CalculDamage(*attacks_player[selectedIndex], *P2[0], *P1[0], Pokemon);
                                P1[0]->takeDamage(damage_p2);
                                P1[0]->handleStatus();
                                Turn.drawInfo(font, P2[0]->getName() + " a attaque !", window, 40, 12, 4, 450);
                            }
                            else {
                                damage_p1 = Turn.CalculDamage(*attacks_enemy[1], *P1[0], *P2[0], Pokemon);
                                P2[0]->takeDamage(damage_p1);
                                P2[0]->handleStatus();
                                Turn.drawInfo(font, P1[0]->getName() + " a attaque !", window, 40, 12, 4, 450);
                            }
                            //Faire le truc d'attaques , faire : boucle event, attaque puis attends genre 10 sec avec anim barre et ensuite remet input 
                        }
                        else {
                            std::cout << "Invalid";
                        }
                    }
                }
            }
        }

        //Tout ce qui est affiché
        window.clear();
        if (P1[0]->IsAlive() && P2[0]->IsAlive()) {
            if (active_1 && active_2) {
                Turn.ShowMoves(font, attacks_player, *P1[0], selectedIndex, window, Pokemon, true);
            }
            else {
                Turn.ShowMoves(font, attacks_player, *P1[0], selectedIndex, window, Pokemon, false);
                Turn.drawInfo(font, "Press 'W' to continue", window, 40, 12, 4, 550);
                if (!active_1) {
                    if (P1[0]->getSpeed() < P2[0]->getSpeed()) {
                        Damage_pi(damage_p2, *P2[0], Turn, window,font);
                    }
                    else {
                        Damage_pi(damage_p1, *P1[0], Turn, window,font);
                    }
                }
                else if (!active_2) {
                    if (P1[0]->getSpeed() < P2[0]->getSpeed()) {
                        Damage_pi(damage_p1, *P1[0], Turn, window,font);
                    }
                    else {
                        Damage_pi(damage_p2, *P2[0], Turn, window,font);
                    }
                }
            }
        }
        else if (!P1[0]->IsAlive() || !P2[0]->IsAlive()) {
            if (!P1[0]->IsAlive()) {
                Turn.ShowMoves(font, attacks_player, *P1[0], selectedIndex, window, Pokemon, false);
                Turn.drawInfo(font, "Vous avez perdu...", window, 40, 12, 5, 350);
                end = true;
            }
            else {
                Turn.ShowMoves(font, attacks_player, *P1[0], selectedIndex, window, Pokemon, false);
                Turn.drawInfo(font, "Vous avez gagne !", window, 40, 12, 5, 350);
                end = true;
                Turn.drawInfo(font, "Press 'W' to continue", window, 40, 12, 4, 550);
            }
        }
        Turn.characterPrint_enemy(font, *P2[0], window, Pokemon);
        window.display();

        //Si y a besoin de clear la fenetre
        /*
        window.clear();
        window.display();
        */
    }

    return 99;
}

void AttackMenu::Damage_pi(int damage, const Character P, Turn_turn Turn , sf::RenderWindow& window,sf::Font font) {
    if (damage > 0) {
        Turn.drawInfo(font, P.getName() + " a attaque !", window, 40, 12, 4, 300);
    }
    else {
        Turn.drawInfo(font, P.getName() + " a rate !", window, 40, 12, 4, 300);
    }
}