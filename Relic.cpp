// include the header file for the Relic class
#include "Relic.h"

// constructor initializes the relic with a texture and starting position
Relic::Relic(const sf::Texture& texture, sf::Vector2f position) {
    sprite.setTexture(texture); // set the texture for the relic's sprite
    sprite.setPosition(position); // set the initial position of the relic
    sprite.setScale(0.05f, 0.05f); // scale the sprite down to 5% of its original size
}

// draws the relic sprite to render window
void Relic::draw(sf::RenderWindow& window) const {
    window.draw(sprite); 
}

// reduces the relic's health by the specified amount
void Relic::takeDamage(int amount) {
    health -= amount; // subtract the damage from the relic's health
    if (health < 0) health = 0; // ensure the health does not drop below zero
}

// checks if the relic is still alive
bool Relic::isAlive() const {
    return health > 0; // return true if health is greater than zero
}

// returns the current health of the relic
int Relic::getHealth() const {
    return health; 
}

// returns the bounding box of the relic's sprite for collision detection
sf::FloatRect Relic::getBounds() const {
    return sprite.getGlobalBounds(); 
}


