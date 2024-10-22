#pragma once
#include <SFML/Graphics.hpp>
#include <vector>  // Ensure this is included

class Enemy {
public:
    Enemy();

    void handleInput(const sf::Event& event);
    void update();
    sf::Sprite getSprite() const;
    std::vector <sf::Sprite> getLasers() const;
    sf::Vector2f getPos() const;
    void removeLaser(int index);
    void reduceHealth(int damage);
    bool isAlive();
    int health;
private:
    void loadDirection();
    void updateProjectile();
    void updateTimer();
    void updateMovement();
    void wrap();
    void shoot();
    

    // Variables
    sf::Texture texture;
    sf::Texture laserTexture;
    sf::Sprite sprite;
    std::vector <sf::Sprite> laser;
    std::vector <sf::Vector2f> laserDirection;
    sf::Vector2f direction;
    sf::Vector2f position;

    //collisions
    


    float speed;
    float timer;
    float laserSpeed;
    float angle;
    const float degToPi = 0.0174533f;

    // Movement flags
    bool moveUp;
    bool shooting;
    bool moveDown;
    bool moveLeft;
    bool moveRight;
};
