#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<GameContext>& context)
    : context(context), isSaveButtonPressed(false),
    isSaveButtonSelected(true), isExitButtonPressed(false),
    isExitButtonSelected(false), isHelpButtonPressed(false),
    isHelpButtonSelected(false)// Correctly initialize the GamePlay object
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
        writeTemporaryDataToFinal("assets/savedGameScores/temporaryScores.txt",
            "assets/savedGameScores/finalScores.txt");
        context->states->Add(std::make_unique<MainMenu>(context), true);

    }
    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}



string* PauseGame::writeTemporaryDataToFinal(const std::string& fromFile, const std::string& toFile) {
    std::ifstream file(fromFile, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << fromFile << std::endl;
        return nullptr;
    }

    std::ofstream file1(toFile, std::ios::binary);

    if (!file1.is_open()) {
        std::cerr << "Error opening file for saving: " << toFile << std::endl;
        return nullptr;
    }

    // Allocate memory for an array of 5 elements
    string* data = new string[6];

    // Read the data from the file
    for (int i = 0; i < 6; ++i) {
        file >> data[i];
        file1 << data[i] << '\n';
    }
    
    cout << "Game saved successfully!";

    return data;
}


void PauseGame::Draw()
{
    context->window->draw(pauseTitle);
    context->window->draw(saveButton);
    context->window->draw(exitButton);
    context->window->display();
}