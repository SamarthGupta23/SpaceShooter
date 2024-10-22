#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Spaceship.hpp"
#include "Enemy.hpp"
class Game {
public:
    Game();  // Constructor
    void run();

private:
    void processEvents();
    void update();
    void render();

    // Variables
    sf::RenderWindow mWindow;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    std::vector<sf::Sprite> laserStore;
    std::vector <sf::Sprite> laserEnemy;
    //music
    sf::Music backgroundMusic;

    //collision checking
    sf::Vector2f playerPos;
    sf::Vector2f enemyPos;


    //collision rendering

    std::vector <int> collisionIndex;

    //textures
    std::vector <sf::Texture> moon;
    int moonIndex;
    sf::Sprite Moon;
    void updateMoon();

    //handle collisions
    void isCollision();

    Spaceship player;  // Spaceship object
    Enemy enemy; //enemy object
    // Helper functions
    void initVariables();
};
