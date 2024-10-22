#include "Game.hpp"
#include <iostream>
Game::Game()
    : mWindow(sf::VideoMode(1600, 900), "Space Samurais"), player()  // Initialize window and spaceship
{
    initVariables();
}


void Game::updateMoon()
{
    moonIndex++;
    if (moonIndex >= 120)
    {
        moonIndex = moonIndex % 120;
    }
    if (moonIndex % 4 == 0) {
        
        Moon.setTexture(moon[moonIndex / 4]);
    }
}

void Game::isCollision() {
    // Use pointers to get the vectors
    std::vector<sf::Sprite>* playerLasers = new std::vector<sf::Sprite>(player.getLasers());
    std::vector<sf::Sprite>* enemyLasers = new std::vector<sf::Sprite>(enemy.getLasers());

    // Check for collisions
    for (size_t i = 0; i < enemyLasers->size(); i++) {
        if (player.getSprite().getGlobalBounds().intersects(enemyLasers->at(i).getGlobalBounds())) {
            // Handle collision
            std::cout << "Collision detected!" << std::endl;
            player.reduceHealth(10);
            // Example: Remove the laser on collision (assuming you have a method to do this)
            enemy.removeLaser(i);
            i--;
            // You may also want to break here if you only want to handle one collision at a time
            break;
        }
    }
    for (size_t i = 0; i < playerLasers->size(); i++) {
        if (enemy.getSprite().getGlobalBounds().intersects(playerLasers->at(i).getGlobalBounds())) {
            // Handle collision
            std::cout << "Collision detected!" << std::endl;
            enemy.reduceHealth(10);
            // Example: Remove the laser on collision (assuming you have a method to do this)
            player.removeLaser(i);
            i--;
            // You may also want to break here if you only want to handle one collision at a time
            break;
        }
    }
    // Clean up the allocated memory
    delete playerLasers;
    delete enemyLasers;
}

void Game::initVariables() {
    // Set frame limit
    mWindow.setFramerateLimit(120);

    // Load background texture
    backgroundTexture.loadFromFile("C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/images/background.png");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, mWindow.getSize().x, mWindow.getSize().y));
    
    //play music
    if (!backgroundMusic.openFromFile("C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/music/background_music.wav")) {
        std::cout << "Failed to load background music!" << std::endl;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(30);
    backgroundMusic.play();
    this->moonIndex = 0;
    
    //moon frames
    for (int i = 1; i <= 60; i++)
    {
        sf::Texture frame;
        std::string filename = "C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/images/Moon/" + std::to_string(i) + ".png";
        frame.loadFromFile(filename);
        moon.push_back(frame);
    }
    Moon.setPosition(1000, 550);
    Moon.setTexture(moon[0]);
    Moon.setScale(4, 4);
}

void Game::run() {
    while (mWindow.isOpen() && player.isAlive() && enemy.isAlive()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

        player.handleInput(event);  // Delegate input handling to the spaceship
        enemy.handleInput(event);
    }
}

void Game::update() {
    // Update the player and enemy
    player.update();
    enemy.update();
    updateMoon();
    isCollision();
    if (!player.isAlive()) {
        mWindow.close();
        std::cout << "RED wins\n Red was at healh: ";
        std::cout << enemy.health;
        
    }
    if (!enemy.isAlive()) {
        mWindow.close();
        std::cout << "BLUE wins\n Blue was at health: ";
        std::cout << player.health;
    }

    // Check for player laser collisions with the enemy
    auto playerLasers = player.getLasers();  // Get reference to the actual laser vector
    
}




void Game::render() {
    mWindow.clear();
    mWindow.draw(background);
    mWindow.draw(Moon);
    mWindow.draw(player.getSprite());
    mWindow.draw(enemy.getSprite());
    
    laserEnemy = enemy.getLasers();
    laserStore = player.getLasers();
    for (int i = 0; i < laserStore.size(); i++)
    {
        mWindow.draw(laserStore[i]);
    }
    for (int i = 0; i < laserEnemy.size(); i++)
    {
        mWindow.draw(laserEnemy[i]);
    }
    mWindow.display();
}
