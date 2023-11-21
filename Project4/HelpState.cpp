#include "HelpState.h"

#include <SFML/Window/Event.hpp>

HelpState::HelpState(std::shared_ptr<GameContext>& context)
    : context(context), isExitButtonSelected(true),
    isExitButtonPressed(false)
{
}

HelpState::~HelpState()
{
}


void HelpState::Init()
{

    this->background.setSize(Vector2f(1280, 720));
    this->background.setFillColor(Color::White);

    context->assets->addTexture(SNAKE_HELP_IMAGE, "assets/textures/snakeHelpImage.jpg");

    snakeImage.setTexture(context->assets->getTexture(SNAKE_HELP_IMAGE));
    snakeImage.setPosition(0, 0);


    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    // Game Info
    gameInfo.setFont(context->assets->getFont(MAIN_FONT));
    gameInfo.setString("Game Info");
    gameInfo.setOrigin(gameInfo.getLocalBounds().width / 2,
        gameInfo.getLocalBounds().height / 2);
    gameInfo.setPosition(context->window->getSize().x / 2 , //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2); //inaltime (cu - e in sus, cu + in jos)
    gameInfo.setCharacterSize(20);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 5 - 180.f ,
        context->window->getSize().y / 2 - 310.f );
    exitButton.setCharacterSize(30);
}

void HelpState::ProcessInput()
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


void HelpState::Update(const sf::Time& deltaTime)
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

void HelpState::Draw()
{
    context->window->clear(sf::Color::Blue);
    context->window->draw(this->snakeImage);
    context->window->draw(gameInfo);
    context->window->draw(exitButton);
    context->window->display();
}