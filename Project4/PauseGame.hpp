#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "LoadGameState.h"

class PauseGame : public Engine::State
{
public:
    PauseGame(std::shared_ptr<GameContext>& context);
    ~PauseGame();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<GameContext> context;
    sf::Text pauseTitle;
    sf::Text saveButton;
    sf::Text helpButton;

    bool isHelpButtonPressed;
    bool isHelpButtonSelected;

    bool isSaveButtonPressed;
    bool isSaveButtonSelected;
};