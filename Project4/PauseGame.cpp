#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<GameContext>& context)
    : context(context), isSaveButtonPressed(false),
    isSaveButtonSelected(true), isExitButtonPressed(false),
    isExitButtonSelected(false)   // Correctly initialize the GamePlay object
{
    // Other constructor code, if needed
}



PauseGame::~PauseGame()
{
}

void PauseGame::saveZeroScore(const string& outputFile)
{
    std::ofstream outFile(outputFile, std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << outputFile << std::endl;
        return;
    }

    outFile << "0" << std::endl;

    outFile.close();
}

void PauseGame::Init()
{
    // Title
    pauseTitle.setFont(context->assets->getFont(MAIN_FONT));
    pauseTitle.setString("Paused");
    pauseTitle.setOrigin(pauseTitle.getLocalBounds().width / 2,
        pauseTitle.getLocalBounds().height / 2);
    pauseTitle.setPosition(context->window->getSize().x / 2 - 25.f,
        context->window->getSize().y / 2 - 150.f);
    pauseTitle.setCharacterSize(50);

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
        saveZeroScore("assets/scores/scores.txt");
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void PauseGame::saveNamesToFile(const std::string& name, const std::string& fileName)
{
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open())
    {
        file << name << std::endl;
        file.close();
        std::cout << "Name saved to file: " << name << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << fileName << std::endl;
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
    string* data = new string[7];

    // Read the data from the file
    for (int i = 0; i < 7; ++i) {
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