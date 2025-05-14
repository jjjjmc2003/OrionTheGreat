#include "Boss.h"

Boss::Boss(const sf::Texture& texture, sf::Vector2f position) {
    // Set up the boss sprite
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.5f, 0.5f); // Scale down the boss sprite if needed

    // Set up the health bar
    healthBar.setSize(sf::Vector2f(300.f, 20.f)); // Width: 300px, Height: 20px
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(position.x, position.y - 30.f); // Position above the boss
}

void Boss::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;

    // Update the health bar size
    float healthPercentage = static_cast<float>(health) / 1000.f;
    healthBar.setSize(sf::Vector2f(300.f * healthPercentage, 20.f));
}

bool Boss::isDead() const {
    return health <= 0;
}

void Boss::draw(sf::RenderWindow& window) const {
    window.draw(sprite); // Draw the boss sprite
    window.draw(healthBar); // Draw the health bar
}

void Boss::update(float dt) {
    // Example: Move the boss downward slowly
    sprite.move(0.f, 50.f * dt);
    healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 30.f);
}
