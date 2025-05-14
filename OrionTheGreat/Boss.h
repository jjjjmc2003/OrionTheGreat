#pragma once
#include <SFML/Graphics.hpp>

class Boss {
public:
    // Constructor 
    Boss(const sf::Texture& texture, sf::Vector2f position);

    // Reduces boss's health by damage 
    void takeDamage(int damage);

    // Checks if boss is dead
    bool isDead() const;

    // Draws the boss and health bar
    void draw(sf::RenderWindow& window) const;

    // Updates the boss's position or behavior
    void update(float dt);

private:
    int health = 1000; // Boss's initial health
    sf::Sprite sprite; // Boss's sprite
    sf::RectangleShape healthBar; // Health bar visual
};
