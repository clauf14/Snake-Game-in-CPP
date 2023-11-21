#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "SnakeColor.cpp"
#include "HelpState.h"
#include "NewGameState.h"
#include "LoadGameState.h"
#include "SelectColorState.h"

using namespace sf;

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text gameTitle;
    Text playButton;
    Text loadGameButton;
    Text selectColorButton;
    Text helpButton;
    Text exitButton;

    RectangleShape background;
    RectangleShape menuBackground;
    RectangleShape snakeBackground;
    SnakeColor snakeColor;;
    Sprite snakeImageSprite;

    Font font;

    bool isPlayButtonSelected;
    bool isPlayButtonPressed;

    bool isLoadGameButtonSelected;
    bool isLoadGameButtonPressed;

    bool isSelectColorButtonSelected;
    bool isSelectColorButtonPressed;

    bool isHelpButtonSelected;
    bool isHelpButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

public:
    MainMenu(std::shared_ptr<GameContext>& context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};