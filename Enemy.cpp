// include the header file for the Enemy class
#include "Enemy.h"

// constructor initializes the enemy with a texture, position, speed, and type
Enemy::Enemy(const sf::Texture& texture, sf::Vector2f position, float speed, EnemyType type)
    : speed(speed), type(type) { // initialize speed and type
    sprite.setTexture(texture); // set the texture for the enemy's sprite
    sprite.setScale(0.1f, 0.1f); // scale the sprite down to 10% of its original size
    sprite.setPosition(position); // set the initial position of the enemy

    // set the enemy's health based on its type
    // day enemies have 100 hp, while night enemies have 300 hp
    hp = (type == EnemyType::Day) ? 100 : 300;
}

void Enemy::takeDamage(int dmg) {
    hp -= dmg; // subtract the damage from the enemy's health
}

// checks if the enemy is dead
bool Enemy::isDead() const {
    return hp <= 0; // return true if health is zero or less
}

// returns the type of the enemy Day or Night
EnemyType Enemy::getType() const {
    return type; 
}

// updates the enemy's position
void Enemy::update(float dt) {
    sprite.move(0.f, speed * dt); // move the enemy downward based on its speed
}

// draws the enemy sprite in render window
void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite); 
}

// sets a new speed for the enemy
void Enemy::setSpeed(float newSpeed) {
    speed = newSpeed; 
}

// checks if the enemy has moved off the bottom of the screen
bool Enemy::isOffScreen() const {
    return sprite.getPosition().y > 600; 
}

// returns the bounding box of the enemy's sprite for collision detection
sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds(); 
}

