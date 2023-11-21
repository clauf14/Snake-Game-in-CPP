#pragma once

#include "MainMenu.hpp"

using namespace sf;

class LoadGameState : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text firstSave;
    Text exitButton;

    RectangleShape background;
    Sprite snakeImage;

    Font font;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

public:
    LoadGameState(std::shared_ptr<GameContext>& context);
    ~LoadGameState();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};

