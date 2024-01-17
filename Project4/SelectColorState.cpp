#include "SelectColorState.h"

#include <SFML/Window/Event.hpp>

SelectColorState::SelectColorState(std::shared_ptr<GameContext>& context)
    : context(context),
    isColorOneButtonSelected(true),  // Set colorOne as initially selected
    isColorOneButtonPressed(false),
    isColorTwoButtonSelected(false),
    isColorTwoButtonPressed(false),
    isColorThreeButtonSelected(false),
    isColorThreeButtonPressed(false),
    isColorFourButtonSelected(false),
    isColorFourButtonPressed(false),
    isColorFiveButtonSelected(false),
    isColorFiveButtonPressed(false),
    isColorSixButtonSelected(false),
    isColorSixButtonPressed(false),
    isExitButtonSelected(false),
    isExitButtonPressed(false)
{
}

SelectColorState::~SelectColorState()
{
}


void SelectColorState::Init()
{
    //// Set up the background

    //// Add the texture for the snake image
    context->assets->addTexture(SNAKE_IMAGE, "assets/textures/snakeImage.png");
    snakeImageSprite.setTexture(context->assets->getTexture(SNAKE_IMAGE));
    snakeImageSprite.setOrigin(snakeImageSprite.getLocalBounds().width / 2,
        snakeImageSprite.getLocalBounds().height / 2);
    snakeImageSprite.setScale(0.6,0.6);
    snakeImageSprite.setPosition(context->window->getSize().x / 2, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2); //inaltime (cu - e in sus, cu + in jos)

    context->assets->addTexture(NORMAL_BACKGROUND, "assets/textures/normalBackground.jpg");
    background.setTexture(context->assets->getTexture(NORMAL_BACKGROUND));

    //// Set up the background for displaying the selected color
    snakeBackground.setSize(sf::Vector2f(370, 400));
    snakeBackground.setFillColor(context->selectedSnakeColor);
    snakeBackground.setOrigin(snakeBackground.getLocalBounds().width / 2,
        snakeBackground.getLocalBounds().height / 2);
    snakeBackground.setPosition(context->window->getSize().x / 2, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2); //inaltime (cu - e in sus, cu + in jos)

    //// Add the texture for the help image
    context->assets->addTexture(SNAKE_HELP_IMAGE, "assets/textures/snakeHelpImage.jpg");

    //// Add the main font
    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    //// Game Info

     //colorTwo
    colorOne.setFont(context->assets->getFont(MAIN_FONT));
    colorOne.setString("Green Color");
    colorOne.setOrigin(colorOne.getLocalBounds().width / 2,
        colorOne.getLocalBounds().height / 2);
    colorOne.setPosition(context->window->getSize().x / 2 - 400, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 - 150); //inaltime (cu - e in sus, cu + in jos)
    colorOne.setCharacterSize(30);

    //colorTwo
    colorTwo.setFont(context->assets->getFont(MAIN_FONT));
    colorTwo.setString("Pink Color");
    colorTwo.setOrigin(colorTwo.getLocalBounds().width / 2,
        colorTwo.getLocalBounds().height / 2);
    colorTwo.setPosition(context->window->getSize().x / 2 - 400, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 + 0); //inaltime (cu - e in sus, cu + in jos)
    colorTwo.setCharacterSize(30);

    //colorThree
    colorThree.setFont(context->assets->getFont(MAIN_FONT));
    colorThree.setString("Blue Color");
    colorThree.setOrigin(colorThree.getLocalBounds().width / 2,
        colorThree.getLocalBounds().height / 2);
    colorThree.setPosition(context->window->getSize().x / 2 - 400, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 + 150); //inaltime (cu - e in sus, cu + in jos)
    colorThree.setCharacterSize(30);

    //colorFour
    colorFour.setFont(context->assets->getFont(MAIN_FONT));
    colorFour.setString("Black Color");
    colorFour.setOrigin(colorFour.getLocalBounds().width / 2,
        colorFour.getLocalBounds().height / 2);
    colorFour.setPosition(context->window->getSize().x / 2 + 400, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 + -150); //inaltime (cu - e in sus, cu + in jos)
    colorFour.setCharacterSize(30);

    //colorFive
    colorFive.setFont(context->assets->getFont(MAIN_FONT));
    colorFive.setString("Orange Color");
    colorFive.setOrigin(colorFive.getLocalBounds().width / 2,
        colorFive.getLocalBounds().height / 2);
    colorFive.setPosition(context->window->getSize().x / 2 + 400, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 + 0); //inaltime (cu - e in sus, cu + in jos)
    colorFive.setCharacterSize(30);

    //colorSix
    colorSix.setFont(context->assets->getFont(MAIN_FONT));
    colorSix.setString("Purple Color");
    colorSix.setOrigin(colorSix.getLocalBounds().width / 2,
        colorSix.getLocalBounds().height / 2);
    colorSix.setPosition(context->window->getSize().x / 2 + 400, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 + 150); //inaltime (cu - e in sus, cu + in jos)
    colorSix.setCharacterSize(30);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 5 - 180.f,
        context->window->getSize().y / 2 - 310.f);
    exitButton.setCharacterSize(30);
}

void SelectColorState::ProcessInput()
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
                if (isColorOneButtonSelected)
                {
                    isColorOneButtonSelected = false;
                    isColorTwoButtonSelected = true;
                }
                else if (isColorTwoButtonSelected)
                {
                    isColorTwoButtonSelected = false;
                    isColorThreeButtonSelected = true;
                }
                else if (isColorThreeButtonSelected)
                {
                    isColorThreeButtonSelected = false;
                    isColorFourButtonSelected = true;
                }
                else if (isColorFourButtonSelected)
                {
                    isColorFourButtonSelected = false;
                    isColorFiveButtonSelected = true;
                }
                else if (isColorFiveButtonSelected)
                {
                    isColorFiveButtonSelected = false;
                    isColorSixButtonSelected = true;
                }
                else if (isColorSixButtonSelected)
                {
                    isColorSixButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else if (isExitButtonSelected)
                {
                    isExitButtonSelected = false;
                    isColorOneButtonSelected = true;
                }
                break;
            case sf::Keyboard::Up:
                if (isColorOneButtonSelected)
                {
                    isColorOneButtonSelected = false;
                    isExitButtonSelected = true;
                }
                else if (isColorTwoButtonSelected)
                {
                    isColorTwoButtonSelected = false;
                    isColorOneButtonSelected = true;
                }
                else if (isColorThreeButtonSelected)
                {
                    isColorThreeButtonSelected = false;
                    isColorTwoButtonSelected = true;
                }
                else if (isColorFourButtonSelected)
                {
                    isColorFourButtonSelected = false;
                    isColorThreeButtonSelected = true;
                }
                else if (isColorFiveButtonSelected)
                {
                    isColorFiveButtonSelected = false;
                    isColorFourButtonSelected = true;
                }
                else if (isColorSixButtonSelected)
                {
                    isColorSixButtonSelected = false;
                    isColorFiveButtonSelected = true;
                }
                else if (isExitButtonSelected)
                {
                    isExitButtonSelected = false;
                    isColorSixButtonSelected = true;
                }
                break;
            case sf::Keyboard::Return:
                isColorOneButtonPressed = false;
                isColorTwoButtonPressed = false;
                isColorThreeButtonPressed = false;
                isColorFourButtonPressed = false;
                isColorFiveButtonPressed = false;
                isColorSixButtonPressed = false;
                isExitButtonPressed = false;

                if (isColorOneButtonSelected)
                {
                    isColorOneButtonPressed = true;
                }
                else if (isColorTwoButtonSelected)
                {
                    isColorTwoButtonPressed = true;
                }
                else if (isColorThreeButtonSelected)
                {
                    isColorThreeButtonPressed = true;
                }
                else if (isColorFourButtonSelected)
                {
                    isColorFourButtonPressed = true;
                }
                else if (isColorFiveButtonSelected)
                {
                    isColorFiveButtonPressed = true;
                }
                else if (isColorSixButtonSelected)
                {
                    isColorSixButtonPressed = true;
                }
                else if (isExitButtonSelected)
                {
                    isExitButtonPressed = true;
                }
                break;
            default:
                break;
            }
        }
    }
}




void SelectColorState::Update(const sf::Time& deltaTime)
{
    sf::Color selectedColor = sf::Color::Black;
    sf::Color defaultColor = sf::Color::White;

    if (isColorOneButtonSelected)
    {
        colorOne.setFillColor(sf::Color::Green);
        colorTwo.setFillColor(defaultColor);
        colorThree.setFillColor(defaultColor);
        colorFour.setFillColor(defaultColor);
        colorFive.setFillColor(defaultColor);
        colorSix.setFillColor(defaultColor);
        exitButton.setFillColor(defaultColor);
    }
    else if (isColorTwoButtonSelected)
    {
        colorTwo.setFillColor(sf::Color(248, 131, 121));
        colorOne.setFillColor(defaultColor);
        colorThree.setFillColor(defaultColor);
        colorFour.setFillColor(defaultColor);
        colorFive.setFillColor(defaultColor);
        colorSix.setFillColor(defaultColor);
        exitButton.setFillColor(defaultColor);
    }
    else if (isColorThreeButtonSelected)
    {
        colorThree.setFillColor(sf::Color(0, 0, 255));
        colorOne.setFillColor(defaultColor);
        colorTwo.setFillColor(defaultColor);
        colorFour.setFillColor(defaultColor);
        colorFive.setFillColor(defaultColor);
        colorSix.setFillColor(defaultColor);
        exitButton.setFillColor(defaultColor);
    }
    else if (isColorFourButtonSelected)
    {
        colorFour.setFillColor(sf::Color(0, 0, 0));
        colorOne.setFillColor(defaultColor);
        colorTwo.setFillColor(defaultColor);
        colorThree.setFillColor(defaultColor);
        colorFive.setFillColor(defaultColor);
        colorSix.setFillColor(defaultColor);
        exitButton.setFillColor(defaultColor);
    }
    else if (isColorFiveButtonSelected)
    {
        colorFive.setFillColor(sf::Color(255, 165, 0));
        colorOne.setFillColor(defaultColor);
        colorTwo.setFillColor(defaultColor);
        colorThree.setFillColor(defaultColor);
        colorFour.setFillColor(defaultColor);
        colorSix.setFillColor(defaultColor);
        exitButton.setFillColor(defaultColor);
    }
    else if (isColorSixButtonSelected)
    {
        colorSix.setFillColor(sf::Color(87, 0, 246));
        colorOne.setFillColor(defaultColor);
        colorTwo.setFillColor(defaultColor);
        colorThree.setFillColor(defaultColor);
        colorFour.setFillColor(defaultColor);
        colorFive.setFillColor(defaultColor);
        exitButton.setFillColor(defaultColor);
    }
    else if (isExitButtonSelected)
    {
        exitButton.setFillColor(selectedColor);
        colorSix.setFillColor(defaultColor);
        colorOne.setFillColor(defaultColor);
        colorTwo.setFillColor(defaultColor);
        colorThree.setFillColor(defaultColor);
        colorFour.setFillColor(defaultColor);
        colorFive.setFillColor(defaultColor);
        //exitButton.setFillColor(defaultColor);
    }

    sf::Color selectedSnakeColor;

    if (isColorOneButtonPressed)
    {
        // Handle press for colorOne
        sf::Color  a(0,128,0);
        snakeColor.setColor(a);
        snakeBackground.setFillColor(snakeColor.getColor());

    }
    else if (isColorTwoButtonPressed)
    {
        // Handle press for colorTwo
        sf::Color  a(248, 131, 121);
        snakeColor.setColor(a);
        snakeBackground.setFillColor(snakeColor.getColor());
    }
    else if (isColorThreeButtonPressed)
    {
        // Handle press for colorThree
        sf::Color  a(0, 0, 255);
        snakeColor.setColor(a);
        snakeBackground.setFillColor(snakeColor.getColor());
    }
    else if (isColorFourButtonPressed)
    {
        // Handle press for colorFour
        sf::Color  a(0, 0, 0);
        snakeColor.setColor(a);
        snakeBackground.setFillColor(snakeColor.getColor());
    }
    else if (isColorFiveButtonPressed)
    {
        // Handle press for colorFive
        sf::Color  a(255, 165, 0);
        snakeColor.setColor(a);
        snakeBackground.setFillColor(snakeColor.getColor());
    }
    else if (isColorSixButtonPressed)
    {
        // Handle press for colorSix
        sf::Color  a(87, 0, 246);
        snakeColor.setColor(a);
        snakeBackground.setFillColor(snakeColor.getColor());
    }

    else if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }

    context->selectedSnakeColor = snakeColor.getColor();
}


void SelectColorState::Draw()
{
    context->window->draw(this->background);
    context->window->draw(this->snakeBackground);
    context->window->draw(this->snakeImageSprite);
    context->window->draw(colorOne);
    context->window->draw(colorTwo);
    context->window->draw(colorThree);
    context->window->draw(colorFour);
    context->window->draw(colorFive);
    context->window->draw(colorSix);
    context->window->draw(exitButton);
    context->window->display();
}
