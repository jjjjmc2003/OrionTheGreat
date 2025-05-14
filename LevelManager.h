// include to prevent multiple uses of header file
#pragma once

// include for graphics
#include <SFML/Graphics.hpp>

// the LevelManager class is responsible for managing the game's levels
// it handles level transitions, background textures, and level-specific settings
class LevelManager {
public:
    // constructor initializes the level manager
    LevelManager();

    // updates the current level based on the player's score
    void update(int score);

    // checks if the current level is night mode
    bool isNight() const;

    // applies level-specific settings to enemy speed and spawn cooldown
    void applyLevelSettings(float& enemySpeed, float& spawnCooldown);

    // gets the texture for the current level's background
    const sf::Texture& getCurrentBackground() const;

    // loads the textures required for the levels
    bool loadAssets();

private:
    int currentLevel = 1; // the current level of the game 1 = day, 2 = night
    sf::Texture dayTexture; // the texture for the day background
    sf::Texture nightTexture; // the texture for the night background
};


