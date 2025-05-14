#pragma once // include to prevent multiple uses of file

// include necessary sfml headers for graphics and shape rendering
#include <SFML/Graphics.hpp>

// the Projectile class represents a projectile fired by the player
// it handles movement, rendering, and collision detection
class Projectile {
public:
    // constructor initializes the projectile with a starting position
    Projectile(sf::Vector2f position);

    // updates the position of the projectile based on its speed and delta time
    void update(float dt);

    // draws the projectile to the given render window
    void draw(sf::RenderWindow& window) const;

    // checks if the projectile has moved off the top of the screen
    bool isOffScreen() const;

    // returns the bounding box of the projectile for collision detection
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape shape; // the shape of the projectile 
    float speed = 300.f;   // the movement speed of the projectile 
};



