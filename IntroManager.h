// include to prevent multiple uses of header file
#pragma once

// include necessary sfml headers for graphics and text rendering
#include <SFML/Graphics.hpp>

// the IntroManager class is responsible for managing and displaying the game's introduction sequence
// it handles scrolling text and user input to skip the intro
class IntroManager {
public:
    // constructor initializes the intro manager with a font and window size
    IntroManager(const sf::Font& font, const sf::Vector2u& windowSize);

    // runs the intro sequence, handling text scrolling and user input to skip
    void run(sf::RenderWindow& window);

private:
    sf::Text introText; // the text displayed during the intro sequence
    sf::Text skipPrompt; // a prompt to inform the user how to skip the intro
    float scrollSpeed = 30.f; // the speed at which the intro text scrolls in pixels per second
};


