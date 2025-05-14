// include the header file for the EnemyManager class
#include "EnemyManager.h"
#include <cstdlib> // include for rand() function
#include "Projectile.h" // include for projectile-related operations

// constructor initializes the enemy manager with a list of enemy textures
EnemyManager::EnemyManager(const std::vector<const sf::Texture*>& textures)
    : enemyTextures(textures) { // initialize the enemy textures
    currentSpeed = 100.f; // set the default enemy speed
    nightModeActive = false; // night mode is initially inactive
}

// updates the state of all enemies, checks for collisions, and handles spawning
void EnemyManager::update(float dt, std::vector<Relic>& relics, std::vector<Projectile>& projectiles, int& score) {
    // increment the time since the last enemy spawn
    timeSinceLastSpawn += dt;

    // spawn a new enemy if the spawn cooldown has elapsed
    if (timeSinceLastSpawn >= spawnCooldown) {
        spawn(); // spawn a new enemy
        timeSinceLastSpawn = 0.f; // reset the spawn timer
    }

    // update the position of all enemies
    for (auto& enemy : enemies)
        enemy.update(dt);

    // check for collisions between projectiles and enemies
    for (auto p = projectiles.begin(); p != projectiles.end();) {
        bool hit = false; // flag to track if the projectile hits an enemy
        for (auto& enemy : enemies) {
            if (p->getBounds().intersects(enemy.getBounds())) { // check for collision
                hit = true; // mark the projectile as having hit an enemy
                enemy.takeDamage(100); // apply 100 damage to the enemy
                if (enemy.isDead()) { // check if the enemy is dead
                    enemy = enemies.back(); // replace the dead enemy with the last enemy
                    enemies.pop_back(); // remove the last enemy 
                    score += 100; // increase the player's score
                }
                break; // exit the loop after handling the collision
            }
        }
        if (hit)
            p = projectiles.erase(p); // remove the projectile if it hit an enemy
        else
            ++p; // move to the next projectile if no collision occurred
    }

    // check for collisions between enemies and relics
    for (auto& enemy : enemies) {
        for (auto& relic : relics) {
            if (relic.isAlive() && enemy.getBounds().intersects(relic.getBounds())) { // check for collision
                relic.takeDamage(10); // apply 10 damage to the relic
                enemy = enemies.back(); // replace the colliding enemy with the last enemy in the vector
                enemies.pop_back(); // remove the last enemy from the vector
                break; // exit the loop after handling the collision
            }
        }
    }

    // remove enemies that have moved off the bottom of the screen
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return e.isOffScreen(); }), // function to check if an enemy is off-screen
        enemies.end()); // remove all off-screen enemies from the vector
}

// draws all enemies to the given render window
void EnemyManager::draw(sf::RenderWindow& window) {
    for (auto& enemy : enemies) // loop through all enemies
        enemy.draw(window); // draw each enemy
}

// sets a new speed for all enemies
void EnemyManager::setEnemySpeed(float speed) {
    currentSpeed = speed; // update the current speed
    for (auto& enemy : enemies) { // loop through all enemies
        enemy.setSpeed(speed); // update the speed of each enemy
    }
}

// sets the spawn cooldown for enemies
void EnemyManager::setSpawnCooldown(float cooldown) {
    spawnCooldown = cooldown; // update the spawn cooldown
}

// activates or deactivates night mode
void EnemyManager::setNightMode(bool active) {
    nightModeActive = active; // update the night mode status
}

// spawns a new enemy at a random horizontal position above the screen
void EnemyManager::spawn() {
    float x = static_cast<float>(rand() % 750 + 25); // generate a random x-coordinate within the screen bounds
    EnemyType type = (nightModeActive) ? EnemyType::Night : EnemyType::Day; // determine the enemy type based on night mode
    const sf::Texture* tex = (type == EnemyType::Day) ? enemyTextures[0] : enemyTextures[1]; // select the appropriate texture

    // create a new enemy and add it to the vector
    enemies.emplace_back(*tex, sf::Vector2f(x, -50.f), currentSpeed, type);
}

