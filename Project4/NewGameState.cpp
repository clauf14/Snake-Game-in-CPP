#include <fstream>

#include "NewGameState.h"

#include <SFML/Window/Event.hpp>

NewGameState::NewGameState(std::shared_ptr<GameContext>& context)
    : context(context),isPeacefulButtonSelected(true),
    isPeacefulButtonPressed(false),
    isExitButtonSelected(false),
    isExitButtonPressed(false), textBox(30, Color::White, true)
{
}

NewGameState::~NewGameState()
{
}

void NewGameState::saveNameToFile(const string& name, const string& fileName)
{
    ofstream file(fileName, ios::app);

    if (file.is_open())
    {
        file << name << endl;
        file.close();
        cout << "Name saved to file: " << name << endl;
    }
    else
    {
        cerr << "Unable to open file for writing: " << name << endl;
    }
}

void NewGameState::Init()
{
    //TextBox
    textBoxFont.loadFromFile("assets/fonts/Pacifico-Regular.ttf");
    textBox.setFont(textBoxFont);
    textBox.setPosition({ 250, 250 });
    textBox.setLimit(true, 30);

    blueColor = sf::Color(102, 178, 255);

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

        //TextBox
       if (event.type == sf::Event::TextEntered)
       {
           textBox.typedOn(event);
       }


       //Upload text from TextBox in file
       if (event.type == sf::Event::MouseButtonPressed)
       {
           sf::Vector2i mousePos = sf::Mouse::getPosition(*(context->window));
           sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

           if (peacefulButton.getGlobalBounds().contains(mousePosF))
           {
               saveNameToFile(textBox.getText(), "assets/scores/score.txt");
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
       saveNameToFile(textBox.getText(), "assets/scores/score.txt");
    }

    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void NewGameState::Draw()
{
    context->window->clear(blueColor);
    context->window->draw(this->snakeImage);
    context->window->draw(peacefulButton);
    context->window->draw(exitButton);

    //TextBox
    textBox.drawTo(*context->window);

    context->window->display();
}