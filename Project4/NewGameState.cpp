#include "NewGameState.h"

#include <SFML/Window/Event.hpp>

NewGameState::NewGameState(std::shared_ptr<GameContext>& context)
    : context(context),isPeacefulButtonSelected(true),
    isPeacefulButtonPressed(false),
    isExitButtonSelected(false),
    isExitButtonPressed(false)
{
}

NewGameState::~NewGameState()
{
}


void NewGameState::Init()
{

    this->background.setSize(Vector2f(1280, 720));
    this->background.setFillColor(Color::White);

    context->assets->addTexture(SNAKE_HELP_IMAGE, "assets/textures/snakeHelpImage.jpg");

    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    // Game Info
    peacefulButton.setFont(context->assets->getFont(MAIN_FONT));
    peacefulButton.setString("Peaceful  :)");
    peacefulButton.setOrigin(peacefulButton.getLocalBounds().width / 2,
        peacefulButton.getLocalBounds().height / 2);
    peacefulButton.setPosition(context->window->getSize().x / 2, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2); //inaltime (cu - e in sus, cu + in jos)
    peacefulButton.setCharacterSize(30);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 5 - 180.f,
        context->window->getSize().y / 2 - 310.f);
    exitButton.setCharacterSize(30);
}

void NewGameState::ProcessInput()
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
            case sf::Keyboard::Down:
            {
                if (isPeacefulButtonSelected)
                {
                    isPeacefulButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else
                {
                    isExitButtonSelected = false;
                    isPeacefulButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Up:
            {
                if (isPeacefulButtonSelected)
                {
                    isPeacefulButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else
                {
                    isExitButtonSelected = false;
                    isPeacefulButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // Handle button presses here, similar to the existing code
                isPeacefulButtonPressed = false;
                isExitButtonPressed = false;
     
                if (isPeacefulButtonSelected)
                {
                    isPeacefulButtonPressed = true;
                }
                else if (isExitButtonSelected)
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


void NewGameState::Update(const sf::Time& deltaTime)
{
    if (isExitButtonSelected)
    {
        exitButton.setFillColor(sf::Color::Black);
        peacefulButton.setFillColor(sf::Color::White);
    }
    else if (isPeacefulButtonSelected) 
    {
        peacefulButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(sf::Color::White);
    }

    if (isPeacefulButtonPressed)
    {
        context->states->Add(std::make_unique<GamePlay>(context), true);
    }

    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void NewGameState::Draw()
{
    context->window->clear(sf::Color::Blue);
    context->window->draw(this->snakeImage);
    context->window->draw(peacefulButton);
    context->window->draw(exitButton);
    context->window->display();
}