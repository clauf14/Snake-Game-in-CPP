#pragma once

#include "MainMenu.hpp"
#include "GamePlay.hpp"

#include "TextBox.cpp"

using namespace sf;

class NewGameState : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text peacefulButton;
    Text exitButton;

    RectangleShape background;
    Sprite snakeImage;

    //TextBox
    TextBox textBox;
    Font textBoxFont;

    sf::Color blueColor;

    Font font;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

    bool isPeacefulButtonSelected;
    bool isPeacefulButtonPressed;


    void initFonts();
    void initButtons();

public:
    NewGameState(std::shared_ptr<GameContext>& context);
    ~NewGameState();

    //Text from TextBox in file
    void saveNameToFile(const std::string& name, const std::string& fileName);

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};



