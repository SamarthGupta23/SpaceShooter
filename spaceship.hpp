#pragma once
#include <SFML/Graphics.hpp>

class Spaceship {
public:
    Spaceship();

    void handleInput(const sf::Event& event); //input to shoot and move around
    void update();  //updates positions  , directions , movement
    sf::Sprite getSprite() const;
    std::vector <sf::Sprite> getLasers() const;
    sf::Vector2f getPos() const;
    void removeLaser(int index);
    void reduceHealth(int damage);
    bool isAlive();
    int health;
private:
    // Helper functions
    void loadDirection();  //updates directions
    void updateProjectile();
    void updateTimer();
    void updateMovement(); //updates position
    void wrap();

    //utilities functions

    void shoot();
    
    // Variables
    sf::Texture texture;
    sf::Texture laserTexture;
    sf::Sprite sprite;
    std::vector <sf::Sprite> laser;   //laser
    std::vector <sf::Vector2f> laserDirection;  //laser direction
    sf::Vector2f direction;
    sf::Vector2f position;
    

    float speed;
    float timer;
    float laserSpeed;
    float angle;
    const float degToPi = 0.0174533f;  // Conversion constant for degrees to radians

    // Movement flags
    bool moveUp;
    bool shooting;
    bool moveDown;
    bool moveLeft;
    bool moveRight;
};
