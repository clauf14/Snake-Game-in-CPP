#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<GameContext>& context)
    : context(context)
{
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    // Title
    pauseTitle.setFont(context->assets->getFont(MAIN_FONT));
    pauseTitle.setString("Paused");
    pauseTitle.setOrigin(pauseTitle.getLocalBounds().width / 2,
        pauseTitle.getLocalBounds().height / 2);
    pauseTitle.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2);
}

void PauseGame::ProcessInput()
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
            case sf::Keyboard::Escape:
            {
                context->states->PopCurrent();
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

void PauseGame::Update(const sf::Time& deltaTime)
{
}

void PauseGame::Draw()
{
    context->window->draw(pauseTitle);
    context->window->display();
}