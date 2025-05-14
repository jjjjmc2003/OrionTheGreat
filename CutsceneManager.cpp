// include the header file for the CutsceneManager class
#include "CutsceneManager.h"

// constructor: initializes the cutscene manager with the provided font and window size
CutsceneManager::CutsceneManager(const sf::Font& font, const sf::Vector2u& windowSize)
    : windowSize(windowSize) { // initialize the window size
    // configure the cutscene text
    cutsceneText.setFont(font); // set the font for the cutscene text
    cutsceneText.setCharacterSize(24); // set the font size for the cutscene text
    cutsceneText.setFillColor(sf::Color::Yellow); // set the text color to yellow

    // calculate the text bounds and set the origin to the center for proper alignment
    sf::FloatRect textBounds = cutsceneText.getLocalBounds();
    cutsceneText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

    // position the text above the top edge of the window (offscreen)
    cutsceneText.setPosition(windowSize.x / 2.f, -textBounds.height);

    // configure the skip prompt (optional)
    skipPrompt.setFont(font); // set the font for the skip prompt
    skipPrompt.setCharacterSize(18); // set the font size for the skip prompt
    skipPrompt.setFillColor(sf::Color::Yellow); // set the text color to yellow
    skipPrompt.setString("Press any key to skip"); // set the skip prompt message

    // calculate the skip prompt bounds and set the origin to the center for proper alignment
    sf::FloatRect promptBounds = skipPrompt.getLocalBounds();
    skipPrompt.setOrigin(promptBounds.width / 2.f, promptBounds.height / 2.f);

    // position the skip prompt near the bottom center of the window
    skipPrompt.setPosition(windowSize.x / 2.f, windowSize.y - 50.f);
}

// starts the cutscene by setting the script text and positioning it at the bottom of the screen
// parameters:
// - script: a string containing the text to display during the cutscene
void CutsceneManager::start(const std::string& script) {
    cutsceneText.setString(script); // set the cutscene text to the provided script
    cutsceneText.setPosition(35, windowSize.y); // position the text at the bottom of the screen
    active = true; // mark the cutscene as active
}

// checks if the cutscene is currently active
// returns:
// - true if the cutscene is active, false otherwise
bool CutsceneManager::isActive() const {
    return active;
}

// runs the cutscene, handling text scrolling and user input to skip
// parameters:
// - window: the sfml render window where the cutscene will be displayed
void CutsceneManager::run(sf::RenderWindow& window) {
    sf::Clock clock; // create a clock to measure time between frames

    // main loop for the cutscene
    while (window.isOpen()) {
        sf::Event event; // create an event object to handle user input
        // handle window events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) // check if the window close event is triggered
                window.close(); // close the window
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) // check if the enter key is pressed
                return; // exit the cutscene
            if (event.type == sf::Event::MouseButtonPressed) // check if the mouse is clicked
                return; // exit the cutscene
        }

        // calculate the time elapsed since the last frame
        float dt = clock.restart().asSeconds();

        // move the cutscene text upward at the specified scroll speed
        cutsceneText.move(0, -scrollSpeed * dt);

        // clear the window and draw the cutscene text
        window.clear(sf::Color::Black); // clear the screen with a black background
        window.draw(cutsceneText); // draw the scrolling cutscene text
        window.display(); // display the updated frame
    }
}

