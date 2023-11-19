#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class GameOver : public Engine::State
{
public:
    GameOver(std::shared_ptr<GameContext>& context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<GameContext> context;
    sf::Text gameOverTitle;
    sf::Text retryButton;
    sf::Text exitButton;

    bool isRetryButtonSelected;
    bool isRetryButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;
};