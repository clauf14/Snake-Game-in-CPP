#include "SelectColorState.h"

#include <SFML/Window/Event.hpp>

SelectColorState::SelectColorState(std::shared_ptr<GameContext>& context)
    : context(context), isExitButtonSelected(true),
    isExitButtonPressed(false)
{
}

SelectColorState::~SelectColorState()
{
}


void SelectColorState::Init()
{

    this->background.setSize(Vector2f(1280, 720));
    this->background.setFillColor(Color::White);

    context->assets->addTexture(SNAKE_HELP_IMAGE, "assets/textures/snakeHelpImage.jpg");

    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    // Game Info
    colorOne.setFont(context->assets->getFont(MAIN_FONT));
    colorOne.setString("Green Color");
    colorOne.setOrigin(colorOne.getLocalBounds().width / 2,
        colorOne.getLocalBounds().height / 2);
    colorOne.setPosition(context->window->getSize().x / 2, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2); //inaltime (cu - e in sus, cu + in jos)
    colorOne.setCharacterSize(20);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 5 - 180.f,
        context->window->getSize().y / 2 - 310.f);
    exitButton.setCharacterSize(30);
}

void SelectColorState::ProcessInput()
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
            case sf::Keyboard::Return:
            {

                isExitButtonPressed = false;

                if (isExitButtonSelected)
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


void SelectColorState::Update(const sf::Time& deltaTime)
{
    if (isExitButtonSelected)
    {
        exitButton.setFillColor(sf::Color::Black);
    }

    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void SelectColorState::Draw()
{
    context->window->clear(sf::Color::Red);
    context->window->draw(this->snakeImage);
    context->window->draw(colorOne);
    context->window->draw(exitButton);
    context->window->display();
}