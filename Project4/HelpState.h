#pragma once

#include "MainMenu.hpp"

using namespace sf;

class HelpState : public Engine::State
{
private:
    std::shared_ptr<GameContext> context;
    Text gameInfo;
    Text exitButton;

    RectangleShape background;
    Sprite snakeImage;

    Font font;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

public:
    HelpState(std::shared_ptr<GameContext>& context);
    ~HelpState();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};

