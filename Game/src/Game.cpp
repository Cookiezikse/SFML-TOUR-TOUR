#include "Game.h"
#include <iostream>





Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "La Voie du Sucre") {
    // Chargez les textures
    if (!playerTexture.loadFromFile("assets/player/img-player.png")) {
        std::cerr << "Erreur lors du chargement de l'image du joueur !" << std::endl;
    }
    if (!enemyTexture.loadFromFile("assets/enemy/img-enemy.png")) {
        std::cerr << "Erreur lors du chargement de l'image de l'ennemi !" << std::endl;
    }

    // Initialisez le sprite du joueur
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);


}


void Game::run() {

    // Icon du Jeu
    sf::Texture iconTexture;
    if (!iconTexture.loadFromFile("assets/icon/donuts.png")) {
        std::cerr << "Erreur lors du chargement de l'icon du jeu !" << std::endl;
    }
    sf::Image iconImage = iconTexture.copyToImage();
    window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());



    Success success;
    success.AddSuccess("Start the game !");
    int menuChoice = mainMenu.run(window);

    switch (menuChoice) {
    case 0:  // Play
        gameLoop();
        break;

    case 1:  // Settings
        settingsMenu.run(window); // Affichez le menu Settings
        run(); // Revenez au menu principal après avoir quitté le menu Settings
        break;

    case 2:  // Quit
        window.close();
        return;

    case 3: //Start fight
        Turn_per_turn.run(window);
        run();
        break;

    default:
        // Gérer les erreurs inattendues
        break;
    }
}

void Game::moveCamera(const sf::Vector2i& movement) {
    cameraPosition += movement;

    // Empêchez la caméra de sortir des limites de la matrice 3x3
    cameraPosition.x = std::max(0, std::min(2, cameraPosition.x));
    cameraPosition.y = std::max(0, std::min(2, cameraPosition.y));

    float offset = 50.0f; // un petit décalage pour éviter un retour immédiat

    // Replacez le joueur de l'autre côté de l'écran
    if (movement.x == 1) player.setPosition(offset, player.getPosition().y);
    else if (movement.x == -1) player.setPosition(WINDOW_WIDTH - player.getBounds().width - offset, player.getPosition().y);
    if (movement.y == 1) player.setPosition(player.getPosition().x, offset);
    else if (movement.y == -1) player.setPosition(player.getPosition().x, WINDOW_HEIGHT - player.getBounds().height - offset);

    sf::Vector2u tileSize = { 16, 16 };

    mMap.setView(cameraPosition, tileSize);
}

void Game::gameLoop() {
    // Créer des ennemis
    //createEnemies();

    while (window.isOpen()) {

        handleEvents();
        if (!isPaused) {
            update();
        }
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                isPaused = !isPaused;  // Activer/désactiver la pause avec la touche "P"
                std::cout << "Touche P appuyée. Pause = " << isPaused << std::endl;

                if (isPaused) {
                    int pauseChoice = pause.run(window);
                    if (pauseChoice == 0) {
                        isPaused = false;  // Reprendre le jeu
                    }
                    else if (pauseChoice == 1) {
                        // Recommencer le jeu
                        // Réinitialisez les éléments du jeu, par exemple le joueur et la carte
                    }
                    else if (pauseChoice == 2) {
                        window.close();  // Quitter le jeu
                    }
                }
            }
        }
    }

    player.handleInput();

    // Vérifier si le joueur atteint un bord
    sf::Vector2i movement = player.checkBounds();
    if (movement.x != 0 || movement.y != 0) {
        moveCamera(movement);
    }

}


void Game::update() {
    player.update();

    // Mise à jour des ennemis
    for (auto& enemy : enemies) {
        enemy.update();

        // Vérification des collisions comme auparavant
        if (enemy.getBounds().intersects(player.getBounds())) {
            // Démarrez le combat
            std::cout << "Combat initié!" << std::endl;
        }
    }
}



void Game::render() {
    window.clear();

    // Dessinez la carte
    mMap.draw(window, sf::RenderStates::Default);

    // Dessinez le joueur
    player.draw(window);

    // Dessinez tous les ennemis
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }

    window.display();
}
