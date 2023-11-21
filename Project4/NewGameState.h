#pragma once

#include "MainMenu.hpp"
#include "GamePlay.hpp"

using namespace sf;

class NewGameState : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text peacefulButton;
    Text exitButton;

    RectangleShape background;
    Sprite snakeImage;

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

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};



