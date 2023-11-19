#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<GameContext>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;

private:
    std::shared_ptr<GameContext> context;
    sf::Sprite grass;
    sf::Sprite food;
    std::array<sf::Sprite, 4> walls;
    Snake snake;

    sf::Text scoreText;
    int score;

    sf::Vector2f snakeDirection;
    sf::Time elapsedTime;

    bool isPaused;
};