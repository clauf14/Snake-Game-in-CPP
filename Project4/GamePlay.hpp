// GamePlay.hpp
#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
public:
    GamePlay();  // Default constructor
    GamePlay(std::shared_ptr<GameContext>& context);
    GamePlay(std::shared_ptr<GameContext>& context, int score, float dirX, float dirY, float posX, float posY);
    ~GamePlay();

    void setSnakeScore(int newScore);
    void setSnakeDirection(const sf::Vector2f& newDirection);
    void SaveGameState(const std::string& filename, int score, float posX, float posY, float dirX, float dirY);
    void LoadGameState(const std::string& filename);

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;

private:
    void initialize();  // A common initialization function

    std::shared_ptr<GameContext> context;
    sf::Sprite grass;
    sf::Sprite food;
    std::array<sf::Sprite, 4> walls;
    Snake snake;

    sf::Sound eatSound;
    sf::Sound gameOverSound;
    sf::SoundBuffer eatBuffer;
    sf::SoundBuffer gameOverBuffer;

    sf::Text scoreText;
    int score;

    sf::Vector2f snakeDirection;
    sf::Time elapsedTime;

    bool isPaused;
};
