#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<GameContext>& context)
    : context(context),isSaveButtonPressed(false),
    isSaveButtonSelected(true)
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
        context->window->getSize().y / 2 - 100.f);

    // Save Button
    saveButton.setFont(context->assets->getFont(MAIN_FONT));
    saveButton.setString("Save Game");
    saveButton.setOrigin(saveButton.getLocalBounds().width / 2,
        saveButton.getLocalBounds().height / 2);
    saveButton.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2);
    saveButton.setCharacterSize(30);
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
            case sf::Keyboard::Return:
            {
                isSaveButtonPressed = false;

                if (isSaveButtonSelected)
                {
                    isSaveButtonPressed = true;
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

void PauseGame::Update(const sf::Time& deltaTime)
{
    if (isSaveButtonSelected)
    {
        saveButton.setFillColor(sf::Color::Black);
    }

    if (isSaveButtonPressed)
    {
        context->states->Add(std::make_unique<LoadGameState>(context), true);
    }
}

void PauseGame::Draw()
{
    context->window->draw(pauseTitle);
    context->window->draw(saveButton);
    context->window->display();
}