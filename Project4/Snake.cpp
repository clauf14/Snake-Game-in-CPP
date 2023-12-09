#include "Snake.hpp"
#include <iostream>

Snake::Snake(int snakeLength, float positionX, float positionY) : body(std::list<sf::Sprite>(snakeLength))
{
    head = --body.end();
    tail = body.begin();
    this->posX = positionX;
    this->posY = positionY;
}



Snake::~Snake()
{
}

float Snake::getPosX()
{
    return head->getPosition().x;
}

float Snake::getPosY()
{
    return head->getPosition().y;
}

float Snake::getDirX(const sf::Vector2f& direction)
{
    return direction.x;
}

float Snake::getDirY(const sf::Vector2f& direction)
{
    return direction.y;
}

int Snake::getScore(int score)
{
    return score;
}


void Snake::Init(const sf::Texture& texture)
{
    float x = posX;
    for (auto& piece : body)
    {
        piece.setTexture(texture);
        piece.setPosition({ x, posY });
        x += 16.f;
    }
}

void Snake::Move(const sf::Vector2f& direction)
{
    tail->setPosition(head->getPosition() + direction);
    /*std::cout << head->getPosition().x << " " <<direction.x << " " << head->getPosition().y << " " << direction.y << std::endl;*/
    head = tail;
    ++tail;

    if (tail == body.end())
    {
        tail = body.begin();
    }
}

bool Snake::IsOn(const sf::Sprite& other) const
{
    return other.getGlobalBounds().intersects(head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(body.begin()->getTexture()));
    newPiece.setPosition(head->getPosition() + direction);

    head = body.insert(++head, newPiece);
}

bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = body.begin(); piece != body.end(); ++piece)
    {
        if (head != piece)
        {
            flag = IsOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& piece : body)
    {
        target.draw(piece);
    }
}