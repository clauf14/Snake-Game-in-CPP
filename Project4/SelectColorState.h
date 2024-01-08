#pragma once

#include "MainMenu.hpp"

using namespace sf;

class SelectColorState : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text colorOne;
    Text colorTwo;
    Text exitButton;

    Sprite background;
    Sprite snakeImage;

    Font font;

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

