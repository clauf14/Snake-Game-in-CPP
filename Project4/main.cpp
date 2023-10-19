#include <SFML/Graphics.hpp>
#include <iostream>



class Button {
public:
    Button(float x, float y, float width, float height, const std::string& buttonText, sf::Font& font) {
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Blue);

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        // Center the text within the button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
        window.draw(text);
    }

private:
    sf::RectangleShape rectangle;
    sf::Text text;
};


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
        return -1; // Error handling
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Snake Game");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 100);
    text.setStyle(sf::Text::Bold);

    Button newGameButton(150, 200, 200, 50, "New Game", font);

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
        newGameButton.draw(window);
        window.display();
    }

    return 0;
}