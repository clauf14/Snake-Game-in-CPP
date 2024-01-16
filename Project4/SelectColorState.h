#pragma once

#include "MainMenu.hpp"

using namespace sf;

class SelectColorState : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text colorOne;
    Text colorTwo;
    Text colorThree;
    Text colorFour;
    Text colorFive;
    Text colorSix;
    Text exitButton;

    Sprite background;
    RectangleShape menuBackground;
    RectangleShape snakeBackground;
    SnakeColor snakeColor;
    Sprite snakeImageSprite;

    Font font;


    bool isColorOneButtonSelected;
    bool isColorOneButtonPressed;

    bool isColorTwoButtonSelected;
    bool isColorTwoButtonPressed;

    bool isColorThreeButtonSelected;
    bool isColorThreeButtonPressed;

    bool isColorFourButtonSelected;
    bool isColorFourButtonPressed;

    bool isColorFiveButtonSelected;
    bool isColorFiveButtonPressed;

    bool isColorSixButtonSelected;
    bool isColorSixButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

public:
    SelectColorState(std::shared_ptr<GameContext>& context);
    ~SelectColorState();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};

