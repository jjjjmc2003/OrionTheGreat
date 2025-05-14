// include sfml headers for graphics and sprite
#include <SFML/Graphics.hpp>

// define an enume for enemy types
enum class EnemyType { Day, Night };

// the Enemy class represents an enemy in the game
// it handles movement, rendering, health, and type-specific behavior
class Enemy {
public:
    // constructor: initializes the enemy with a texture, position, speed, and type
       Enemy(const sf::Texture& texture, sf::Vector2f position, float speed, EnemyType type = EnemyType::Day);

    // updates the enemy's position based on its speed and delta time
     void update(float dt);

    // draws the enemy sprite to the given render window
    void draw(sf::RenderWindow& window) const;

    // returns the bounding box of the enemy's sprite for collision detection
    sf::FloatRect getBounds() const;

    // checks if the enemy has moved off the bottom of the screen
    bool isOffScreen() const;

    // reduces the enemy's health by the specified damage amount
    void takeDamage(int dmg);

    // checks if the enemy is dead  
    bool isDead() const;

    // sets a new speed for the enemy
    void setSpeed(float s);

    // returns the type of the enemy Day or Night
    EnemyType getType() const;

private:
    sf::Sprite sprite; // the enemy's sprite for rendering and collision detection
    float speed;       // the movement speed of the enemy in pixels per second
    int hp;            // the health points of the enemy
    EnemyType type;    // the type of the enemy Day or Night
};

