// include the header file for the IntroManager class
#include "IntroManager.h"

// constructor initializes the intro manager with the provided font and window size
IntroManager::IntroManager(const sf::Font& font, const sf::Vector2u& windowSize) {
    // define the story text to be displayed during the intro 
    std::string story =
        "A long time ago, a great war erupted between mankind and evil spirits.\n\n"
        "Led by the 7 Warriors of Chaos, the spirits sought to destroy humanity.\n\n"
        "Humanity stood no chance, until the Great Wizard Orion led a final charge.\n\n"
        "At the Battle of Last Light, he killed the warriors and sealed them in tombs.\n\n"
        "In his final breath, Orion bound his soul to protect the tombs for all time.\n\n"
        "Now, centuries later, the spirits have returned...\n\n"
        "You, Orion  Spirit of light, Defender of Humanity have been awakened\n\n"
        "Protect the graves.\n"
        "Hold the line.\n"
        "Stop the invasion.\n"
        "Save humanity.\n\n"

        "GAME PLAY HOW TO \n"
        "________________\n"
        "Use the arrow keys to move left right up down\n"
        "Press space to shoot\n\n"

        "Note: not all graves need to be defended\n"
        "Only one needs to be defended until the end, but try to protect them all\n\n"

        "CLICK ANYWHERE TO START";

    // configure the intro text
    introText.setFont(font); // set the font for the intro text
    introText.setString(story); // set the story text
    introText.setCharacterSize(24); // set the font size for the intro text
    introText.setFillColor(sf::Color::Yellow); // set the text color to yellow
    introText.setPosition(35, windowSize.y); // position the text offscreen at the bottom

    // configure the skip prompt
    skipPrompt.setFont(font); // set the font for the skip prompt
    skipPrompt.setString("CLICK ANYWHERE TO START"); // set the skip prompt message
    skipPrompt.setCharacterSize(20); // set the font size for the skip prompt
    skipPrompt.setFillColor(sf::Color(255, 255, 255, 150)); // set the color to semi-transparent white
    skipPrompt.setPosition(windowSize.x / 2.f - 130.f, windowSize.y - 50.f); // position the skip prompt near the bottom center
}

// runs the intro sequence, scrolling the text and handling user input to skip
void IntroManager::run(sf::RenderWindow& window) {
    sf::Clock clock; // create a clock to measure time between frames

    // main loop for the intro sequence
    while (window.isOpen()) {
        sf::Event event; // create an event object to handle user input
        // handle window events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) // check if the window close event is triggered
                window.close(); // close the window
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) // check if the enter key is pressed
                return; // exit the intro sequence
            if (event.type == sf::Event::MouseButtonPressed) // check if the mouse is clicked
                return; // exit the intro sequence
        }

        // calculate the time elapsed since the last frame
        float dt = clock.restart().asSeconds();

        // move the intro text upward at the specified scroll speed
        introText.move(0, -scrollSpeed * dt);

        // clear the window and draw the intro text
        window.clear(sf::Color::Black); // clear the screen with a black background
        window.draw(introText); // draw the scrolling intro text
        window.display(); // display the updated frame
    }
}

