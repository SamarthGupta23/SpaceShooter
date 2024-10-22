#include "Spaceship.hpp"

Spaceship::Spaceship()
    : speed(4.f * 14 / 12), angle(90.f), moveUp(false), moveDown(false), moveLeft(false), moveRight(false) {
    // Load spaceship texture
    texture.loadFromFile("C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/images/spaceship.png");
    laserTexture.loadFromFile("C:/Users/samar/OneDrive/Desktop/Game Development/SpaceSamurais/images/laser-3.png");
    sprite.setTexture(texture);
    sprite.setScale(1.5f, 1.5f);

    // Set laser size (make it bigger)
    laserTexture.setSmooth(true); // Optional: if you want smooth textures
    
    health = 100;
    timer = 12;
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    laserSpeed = 10.f * 14 / 12;

    // Set initial position
    sprite.setPosition(100.f, 100.f);
    position = sprite.getPosition();

    // Initialize direction
    loadDirection();
}

void Spaceship::loadDirection() {
    direction.x = std::cos(degToPi * angle);
    direction.y = -std::sin(degToPi * angle);
}

void Spaceship::updateProjectile() {
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

void Spaceship::updateTimer() {
    if (timer < 12) {
        timer++;
    }
    if (timer == 12 && shooting)
    {
        timer = 0;
        shoot();
    }
}

void Spaceship::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) moveUp = true;
        if (event.key.code == sf::Keyboard::A) moveLeft = true;
        if (event.key.code == sf::Keyboard::S) moveDown = true;
        if (event.key.code == sf::Keyboard::D) moveRight = true;
        if (event.key.code == sf::Keyboard::Space) {
            shooting = true;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) moveUp = false;
        if (event.key.code == sf::Keyboard::A) moveLeft = false;
        if (event.key.code == sf::Keyboard::S) moveDown = false;
        if (event.key.code == sf::Keyboard::D) moveRight = false;
        if (event.key.code == sf::Keyboard::Space) {
            shooting = false;;
        }
    }
}

void Spaceship::update() {
    updateTimer();
    updateProjectile();
    updateMovement();
    sprite.setPosition(position);
}

sf::Sprite Spaceship::getSprite() const {
    return sprite;
}

std::vector<sf::Sprite> Spaceship::getLasers() const {
    return laser;
}

sf::Vector2f Spaceship::getPos() const
{
    return position;
}

void Spaceship::updateMovement() {
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

void Spaceship::wrap() {
    if (position.x > 1600) position.x = 0;
    if (position.y > 900) position.y = 0;
    if (position.x < 0) position.x = 1600;
    if (position.y < 0) position.y = 900;
}

void Spaceship::removeLaser(int index) {
    if (index < laser.size()) {
        laser.erase(laser.begin() + index);  // Remove laser
        laserDirection.erase(laserDirection.begin() + index);  // Remove corresponding direction
    }
}

void Spaceship::reduceHealth(int damage)
{
    health -= damage;
}

bool Spaceship::isAlive()
{
    return (health > 0) ? true : false;
}


void Spaceship::shoot() {
    sf::Sprite Laser;
    Laser.setTexture(laserTexture);
    loadDirection();
    Laser.setScale(0.7, 0.7);
    // Position the laser at the front of the spaceship
    Laser.setPosition(sprite.getPosition() + 18.f * direction); // Adjust position based on direction
    laser.push_back(Laser);
    laserDirection.push_back(direction);
}
