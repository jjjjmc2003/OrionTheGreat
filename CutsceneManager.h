// include to prevent multiple uses of this header file
#pragma once

// include sfml headers for graphics and text 
#include <SFML/Graphics.hpp>
#include <string>

// the CutsceneManager class is responsible for managing and displaying cutscenes in the game
class CutsceneManager {
public:
    // constructor initializes the cutscene manager with a font and window size
    CutsceneManager(const sf::Font& font, const sf::Vector2u& windowSize);

    // starts the cutscene with the provided script text
    // script is a string containing the text to display during the cutscene
    void start(const std::string& script);

    // runs the cutscene, handling text scrolling and user input to skip
    // window is the sfml render window where the cutscene will be displayed
    void run(sf::RenderWindow& window);

    // checks if the cutscene is currently active
    bool isActive() const;

private:
    sf::Text cutsceneText; // the text displayed during the cutscene
    sf::Vector2u windowSize; // size of the game window
	sf::Text skipPrompt; // the text displayed to prompt the user to skip the cutscene
    bool active = false;   // indicates whether the cutscene is currently active
    float scrollSpeed = 30.f; // the speed the cutscene text scrolls 
};

