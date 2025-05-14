#pragma once // include to prevent multiple uses file

// include for graphics
#include <SFML/Graphics.hpp>

// the Relic class represents the tombstones
class Relic {
public:
    // constructor: initializes the relic with a texture and starting position
    Relic(const sf::Texture& texture, sf::Vector2f position);

    // draws the relic sprite to the given render window
    void draw(sf::RenderWindow& window) const;

    // reduces the relic's health by the specified amount
    void takeDamage(int dmg);

    // returns the current health of the relic
    int getHealth() const;

    // checks if the relic is still alive 
    bool isAlive() const;

    // returns the bounding box of the relic's sprite for collision detection
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite; // the relic's sprite for rendering and collision detection
    int health = 100;  // the health points of the relic (starts at 100)
};



