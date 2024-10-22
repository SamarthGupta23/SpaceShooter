#include "Enemy.hpp"

Enemy::Enemy()
    : speed(4.f * 14 / 12), angle(90.f), moveUp(false), moveDown(false), moveLeft(false), moveRight(false) {
    // Load enemy texture
    texture.loadFromFile("C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/images/enemy.png");
    laserTexture.loadFromFile("C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/images/laser-2.png");
    sprite.setTexture(texture);
    sprite.setScale(1.5f, 1.5f);

    // Set laser size (make it bigger)
    laserTexture.setSmooth(true); // Optional: if you want smooth textures

    timer = 12;
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    laserSpeed = 10.f * 14 / 12;
    health = 100;
    // Set initial position
    sprite.setPosition(1500.f, 100.f);
    position = sprite.getPosition();

    // Initialize direction
    loadDirection();
}

void Enemy::loadDirection() {
    direction.x = std::cos(degToPi * angle);
    direction.y = -std::sin(degToPi * angle);
}

void Enemy::updateProjectile() {
    for (size_t i = 0; i < laser.size(); i++) {
        // Update laser position based on its direction
        laser[i].move(laserSpeed * laserDirection[i]);

        // Check if the laser is out of bounds
        if (laser[i].getPosition().x < 0 || laser[i].getPosition().x > 1600 ||
            laser[i].getPosition().y < 0 || laser[i].getPosition().y > 900) {
            laser.erase(laser.begin() + i);
            laserDirection.erase(laserDirection.begin() + i);
            --i; // Adjust index after erase
        }
    }
}

void Enemy::updateTimer() {
    if (timer < 12) {
        timer++;
    }
    if (timer == 12 && shooting) {
        timer = 0;
        shoot();
    }
}

void Enemy::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) moveUp = true;
        if (event.key.code == sf::Keyboard::Left) moveLeft = true;
        if (event.key.code == sf::Keyboard::Down) moveDown = true;
        if (event.key.code == sf::Keyboard::Right) moveRight = true;
        if (event.key.code == sf::Keyboard::Enter) {
            shooting = true;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) moveUp = false;
        if (event.key.code == sf::Keyboard::Left) moveLeft = false;
        if (event.key.code == sf::Keyboard::Down) moveDown = false;
        if (event.key.code == sf::Keyboard::Right) moveRight = false;
        if (event.key.code == sf::Keyboard::Enter) {
            shooting = false;
        }
    }
}

void Enemy::update() {
    updateTimer();
    updateProjectile();
    updateMovement();
    sprite.setPosition(position);
}

sf::Sprite Enemy::getSprite() const {
    return sprite;
}

std::vector<sf::Sprite> Enemy::getLasers() const {
    return laser;
}

sf::Vector2f Enemy::getPos() const
{
    return position;
}

void Enemy::updateMovement() {
    if (moveUp) {
        loadDirection();
        position += speed * direction;
    }
    if (moveDown) {
        loadDirection();
        position += -1 * speed * direction;
    }
    if (moveLeft) {
        sprite.rotate(-2);
        angle += 2;
        loadDirection();
    }
    if (moveRight) {
        sprite.rotate(2);
        angle -= 2;
        loadDirection();
    }

    if (!moveUp && !moveDown) {
        position += 0.5f * direction;  // Drift when no keys are pressed
    }

    wrap();
}

void Enemy::wrap() {
    if (position.x > 1600) position.x = 0;
    if (position.y > 900) position.y = 0;
    if (position.x < 0) position.x = 1600;
    if (position.y < 0) position.y = 900;
}

void Enemy::shoot() {
    sf::Sprite Laser;
    Laser.setTexture(laserTexture);
    loadDirection();
    Laser.setScale(0.4, 0.4);
    // Position the laser at the front of the enemy
    Laser.setPosition(sprite.getPosition() + 18.f * direction); // Adjust position based on direction
    laser.push_back(Laser);
    laserDirection.push_back(direction);
}

void Enemy::removeLaser(int index) {
    if (index < laser.size()) {
        laser.erase(laser.begin() + index);  // Remove laser
        laserDirection.erase(laserDirection.begin() + index);  // Remove corresponding direction
    }
}

void Enemy::reduceHealth(int damage)
{
    health -= damage;
}

bool Enemy::isAlive()
{
    return (health > 0) ? true : false;
}


