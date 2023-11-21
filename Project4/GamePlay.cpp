#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>
#include <random>

GamePlay::GamePlay(std::shared_ptr<GameContext>& context)
    : context(context),
    score(0),
    snakeDirection({ 16.f, 0.f }),
    elapsedTime(sf::Time::Zero),
    isPaused(false)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    context->assets->addTexture(GRASS, "assets/textures/grass-minecraft.jpg", true);
    context->assets->addTexture(FOOD, "assets/textures/food.png");
    context->assets->addTexture(WALL, "assets/textures/wall2.png", true);
    context->assets->addTexture(SNAKE, "assets/textures/purple-snake.png");

    grass.setTexture(context->assets->getTexture(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    for (auto& wall : walls)
    {
        wall.setTexture(context->assets->getTexture(WALL));
    }

    walls[0].setTextureRect({ 0, 0, (int)context->window->getSize().x, 16 });
    walls[1].setTextureRect({ 0, 0, (int)context->window->getSize().x, 16 });
    walls[1].setPosition(0, context->window->getSize().y - 16);

    walls[2].setTextureRect({ 0, 0, 16, (int)context->window->getSize().y });
    walls[3].setTextureRect({ 0, 0, 16, (int)context->window->getSize().y });
    walls[3].setPosition(context->window->getSize().x - 16, 0);

    food.setTexture(context->assets->getTexture(FOOD));
    food.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2);

    snake.Init(context->assets->getTexture(SNAKE));

    scoreText.setFont(context->assets->getFont(MAIN_FONT));
    scoreText.setString("Score : " + std::to_string(score));
    scoreText.setPosition(sf::Vector2f(20.f,20.f));
    scoreText.setCharacterSize(18);
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = { 0.f, -16.f };
                break;
            case sf::Keyboard::Down:
                newDirection = { 0.f, 16.f };
                break;
            case sf::Keyboard::Left:
                newDirection = { -16.f, 0.f };
                break;
            case sf::Keyboard::Right:
                newDirection = { 16.f, 0.f };
                break;
            case sf::Keyboard::Escape:
                context->states->Add(std::make_unique<PauseGame>(context));
                break;

            default:
                break;
            }

            if (std::abs(snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(snakeDirection.y) != std::abs(newDirection.y))
            {
                snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(const sf::Time& deltaTime)
{
    if (!isPaused)
    {
        elapsedTime += deltaTime;

        if (elapsedTime.asSeconds() > 0.1)
        {
            for (auto& wall : walls)
            {
                if (snake.IsOn(wall))
                {
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            if (snake.IsOn(food))
            {
                snake.Grow(snakeDirection);

                std::random_device rd;
                std::mt19937 gen(rd());

                std::uniform_int_distribution<int> xDist(16, context->window->getSize().x - 2 * 16);
                std::uniform_int_distribution<int> yDist(16, context->window->getSize().y - 2 * 16);

                int x = xDist(gen);
                int y = yDist(gen);
                  
                food.setPosition(x, y);
                score += 1;
                scoreText.setString("Score : " + std::to_string(score));
            }
            else
            {
                snake.Move(snakeDirection);
            }

            if (snake.IsSelfIntersecting())
            {
                context->states->Add(std::make_unique<GameOver>(context), true);
            }

            elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw()
{
    context->window->clear();
    context->window->draw(grass);

    for (auto& wall : walls)
    {
        context->window->draw(wall);
    }
    context->window->draw(food);
    context->window->draw(snake);
    context->window->draw(scoreText);

    context->window->display();
}

void GamePlay::Pause()
{
    isPaused = true;
}

void GamePlay::Start()
{
    isPaused = false;
}