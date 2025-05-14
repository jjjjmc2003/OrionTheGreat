// Player.h
#pragma once // include guard to prevent multiple inclusions of this header file

// include necessary sfml headers for graphics and vector operations
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h" // include the Projectile class for shooting functionality

// the Player class represents the player character in the game
// it handles movement, shooting, and rendering
class Player {
public:
    // constructor: initializes the player with a texture and starting position
    // parameters:
    // - texture: the texture to be applied to the player's sprite
    // - position: the initial position of the player in the game window
    Player(const sf::Texture& texture, sf::Vector2f position);

    // handles player input (e.g., movement and shooting)
    // parameters:
    // - dt: the time elapsed since the last frame (delta time)
    void handleInput(float dt);

    // updates the player's state (e.g., position and cooldown timers)
    // parameters:
    // - dt: the time elapsed since the last frame (delta time)
    void update(float dt);

    // draws the player sprite to the given render window
    // parameters:
    // - window: the sfml render window where the player will be drawn
    void draw(sf::RenderWindow& window) const;

    // returns the bounding box of the player's sprite for collision detection
    // returns:
    // - an sf::FloatRect representing the player's bounding box
    sf::FloatRect getBounds() const;

    // returns the current position of the player sprite
    // returns:
    // - an sf::Vector2f representing the player's position
    sf::Vector2f getPosition() const;

    // creates and returns a new projectile at the player's position
    // returns:
    // - a Projectile object positioned relative to the player's sprite
    Projectile shoot();

    // checks if the player is allowed to shoot based on the cooldown timer
    // returns:
    // - true if enough time has passed since the last shot, false otherwise
    bool canShoot();

    // resets the shooting cooldown, allowing the player to shoot immediately
    void resetCooldown();

private:
    sf::Sprite sprite; // the player's sprite for rendering and collision detection
    float speed = 200.f; // the movement speed of the player (pixels per second)
    float shootCooldown = 0.3f; // the time (in seconds) between allowed shots
    float timeSinceLastShot = 0.f; // tracks the time since the last shot was fired
};

