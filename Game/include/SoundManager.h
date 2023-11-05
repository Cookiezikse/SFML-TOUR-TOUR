#pragma once
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <vector>

class SoundManager {
private:
    //Sound Effect Menu - Deplacement 
    sf::SoundBuffer navigateSoundBuffer;
    sf::Sound navigateSound;

    // Sound Effect Menu - Enter
    sf::SoundBuffer navigateSoundBuffer_enter;
    sf::Sound navigateSound_enter;

    // Musique d'ambiance
    sf::Music music_menu;

public:
    SoundManager() {
        if (!navigateSoundBuffer.loadFromFile("assets/sounds/navigation.wav")) {
            std::cerr << "Erreur lors du chargement du son de navigation du menu (Deplacement)!" << std::endl;
        }
        if (!navigateSoundBuffer_enter.loadFromFile("assets/sounds/navigation_enter.wav")) {
            std::cerr << "Erreur lors du chargement du son de navigation du menu (Entree)!" << std::endl;
        }
        if (!music_menu.openFromFile("assets/sounds/music_menu.wav")) {
            std::cerr << "Erreur lors du chargement de la musique d'ambiance !" << std::endl;
        }
        navigateSound.setBuffer(navigateSoundBuffer);
        navigateSound_enter.setBuffer(navigateSoundBuffer_enter);
    }

    void playNavigateSound();

    void playNavigateEnterSound();

    void playMenuMusic();

    std::vector<sf::Sound*> getAllSounds() {
        return { &navigateSound, &navigateSound_enter };
    }
};


