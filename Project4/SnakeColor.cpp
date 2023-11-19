#include "State.hpp"
#include <SFML/Graphics/Color.hpp>

using namespace sf;

class SnakeColor
{
public:
	SnakeColor() : snakeColor(sf::Color::Green) {

	}

	Color getColor() {
		return snakeColor;
	}

	Color setColor(Color& newColor) {
		snakeColor = newColor;
	}

private:

	Color snakeColor;

};
