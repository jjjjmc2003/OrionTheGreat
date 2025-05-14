// include the header file for the Projectile class
#include "Projectile.h"

// constructor initializes the projectile with a starting position
Projectile::Projectile(sf::Vector2f position) {
    shape.setRadius(3.f); // set the radius of the projectile to 3 pixels
    shape.setFillColor(sf::Color::Red); // set the color of the projectile to red 
    shape.setOrigin(shape.getRadius(), shape.getRadius()); // set the origin to the center of the projectile for proper alignment
    shape.setPosition(position); // set the initial position of the projectile
}

// updates the position of the projectile based on its speed and delta time
void Projectile::update(float dt) {
    shape.move(0.f, -speed * dt); // move the projectile up based on its speed
}

// draws the projectile to the given render window
void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(shape); // render the projectile's shape to the window
}

// checks if the projectile has moved off the top of the screen
bool Projectile::isOffScreen() const {
    return shape.getPosition().y < 0; // return true if the projectile's y-position is less than 0
}

// returns the bounding box of the projectile for collision detection
sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds(); 
}


