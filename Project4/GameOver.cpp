#include "GameOver.hpp"
#include "GamePlay.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<GameContext>& context)
    : context(context), isRetryButtonSelected(true),
    isRetryButtonPressed(false), isExitButtonSelected(false),
    isExitButtonPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{

    blueColor = sf::Color(102,178,255);
    // Title
    gameOverTitle.setFont(context->assets->getFont(MAIN_FONT));
    gameOverTitle.setString("Game Over");
    gameOverTitle.setOrigin(gameOverTitle.getLocalBounds().width / 2,
        gameOverTitle.getLocalBounds().height / 2);
    gameOverTitle.setPosition(context->window->getSize().x / 2 - 70.f,
        context->window->getSize().y / 2 - 150.f);
    gameOverTitle.setCharacterSize(50);

    // Play Button
    retryButton.setFont(context->assets->getFont(MAIN_FONT));
    retryButton.setString("Retry");
    retryButton.setOrigin(retryButton.getLocalBounds().width / 2,
        retryButton.getLocalBounds().height / 2);
    retryButton.setPosition(context->window->getSize().x / 2 - 30.f,
        context->window->getSize().y / 2 - 25.f);
    retryButton.setCharacterSize(30);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit To Main Menu");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 2 - 10,
        context->window->getSize().y / 2 + 25.f);
    exitButton.setCharacterSize(30);
}

void GameOver::ProcessInput()
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
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!isRetryButtonSelected)
                {
                    isRetryButtonSelected = true;
                    isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!isExitButtonSelected)
                {
                    isRetryButtonSelected = false;
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                isRetryButtonPressed = false;
                isExitButtonPressed = false;

                if (isRetryButtonSelected)
                {
                    isRetryButtonPressed = true;
                }
                else
                {
                    isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void GameOver::Update(const sf::Time& deltaTime)
{
    if (isRetryButtonSelected)
    {
        retryButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        exitButton.setFillColor(sf::Color::Black);
        retryButton.setFillColor(sf::Color::White);
    }

    if (isRetryButtonPressed)
    {
        context->states->Add(std::make_unique<GamePlay>(context), true);
    }
    else if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void GameOver::Draw()
{
    context->window->clear(blueColor);
    context->window->draw(gameOverTitle);
    context->window->draw(retryButton);
    context->window->draw(exitButton);
    context->window->display();
}