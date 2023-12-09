#include "LoadGameState.h"
#include <fstream> // Include for file operations

LoadGameState::LoadGameState(std::shared_ptr<GameContext>& context)
    : context(context), isExitButtonSelected(true),
    isExitButtonPressed(false), isContinueButtonPressed(false),
    isContinueButtonSelected(false) ,savedScore(0), playerName("No save game available") // Initialize savedScore
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

    string* saveData = ReadDataFromFile("assets/savedGameScores/finalScores.txt");
    playerName = saveData[0];
    savedScore = stof(saveData[1]);

    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Back to Menu");
    /*exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2)*/;
    exitButton.setPosition(20.f, 20.f);
    exitButton.setCharacterSize(30);

    // Set the text for the Continue button with the saved score
    continueButton.setFont(context->assets->getFont(MAIN_FONT));
    continueButton.setString("Continue -> Player name: " + playerName + ", Score " + std::to_string(savedScore));
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
        context->states->PopCurrent();
    }

    if (isContinueButtonPressed) 
    {

        string* savedData = ReadDataFromFile("assets/savedGameScores/finalScores.txt");

        int score = stof(savedData[1]);
        float posX = stof(savedData[2]);
        float posY = stof(savedData[3]);
        float dirX = stof(savedData[4]);
        float dirY = stof(savedData[5]);

        context->states->Add(std::make_unique<GamePlay>(context, score , dirX, dirY, posX, posY), true);


    }
}


string* LoadGameState::ReadDataFromFile(const std::string& filename) {

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return nullptr;
    }

    string* data = new string[6];

    // Read the data from the file
    for (int i = 0; i < 6; ++i) {
        file >> data[i];
    }

    // Debugging output
   /* std::cout << "Read Score: " << data[0] << std::endl;
    std::cout << "Read Snake Position: (x= " << data[1] << ",y= " << data[2] << ")" << std::endl;
    std::cout << "Read Snake Direction: (x= " << data[3] << ",y= " << data[4] << ")" << std::endl;*/

    return data;
}

void LoadGameState::Draw()
{
    context->window->clear(sf::Color::Magenta);
    context->window->draw(firstSave);
    context->window->draw(exitButton);
    context->window->draw(continueButton);

    context->window->display();
}



