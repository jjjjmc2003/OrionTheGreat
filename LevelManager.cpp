// include the header file for the LevelManager class
#include "LevelManager.h"

// constructor initializes the level manager
LevelManager::LevelManager() {}

// loads the textures required for the levels
bool LevelManager::loadAssets() {
    // load the texture for the day background
    if (!dayTexture.loadFromFile("assets/blueSky.png"))
        return false; // return false if the day texture fails to load

    // load the texture for the night background
    if (!nightTexture.loadFromFile("assets/nightSky.png")) 
        return false; // return false if the night texture fails to load

    return true; // return true if all assets are successfully loaded
}

// updates the current level based on the player's score
void LevelManager::update(int score) {
    // switch to level 2 Night if the score reaches 1500 and the current level is 1
    if (score >= 1500 && currentLevel == 1) {
        currentLevel = 2; // update the current level to 2
    }
}

// checks if the current level is Night
bool LevelManager::isNight() const {
    return currentLevel == 2; // return true if the current level is 2 Night
}

// applies level-specific settings to enemy speed and spawn cooldown
void LevelManager::applyLevelSettings(float& enemySpeed, float& spawnCooldown) {
    // if the current level is night mode, adjust the enemy speed and spawn cooldown
    if (currentLevel == 2) {
        enemySpeed = 250.f;   // increase the enemy speed for night mode
        spawnCooldown = 1.2f; // decrease the spawn cooldown for faster spawns
    }
}

// gets the texture for the current level's background
const sf::Texture& LevelManager::getCurrentBackground() const {
    // return the day texture if the current level is 1, otherwise return the night texture
    return (currentLevel == 1) ? dayTexture : nightTexture;
}

