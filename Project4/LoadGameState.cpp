#include "LoadGameState.h"
#include <fstream> // Include for file operations

LoadGameState::LoadGameState(std::shared_ptr<GameContext>& context)
    : context(context), isExitButtonSelected(true),
    isExitButtonPressed(false), savedScore(0) // Initialize savedScore
{
}

LoadGameState::~LoadGameState()
{
}

void LoadGameState::Init()
{
    this->background.setSize(Vector2f(1280, 720));
    this->background.setFillColor(Color::White);

    context->assets->addTexture(SNAKE_HELP_IMAGE, "assets/textures/snakeHelpImage.jpg");

    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");

    // Read the saved score from the file
    savedScore = ReadSavedScoreFromFile("assets/savedGameScores/scores.txt");

    // Set the text for the Continue button with the saved score
    continueButton.setFont(context->assets->getFont(MAIN_FONT));
    continueButton.setString("Continue: Score " + std::to_string(savedScore));
    continueButton.setOrigin(continueButton.getLocalBounds().width / 2,
        continueButton.getLocalBounds().height / 2);
    continueButton.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2);
    continueButton.setCharacterSize(30);
}

void LoadGameState::ProcessInput()
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
                isExitButtonPressed = false;

                if (isExitButtonSelected)
                {
                    isExitButtonPressed = true;
                }
                else if (isContinueButtonSelected)
                {
                    isContinueButtonPressed = true;
                }
                break;

            case sf::Keyboard::Up:
                isExitButtonSelected = true;
                isContinueButtonSelected = false;
                break;

            case sf::Keyboard::Down:
                isExitButtonSelected = false;
                isContinueButtonSelected = true;
                break;

            default:
                break;
            }
        }
    }
}


void LoadGameState::Update(const sf::Time& deltaTime)
{
    // Assuming there's some logic to change isExitButtonSelected, otherwise, update it accordingly.
    // For example, you might want to set isExitButtonSelected to false after a certain condition is met.
    if (isExitButtonSelected)
    {
        exitButton.setFillColor(sf::Color::Black);
    }
    else
    {
        exitButton.setFillColor(sf::Color::White);
    }

    // Assuming there's some logic to change isContinueButtonSelected, update it accordingly.
    // For example, set isContinueButtonSelected to true when you want the "Continue" button to be pressable.
    if (isContinueButtonSelected)
    {
        continueButton.setFillColor(sf::Color::Black);
    }
    else
    {
        continueButton.setFillColor(sf::Color::White);
    }

    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }

    // Add logic to handle when the "Continue" button is pressed
    if (isContinueButtonPressed)
    {
        // Add your logic here for what should happen when the "Continue" button is pressed.
        // For example, load the saved game state and transition to the gameplay state.
        loadedGame.LoadGameState("assets/savedGameScores/scores.txt");
        isContinueButtonPressed = false;


    }
}




void LoadGameState::Draw()
{
    context->window->clear(sf::Color::Magenta);
    context->window->draw(this->snakeImage);
    context->window->draw(firstSave);
    context->window->draw(exitButton);

    // Draw the Continue button
    context->window->draw(continueButton);

    context->window->display();
}

int LoadGameState::ReadSavedScoreFromFile(const std::string& fileName)
{
   
    int score = 0;
    std::ifstream file(fileName);

    if (file.is_open())
    {
        if (file >> score) // Read the score from the file
        {
            file.close();
            return score;
        }
        else
        {
            std::cerr << "Failed to read the saved score from the file.\n";
        }
    }
    else
    {
        std::cerr << "Unable to open file for reading: " << fileName << std::endl;
    }

    return score;
}



void GamePlay::LoadGameState(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for loading: " << filename << std::endl;
        return;
    }

    // Declare variables to store loaded data
    int loadedScore = 0;
    float loadedDirectionX = 0.f, loadedDirectionY = 0.f;

    // Load relevant game state data directly
    file >> loadedScore >> loadedDirectionX >> loadedDirectionY;

    if (file.fail()) {
        std::cerr << "Failed to read game state from file." << std::endl;
    }
    else {
        std::cout << "Game loaded successfully. Score: " << loadedScore << std::endl;
        std::cout << "Snake Direction: (" << loadedDirectionX << ", " << loadedDirectionY << ")\n";
    }

    // Set the loaded score and snake direction in the current game instance
    setSnakeScore(loadedScore);
    setSnakeDirection(sf::Vector2f(loadedDirectionX, loadedDirectionY));
    // Add a print statement to check if the function is reached
    std::cout << "Reached the end of LoadGameState function." << std::endl;
   
    // Close the file
    file.close();
    context->states->Add(std::make_unique<GamePlay>(context), true);
    

}







