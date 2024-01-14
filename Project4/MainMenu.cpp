#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<GameContext>& context)
    : context(context), 
    isPlayButtonSelected(true), isPlayButtonPressed(false), 
    isExitButtonSelected(false), isExitButtonPressed(false), 
    isLoadGameButtonSelected(false), isLoadGameButtonPressed(false), 
    isSelectColorButtonSelected(false), isSelectColorButtonPressed(false), 
    isSelectedLeaderBoardSelected(false), isSelectedLeaderBoardPressed(false),
    isHelpButtonSelected(false), isHelpButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    blueColor = sf::Color(102, 178, 255);

    this->background.setSize(Vector2f(1280, 720));
    this->background.setFillColor(Color::White);

    context->assets->addTexture(SNAKE_IMAGE, "assets/textures/snakeImage.png");

    snakeImageSprite.setTexture(context->assets->getTexture(SNAKE_IMAGE));
    snakeImageSprite.setPosition(550, 20);

    context->assets->addTexture(MENU_BACKGROUND, "assets/textures/menuBackground.jpg");
    menuBackgroundSprite.setTexture(context->assets->getTexture(MENU_BACKGROUND));
    menuBackground.setSize(sf::Vector2f(500, 720));

    snakeBackground.setSize(sf::Vector2f(670, 670));
    snakeBackground.setFillColor(context->selectedSnakeColor);
    cout << snakeColor.getColor().toInteger();
    snakeBackground.setPosition(Vector2f(550, 20));


    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    // Title
    gameTitle.setFont(context->assets->getFont(MAIN_FONT));
    gameTitle.setString("Snake Game");
    gameTitle.setOrigin(gameTitle.getLocalBounds().width / 2,
        gameTitle.getLocalBounds().height / 2);


    gameTitle.setPosition(context->window->getSize().x / 5 - 60.f, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 - 250.f); //inaltime (cu - e in sus, cu + in jos)
    gameTitle.setCharacterSize(50);

    // Play Button
    playButton.setFont(context->assets->getFont(MAIN_FONT));
    playButton.setString("Play");
    playButton.setOrigin(playButton.getLocalBounds().width / 2 + 10.f,
        playButton.getLocalBounds().height / 2);
    playButton.setPosition(context->window->getSize().x / 5,
        context->window->getSize().y / 2 - 100.f);
    playButton.setCharacterSize(30);

    // Load Game Button
    loadGameButton.setFont(context->assets->getFont(MAIN_FONT));
    loadGameButton.setString("Load Game");
    loadGameButton.setOrigin(loadGameButton.getLocalBounds().width / 2,
        loadGameButton.getLocalBounds().height / 2);
    loadGameButton.setPosition(menuBackground.getSize().x / 2,
        context->window->getSize().y / 2 - 30.f);
    loadGameButton.setCharacterSize(30);

    // Select Color Button
    selectColorButton.setFont(context->assets->getFont(MAIN_FONT));
    selectColorButton.setString("Select Color");
    selectColorButton.setOrigin(selectColorButton.getLocalBounds().width / 2,
        selectColorButton.getLocalBounds().height / 2);
    selectColorButton.setPosition(menuBackground.getSize().x / 2,
        context->window->getSize().y / 2 + 40.f);
    selectColorButton.setCharacterSize(30);

    // LeaderBoard Button
    leaderBoardButton.setFont(context->assets->getFont(MAIN_FONT));
    leaderBoardButton.setString("Leader Board");
    leaderBoardButton.setOrigin(leaderBoardButton.getLocalBounds().width / 2,
        leaderBoardButton.getLocalBounds().height / 2);
    leaderBoardButton.setPosition(menuBackground.getSize().x / 2,
        context->window->getSize().y / 2 + 110.f);
    leaderBoardButton.setCharacterSize(30);

    // Help Button
    helpButton.setFont(context->assets->getFont(MAIN_FONT));
    helpButton.setString("Help");
    helpButton.setOrigin(helpButton.getLocalBounds().width / 2,
        helpButton.getLocalBounds().height / 2);
    helpButton.setPosition(menuBackground.getSize().x / 2,
        context->window->getSize().y / 2 + 180.f);
    helpButton.setCharacterSize(30);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(menuBackground.getSize().x / 2,
        menuBackground.getSize().y / 2 + 250.f);
    exitButton.setCharacterSize(30);
}

void MainMenu::ProcessInput()
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
                if (isPlayButtonSelected)
                {
                    isPlayButtonSelected = false;
                    isLoadGameButtonSelected = true;
                }
                else if (isLoadGameButtonSelected)
                {
                    isLoadGameButtonSelected = false;
                    isSelectColorButtonSelected = true;
                }
                else if (isSelectColorButtonSelected)
                {
                    isSelectColorButtonSelected = false;
                    isSelectedLeaderBoardSelected = true;
                }
                else if (isSelectedLeaderBoardSelected)
                {
                    isSelectedLeaderBoardSelected = false;
                    isHelpButtonSelected = true;
                }
                else if (isHelpButtonSelected)
                {
                    isHelpButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else
                {
                    isExitButtonSelected = false;
                    isPlayButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Up:
            {
                if (isPlayButtonSelected)
                {
                    isPlayButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else if (isExitButtonSelected)
                {
                    isExitButtonSelected = false;
                    isHelpButtonSelected = true;
                }
                else if(isHelpButtonSelected)
                {
                    isHelpButtonSelected = false;
                    isSelectedLeaderBoardSelected = true;
                }
                else if (isSelectedLeaderBoardSelected)
                {
                    isSelectedLeaderBoardSelected = false;
                    isSelectColorButtonSelected = true;
                }
                else if (isSelectColorButtonSelected)
                {
                    isSelectColorButtonSelected = false;
                    isLoadGameButtonSelected = true;
                }
                else
                {
                    isLoadGameButtonSelected = false;
                    isPlayButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // Handle button presses here, similar to the existing code
                isPlayButtonPressed = false;
                isExitButtonPressed = false;
                isLoadGameButtonPressed = false;
                isSelectColorButtonPressed = false;
                isSelectedLeaderBoardPressed = false;
                isHelpButtonPressed = false;

                if (isPlayButtonSelected)
                {
                    isPlayButtonPressed = true;
                }
                else if (isExitButtonSelected)
                {
                    isExitButtonPressed = true;
                }
                else if (isLoadGameButtonSelected)
                {
                    isLoadGameButtonPressed = true;
                }
                else if (isSelectColorButtonSelected)
                {
                    isSelectColorButtonPressed = true;
                }
                else if (isSelectedLeaderBoardSelected)
                {
                    isSelectedLeaderBoardPressed = true;
                }
                else if(isHelpButtonSelected)
                {
                    isHelpButtonPressed = true;
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


void MainMenu::Update(const sf::Time& deltaTime)
{
    if (isPlayButtonSelected)
    {
        playButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(sf::Color::White);
        loadGameButton.setFillColor(sf::Color::White);
        selectColorButton.setFillColor(sf::Color::White);
        leaderBoardButton.setFillColor(sf::Color::White);
        helpButton.setFillColor(sf::Color::White);
        
    }
    else if (isExitButtonSelected)
    {
        exitButton.setFillColor(sf::Color::Black);
        playButton.setFillColor(sf::Color::White);
        loadGameButton.setFillColor(sf::Color::White);
        selectColorButton.setFillColor(sf::Color::White);
        leaderBoardButton.setFillColor(sf::Color::White);
        helpButton.setFillColor(sf::Color::White);
    }
    else if (isLoadGameButtonSelected)
    {
        loadGameButton.setFillColor(sf::Color::Black);
        playButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::White);
        selectColorButton.setFillColor(sf::Color::White);
        leaderBoardButton.setFillColor(sf::Color::White);
        helpButton.setFillColor(sf::Color::White);
    }
    else if (isSelectColorButtonSelected)
    {
        selectColorButton.setFillColor(sf::Color::Black);
        leaderBoardButton.setFillColor(sf::Color::White);
        playButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::White);
        loadGameButton.setFillColor(sf::Color::White);
        helpButton.setFillColor(sf::Color::White);
    }
    else if (isSelectedLeaderBoardSelected)
    {
        leaderBoardButton.setFillColor(sf::Color::Black);
        helpButton.setFillColor(sf::Color::White);
        selectColorButton.setFillColor(sf::Color::White);
        playButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::White);
        loadGameButton.setFillColor(sf::Color::White);
    }
    else if (isHelpButtonSelected)
    {
        helpButton.setFillColor(sf::Color::Black);
        selectColorButton.setFillColor(sf::Color::White);
        leaderBoardButton.setFillColor(sf::Color::White);
        playButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::White);
        loadGameButton.setFillColor(sf::Color::White);
        
    }

    if (isPlayButtonPressed)
    {
        context->states->Add(std::make_unique<NewGameState>(context), true);
    }
    else if (isHelpButtonPressed) 
    {
        context->states->Add(std::make_unique<HelpState>(context), true);
    }
    else if (isLoadGameButtonPressed)
    {
        context->states->Add(std::make_unique<LoadGameState>(context), true);
    }
    else if (isSelectColorButtonPressed)
    {
        context->states->Add(std::make_unique<SelectColorState>(context), true);
    }
    else if (isSelectedLeaderBoardPressed)
    {
        context->states->Add(std::make_unique<LeaderBoardState>(context), true);
    }
    else if (isExitButtonPressed)
    {
        context->window->close();
    }
    
    snakeBackground.setFillColor(context->selectedSnakeColor);
}

void MainMenu::Draw()
{
    context->window->draw(this->background);
    context->window->draw(this->menuBackground);
    context->window->draw(this->menuBackgroundSprite);
    context->window->draw(this->snakeBackground);
    context->window->draw(this->snakeImageSprite);
    context->window->draw(gameTitle);
    context->window->draw(playButton);
    context->window->draw(loadGameButton);
    context->window->draw(selectColorButton);
    context->window->draw(helpButton);
    context->window->draw(leaderBoardButton);
    context->window->draw(exitButton);
    context->window->display();
}