#include <fstream>

#include "NewGameState.h"

#include <SFML/Window/Event.hpp>

NewGameState::NewGameState(std::shared_ptr<GameContext>& context)
    : context(context),
    isPeacefulButtonSelected(true), isPeacefulButtonPressed(false),
    isHardcoreButtonSelected(false), isHardcoreButtonPressed(false),
    isExitButtonSelected(false), isExitButtonPressed(false),
    textBox(30, Color::White, true)
{
}

NewGameState::~NewGameState()
{
}

void NewGameState::saveNameToFile(const string& name, const string& fileName)
{
    ofstream file(fileName, ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file for saving: " + fileName);
    }

    file << name;
}

void NewGameState::saveNamesToFile(const std::string& name, const std::string& fileName)
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

void NewGameState::saveDifficultyToFile(const std::string& difficulty, const std::string& fileName)
{
    std::ofstream file(fileName, std::ios::binary);
    if (file.is_open())
    {
        file << difficulty;
        file.close();
        std::cout << "Diff saved to file: " << difficulty << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << fileName << std::endl;
    }
}

void NewGameState::Init()
{
    //TextBox
    textBoxFont.loadFromFile("assets/fonts/Pacifico-Regular.ttf");
    textBox.setFont(textBoxFont);
    textBox.setPosition({ 230, 318 });
    textBox.setLimit(true, 20);

    blueColor = sf::Color(102, 178, 255);

    context->assets->addTexture(NEW_GAME_BACKGROUND, "assets/textures/NewGameBackground.jpg");
    background.setTexture(context->assets->getTexture(NEW_GAME_BACKGROUND));

    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");

    // Peaceful Button
    peacefulButton.setFont(context->assets->getFont(MAIN_FONT));
    peacefulButton.setString("Peaceful");
    peacefulButton.setOrigin(peacefulButton.getLocalBounds().width / 2,
        peacefulButton.getLocalBounds().height / 2);
    peacefulButton.setPosition(context->window->getSize().x / 2 + 257.f, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 - 27.f); //inaltime (cu - e in sus, cu + in jos)
    peacefulButton.setCharacterSize(30);

    //Hardcore Button
    hardcoreButton.setFont(context->assets->getFont(MAIN_FONT));
    hardcoreButton.setString("Hardcore");
    hardcoreButton.setOrigin(hardcoreButton.getLocalBounds().width / 2,
        hardcoreButton.getLocalBounds().height / 2);
    hardcoreButton.setPosition(context->window->getSize().x / 2 + 260.f, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 + 118); //inaltime (cu - e in sus, cu + in jos)
    hardcoreButton.setCharacterSize(30);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 5 - 120.f,
        context->window->getSize().y / 2 - 302.f);
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

        //TextBox
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode != ' ')
            {
                textBox.typedOn(event);
            }
        }


        //Upload text from TextBox in file
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*(context->window));
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            if (peacefulButton.getGlobalBounds().contains(mousePosF))
            {
                saveNameToFile(textBox.getText(), "assets/scores/playerName.txt");
            }
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
                    isHardcoreButtonSelected = true;
                }
                else if (isHardcoreButtonSelected)
                {
                    isHardcoreButtonSelected = false;
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
                    isExitButtonSelected = true;
                    isPeacefulButtonSelected = false;
                }
                else if (isHardcoreButtonSelected)
                {
                    isHardcoreButtonSelected = false;
                    isPeacefulButtonSelected = true;
                }
                else
                {
                    isExitButtonSelected = false;
                    isHardcoreButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // Handle button presses here, similar to the existing code
                isPeacefulButtonPressed = false;
                isExitButtonPressed = false;
                isHardcoreButtonPressed = false;

                if (isPeacefulButtonSelected)
                {
                    isPeacefulButtonPressed = true;
                }
                else if (isExitButtonSelected)
                {
                    isExitButtonPressed = true;
                }
                else if (isHardcoreButtonSelected)
                {
                    isHardcoreButtonPressed = true;
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
        hardcoreButton.setFillColor(sf::Color::White);
    }
    else if (isPeacefulButtonSelected)
    {
        peacefulButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(sf::Color::White);
        hardcoreButton.setFillColor(sf::Color::White);
    }
    else if (isHardcoreButtonSelected)
    {
        hardcoreButton.setFillColor(Color::Black);
        exitButton.setFillColor(sf::Color::White);
        peacefulButton.setFillColor(sf::Color::White);
    }

    if (isPeacefulButtonPressed)
    {
        saveDifficultyToFile(peacefulButton.getString(), "assets/scores/difficulty.txt");

        if (textBox.getText().length() == 1)
        {
            saveNameToFile("Anonymous", "assets/scores/playerName.txt");
            saveNamesToFile("Anonymous", "assets/scores/peacefulNames.txt");
        }
        else
        {
            saveNameToFile(textBox.getText(), "assets/scores/playerName.txt");
            saveNamesToFile(textBox.getText(), "assets/scores/peacefulNames.txt");
        }

        context->states->Add(std::make_unique<GamePlay>(context), true);
    }

    if (isHardcoreButtonPressed)
    {
        saveDifficultyToFile(hardcoreButton.getString(), "assets/scores/difficulty.txt");

        if (textBox.getText().length() == 1)
        {
            saveNameToFile("Anonymous", "assets/scores/playerName.txt");
            saveNamesToFile("Anonymous", "assets/scores/hardcoreNames.txt");
        }
        else
        {
            saveNameToFile(textBox.getText(), "assets/scores/playerName.txt");
            saveNamesToFile(textBox.getText(), "assets/scores/hardcoreNames.txt");
        }

        context->states->Add(std::make_unique<GamePlay>(context), true);
    }

    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void NewGameState::Draw()
{
    /*context->window->clear(blueColor);*/
    context->window->draw(background);
    context->window->draw(peacefulButton);
    context->window->draw(hardcoreButton);
    context->window->draw(exitButton);

    //TextBox
    textBox.drawTo(*context->window);

    context->window->display();
}
