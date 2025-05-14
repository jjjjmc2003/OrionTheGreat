// include to stop multiple uses of header file
#pragma once

// include necessary sfml headers for graphics
#include <SFML/Graphics.hpp>
#include <vector> // include for using std::vector
#include "Enemy.h" // include the Enemy class for managing enemies
#include "Relic.h" // include the Relic class for collision checks
#include "Projectile.h" // include the Projectile class for collision checks

// the EnemyManager class is responsible for managing all enemies in the game
// it handles spawning, updating, rendering, and interactions with relics and projectiles
class EnemyManager {
public:
    // constructor initializes the enemy manager with a list of enemy textures
    EnemyManager(const std::vector<const sf::Texture*>& textures);

    // updates the state of all enemies, checks for collisions, and handles spawning
    void update(float dt, std::vector<Relic>& relics, std::vector<Projectile>& projectiles, int& score);

    // draws all enemies to the given render window
    void draw(sf::RenderWindow& window);

    // sets a new speed for all enemies
    void setEnemySpeed(float speed);

    // sets the spawn cooldown for enemies
    void setSpawnCooldown(float cooldown);

    // spawns a new enemy at a random horizontal position above the screen
    void spawn();

    // activates or deactivates night mode
    void setNightMode(bool nightMode);

private:
    std::vector<Enemy> enemies; // a vector to store all active enemies
    std::vector<const sf::Texture*> enemyTextures; // a vector of textures for different enemy types
    float spawnCooldown = 2.0f; // the time in seconds between enemy spawns
    float timeSinceLastSpawn = 0.f; // tracks the time elapsed since the last enemy spawn

    float currentSpeed = 100.f; // the current movement speed of the enemies
    bool nightModeActive = false; // flag to indicate whether night mode is active
};


