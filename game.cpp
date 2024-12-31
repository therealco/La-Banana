#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 400.0f;
const float BANANA_SPEED = 200.0f;

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "La Banana");

    // Load the player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("player.png")) {
        std::cerr << "Error loading player texture" << std::endl;
        return -1;
    }
    sf::Sprite player(playerTexture);
    player.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - playerTexture.getSize().y);

    // Load the banana texture
    sf::Texture bananaTexture;
    if (!bananaTexture.loadFromFile("banana.png")) {
        std::cerr << "Error loading banana texture" << std::endl;
        return -1;
    }
    sf::Sprite banana(bananaTexture);
    banana.setPosition(static_cast<float>(rand() % WINDOW_WIDTH), 0);

    // Load the music
    sf::Music music;
    if (!music.openFromFile("la_banana.ogg")) {
        std::cerr << "Error loading music" << std::endl;
        return -1;
    }
    music.setLoop(true);
    music.play();

    // Clock for delta time
    sf::Clock clock;

    // Game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Move player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0)
        {
            player.move(-PLAYER_SPEED * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x < WINDOW_WIDTH - playerTexture.getSize().x)
        {
            player.move(PLAYER_SPEED * deltaTime, 0);
        }

        // Move banana
        banana.move(0, BANANA_SPEED * deltaTime);

        // Check for collision
        if (banana.getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            // Reset banana position
            banana.setPosition(static_cast<float>(rand() % WINDOW_WIDTH), 0);
        }

        // Check if banana missed
        if (banana.getPosition().y > WINDOW_HEIGHT)
        {
            // Restart the game
            player.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - playerTexture.getSize().y);
            banana.setPosition(static_cast<float>(rand() % WINDOW_WIDTH), 0);
        }

        // Clear the screen
        window.clear();

        // Draw the sprites
        window.draw(player);
        window.draw(banana);

        // Update the window
        window.display();
    }

    return 0;
}
