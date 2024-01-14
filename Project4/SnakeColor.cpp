#include "State.hpp"
#include <SFML/Graphics/Color.hpp>

using namespace sf;

class SnakeColor
{
public:
	SnakeColor() : snakeColor(sf::Color::Blue) {

	}

	Color getColor() {
		return snakeColor;
	}

	void setColor(Color& newColor) {
		snakeColor = newColor;
	}

private:

	Color snakeColor;

};
