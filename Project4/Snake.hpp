#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
public:
    Snake(int snakeLength, float positionX, float positionY);
    ~Snake();

    /*void Init(const sf::Texture& texture, float posX = 16.f, float posY = 16.f);*/
    void Init(const sf::Texture& texture);
    void Move(const sf::Vector2f& direction);
    bool IsOn(const sf::Sprite& other) const;
    void Grow(const sf::Vector2f& direction);
    bool IsSelfIntersecting() const;

    float getPosX();
    float getPosY();
    float getDirX(const sf::Vector2f& direction);
    float getDirY(const sf::Vector2f& direction);
    int getScore(int score);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    float posX;
    float posY;
    std::list<sf::Sprite> body;
    std::list<sf::Sprite>::iterator head;
    std::list<sf::Sprite>::iterator tail;
};