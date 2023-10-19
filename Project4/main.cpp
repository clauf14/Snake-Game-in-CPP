#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(1280, 720)); // Width and height of the button
    background.setFillColor(sf::Color::White); // Button color
    sf::RectangleShape menuBackground;
    menuBackground.setSize(sf::Vector2f(500, 720));
    menuBackground.setFillColor(sf::Color::Magenta);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Load a font
        std::cout << "nu merge"; // Error handling
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Snake Game");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setPosition(370, 60);
    text.setStyle(sf::Text::Bold);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(menuBackground);
        window.draw(text);
        window.display();
    }

    return 0;
}