// Include necessary SFML modules for graphics and audio
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Include custom game components
#include "Player.h"
#include "Relic.h"
#include "IntroManager.h"
#include "EnemyManager.h"
#include "Projectile.h"
#include "LevelManager.h"
#include "CutsceneManager.h"

// Include standard library for vector usage
#include <vector>

int main() {
    // Initialize game variables
    int score = 0; // Player's score
    int currentLevel = 1; // Current game level
    bool showStatsPage = false; // Flag to show stats page
    bool statsPageDisplayed = false; // Flag to ensure stats page is displayed only once

    // Create the game window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Orion The Great");

    // Load and configure background music for gameplay
    sf::Music gameplayMusic;
    if (!gameplayMusic.openFromFile("assets/game-background.mp3")) {
        return -1; // Exit if music file fails to load
    }
    gameplayMusic.setLoop(true); // Loop the music indefinitely
    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS

    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("assets/Alkatra-VariableFont_wght.ttf"))
        return -1; // Exit if font file fails to load

    // Initialize the cutscene manager
    CutsceneManager cutscene(font, window.getSize());

    // Load textures for game assets
    sf::Texture playerTexture, relicTexture, slimeTexture, spiritTexture;
    if (!playerTexture.loadFromFile("assets/ghost.png")) return -1; // Player texture
    if (!relicTexture.loadFromFile("assets/tombstone.png")) return -1; // Relic texture
    if (!slimeTexture.loadFromFile("assets/slime.png")) return -1; // Enemy slime texture
    if (!spiritTexture.loadFromFile("assets/evil_spirit.png")) return -1; // Enemy spirit texture

    // Store enemy textures in a vector for the enemy manager
    std::vector<const sf::Texture*> enemyTextures = { &slimeTexture, &spiritTexture };
    EnemyManager enemyManager(enemyTextures); // Initialize enemy manager

    // Initialize the intro manager and play lore music during the intro
    IntroManager intro(font, window.getSize());
    sf::Music loreMusic;
    if (!loreMusic.openFromFile("assets/lore.mp3")) {
        return -1; // Exit if lore music file fails to load
    }
    loreMusic.play(); // Start playing lore music
    intro.run(window); // Run the intro sequence
    loreMusic.stop(); // Stop lore music after intro
    gameplayMusic.play(); // Start gameplay music

    // Initialize the level manager and load level assets
    LevelManager levelManager;
    if (!levelManager.loadAssets()) return -1; // Exit if level assets fail to load

    // Configure the background sprite for the current level
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(levelManager.getCurrentBackground());
    backgroundSprite.setScale(800.f / levelManager.getCurrentBackground().getSize().x,
        600.f / levelManager.getCurrentBackground().getSize().y);
    const sf::Texture* lastBackground = &levelManager.getCurrentBackground(); // Track the last background

    // Initialize the player with the player texture and starting position
    Player player(playerTexture, { 400.f, 400.f });

    // Create a vector of relics with predefined positions
    std::vector<Relic> relics = {
        {relicTexture, {100.f, 500.f}}, {relicTexture, {200.f, 450.f}}, {relicTexture, {300.f, 410.f}},
        {relicTexture, {400.f, 500.f}}, {relicTexture, {500.f, 400.f}}, {relicTexture, {620.f, 500.f}},
        {relicTexture, {650.f, 425.f}}
    };

    // Initialize a vector to store projectiles and a clock for delta time calculations
    std::vector<Projectile> projectiles;
    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Close the window if the close event is triggered
        }

        float dt = clock.restart().asSeconds(); // Calculate delta time

        
        // Trigger cutscene for level 2 when score reaches 1500
        if (score >= 1500 && currentLevel == 1) {
            currentLevel = 2; // Switch to level 2
            gameplayMusic.pause(); // Pause gameplay music
            loreMusic.play(); // Play lore music
            cutscene.start( // Display cutscene text
                "You defeated the spirit army's first wave!!!\n\n"
                "They are now in retreat...\n\n"
                "But you get an odd feeling they'll be back...\n\n"
                "This time, stronger and under the cover of darkness.\n\n"
                "Note: these spirits will take at least 3 shots to kill\n\n"
                "CLICK ANYWHERE TO CONTINUE"
            );
            cutscene.run(window); // Run the cutscene
            loreMusic.stop(); // Stop lore music
            gameplayMusic.play(); // Resume gameplay music
        }

        // Trigger cutscene for level 3 when score reaches 3000
        if (score >= 3000 && currentLevel == 2) {
            currentLevel = 3; // Switch to level 3
            gameplayMusic.pause(); // Pause gameplay music
            loreMusic.play(); // Play lore music
            cutscene.start( // Display cutscene text
                "The spirits can't even get to you at night!!!\n\n"
                "That's why you're Orion the Great.\n\n"
                "You have successfully defended the Tombs!\n\n"
                "Chaos has been stopped. Humanity thanks you.\n\n"
                "CLICK ANYWHERE TO SEE STATS"
            );
            cutscene.run(window); // Run the cutscene
            showStatsPage = true; // Activate stats page after cutscene
        }

      
        if (showStatsPage && !statsPageDisplayed) {
            window.clear(sf::Color::Black); // Clear the window with a black background

            // Display victory text
            sf::Text victoryText;
            victoryText.setFont(font);
            victoryText.setCharacterSize(32);
            victoryText.setFillColor(sf::Color::Yellow);
            victoryText.setString("Victory!");
            victoryText.setPosition(300.f, 100.f);

            // Display graves defended count
            sf::Text gravesText;
            gravesText.setFont(font);
            gravesText.setCharacterSize(24);
            gravesText.setFillColor(sf::Color::White);
            gravesText.setString("Graves Defended: " + std::to_string(relics.size()));
            gravesText.setPosition(300.f, 250.f);

            // Display final score
            sf::Text finalScoreText;
            finalScoreText.setFont(font);
            finalScoreText.setCharacterSize(24);
            finalScoreText.setFillColor(sf::Color::White);
            finalScoreText.setString("Final Score: " + std::to_string(score));
            finalScoreText.setPosition(300.f, 320.f);

            // Display thank you message
            sf::Text thanksText;
            thanksText.setFont(font);
            thanksText.setCharacterSize(20);
            thanksText.setFillColor(sf::Color::Green);
            thanksText.setString("Thank you for saving humanity!");
            thanksText.setPosition(300.f, 400.f);

            // Display exit instructions
            sf::Text exitText;
            exitText.setFont(font);
            exitText.setCharacterSize(20);
            exitText.setFillColor(sf::Color::White);
            exitText.setString("Press ESC to exit.");
            exitText.setPosition(300.f, 500.f);

			window.clear(sf::Color::Black); //draw the background
            // Draw all stats page elements
            window.draw(victoryText);
            window.draw(gravesText);
            window.draw(finalScoreText);
            window.draw(thanksText);
            window.draw(exitText);
            window.display(); // Display the stats page

            // Handle exit events
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close(); // Close the window if ESC is pressed or window is closed
            }

            statsPageDisplayed = true; // Mark stats page as displayed
        }

     
        if (showStatsPage) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    window.close(); // Close the window if ESC is pressed or window is closed
                }
            }
            continue; // Skip normal game updates while stats page is showing
        }

        
        relics.erase(
            std::remove_if(relics.begin(), relics.end(),
                [](const Relic& r) { return !r.isAlive(); }), // Remove relics that are no longer alive
            relics.end()
        );

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.canShoot()) {
            projectiles.push_back(player.shoot()); // Add a new projectile
            player.resetCooldown(); // Reset the player's shooting cooldown
        }

        
        if (relics.empty()) { // Check if all relics are destroyed
            sf::Text loseText("All graves destroyed!\nPress ESC to quit.", font, 32);
            loseText.setFillColor(sf::Color::Red);
            loseText.setPosition(200.f, 250.f);
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed ||
                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                        window.close(); // Close the window if ESC is pressed or window is closed
                }
                window.clear(); // Clear the window
                window.draw(backgroundSprite); // Draw the background
                window.draw(loseText); // Draw the lose text
                window.display(); // Display the lose screen
            }
        }

        // Update the level manager with the current score
        levelManager.update(score);

        // Handle player input and update the player
        player.handleInput(dt);
        player.update(dt);

        const sf::Texture* currentBackground = &levelManager.getCurrentBackground();
        if (currentBackground != lastBackground) { // Check if the background has changed
            backgroundSprite.setTexture(*currentBackground, true); // Update the background texture
            backgroundSprite.setScale(800.f / currentBackground->getSize().x,
                600.f / currentBackground->getSize().y); // Scale the background to fit the window
            lastBackground = currentBackground; // Update the last background reference
        }

        
        for (auto& p : projectiles)
            p.update(dt); // Update each projectile

        projectiles.erase(
            std::remove_if(projectiles.begin(), projectiles.end(),
                [](const Projectile& p) { return p.isOffScreen(); }), // Remove projectiles that are off-screen
            projectiles.end()
        );

      
        float enemySpeed = 200.f; // Default enemy speed
        float spawnCooldown = 2.0f; // Default enemy spawn cooldown
        levelManager.applyLevelSettings(enemySpeed, spawnCooldown); // Adjust settings based on the level

        enemyManager.setEnemySpeed(enemySpeed); // Set enemy speed
        enemyManager.setSpawnCooldown(spawnCooldown); // Set enemy spawn cooldown
        enemyManager.setNightMode(levelManager.isNight()); // Enable night mode if applicable
        enemyManager.update(dt, relics, projectiles, score); // Update enemies

   
        window.clear(); // Clear the window
        window.draw(backgroundSprite); // Draw the background

        // Draw the score
        sf::Text scoreText("Score: " + std::to_string(score), font, 20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10.f, 10.f);
        window.draw(scoreText);

        // Draw each relic and its health
        for (const auto& relic : relics) {
            relic.draw(window); // Draw the relic
            sf::Text hpText("HP: " + std::to_string(relic.getHealth()), font, 14);
            hpText.setFillColor(sf::Color::Red);
            sf::FloatRect bounds = relic.getBounds();
            hpText.setPosition(bounds.left + bounds.width / 2.f - 18.f, bounds.top - 10.f);
            window.draw(hpText); // Draw the relic's health text
        }

        // Draw each projectile
        for (const auto& p : projectiles)
            p.draw(window);

        // Draw the player
        player.draw(window);

        // Draw the enemies
        enemyManager.draw(window);

        // Display everything on the screen
        window.display();
    }

    return 0; // Exit the program
}
