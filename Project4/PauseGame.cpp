#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<GameContext>& context)
    : context(context), isSaveButtonPressed(false),
    isSaveButtonSelected(true),
    gamePlay(context) // Correctly initialize the GamePlay object
{
    // Other constructor code, if needed
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

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2 + 100.f);
    exitButton.setCharacterSize(30);
    gamePlay.Init();
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
            case sf::Keyboard::Down:
            {
                if (isSaveButtonSelected)
                {
                    isSaveButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else
                {
                    isExitButtonSelected = false;
                    isSaveButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Up:
            {
                if (isSaveButtonSelected)
                {
                    isSaveButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else
                {
                    isExitButtonSelected = false;
                    isSaveButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                isSaveButtonPressed = false;
                isExitButtonPressed = false;

                if (isSaveButtonSelected)
                {
                    isSaveButtonPressed = true;
                }
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

void PauseGame::Update(const sf::Time& deltaTime)
{
    if (isSaveButtonSelected)
    {
        saveButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(Color::White);
    }
    else
    {
        saveButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(Color::Black);
    }

    if (isSaveButtonPressed)
    {
        // Save the game state here
        gamePlay.SaveGameState("assets/savedGameScores/scores.txt");

        // Now, you can either return to the game or go to the main menu
        // In this example, let's go back to the game
        context->states->Add(std::make_unique<MainMenu>(context), true);
        std::cout << "Game saved successfully." << std::endl;

    }
    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}


void PauseGame::Draw()
{
    context->window->draw(pauseTitle);
    context->window->draw(saveButton);
    context->window->draw(exitButton);
    context->window->display();
}