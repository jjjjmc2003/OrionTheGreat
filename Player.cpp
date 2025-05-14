// include the header file for the Player class
#include "Player.h"

// constructor: initializes the player with a texture and starting position
// parameters:
// - texture: the texture to be applied to the player's sprite
// - position: the initial position of the player in the game window
Player::Player(const sf::Texture& texture, sf::Vector2f position) {
    sprite.setTexture(texture); // set the texture for the player's sprite
    sprite.setScale(0.1f, 0.1f); // scale the sprite down to 10% of its original size
    sprite.setPosition(position); // set the initial position of the player
}

// handles player input for movement and updates the time since the last shot
// parameters:
// - dt: the time elapsed since the last frame (delta time)
void Player::handleInput(float dt) {
    sf::Vector2f velocity(0.f, 0.f); // initialize velocity to zero

    // check for keyboard input and adjust velocity accordingly
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) velocity.y -= speed; // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) velocity.y += speed; // move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) velocity.x -= speed; // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocity.x += speed; // move right

    // move the sprite based on the calculated velocity and delta time
    sprite.move(velocity * dt);

    // update the time since the last shot
    timeSinceLastShot += dt;
}

// updates the player's position and ensures it stays within the screen bounds
// parameters:
// - dt: the time elapsed since the last frame (delta time)
void Player::update(float dt) {
    sf::Vector2f pos = sprite.getPosition(); // get the current position of the sprite
    sf::FloatRect bounds = sprite.getGlobalBounds(); // get the bounding box of the sprite

    // prevent the player from moving off the left or top edges of the screen
    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;

    // prevent the player from moving off the right edge of the screen
    if (pos.x + bounds.width > 800) pos.x = 800 - bounds.width;

    // prevent the player from moving off the bottom edge of the screen
    if (pos.y + bounds.height < 450) pos.y = 450 - bounds.height; // upper limit
    if (pos.y + bounds.height > 600) pos.y = 600 - bounds.height; // lower limit

    // update the sprite's position to stay within bounds
    sprite.setPosition(pos);
}

// creates and returns a new projectile at the player's position
// returns:
// - a Projectile object positioned relative to the player's sprite
Projectile Player::shoot() {
    sf::Vector2f pos = sprite.getPosition(); // get the current position of the sprite
    sf::FloatRect bounds = sprite.getGlobalBounds(); // get the bounding box of the sprite

    // center the projectile horizontally and position it slightly above the sprite
    pos.x += bounds.width / 2.f;
    pos.y += bounds.height * 0.2f; // adjust vertically to appear above the player

    return Projectile(pos); // return a new projectile at the calculated position
}

// draws the player sprite to the given render window
// parameters:
// - window: the sfml render window where the player will be drawn
void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite); // render the sprite to the window
}

// returns the bounding box of the player's sprite for collision detection
// returns:
// - an sf::FloatRect representing the player's bounding box
sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

// returns the current position of the player sprite
// returns:
// - an sf::Vector2f representing the player's position
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

// checks if the player is allowed to shoot based on the cooldown timer
// returns:
// - true if enough time has passed since the last shot, false otherwise
bool Player::canShoot() {
    return timeSinceLastShot >= shootCooldown;
}

// resets the shooting cooldown, allowing the player to shoot immediately
void Player::resetCooldown() {
    timeSinceLastShot = 0.f; // reset the time since the last shot to zero
}


