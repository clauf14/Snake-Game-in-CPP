#pragma once

#include <memory>
#include <array>
#include <sstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<GameContext>& context);
    GamePlay(std::shared_ptr<GameContext>& context, int score, float dirX, float dirY, float posX, float posY, string difficulty, sf::Color color, int timer);
    ~GamePlay();

    void saveScoresToFile(const int& score, const std::string& fileName);

    void setSnakeScore(int newScore);
    void setSnakeDirection(const sf::Vector2f& newDirection);
    void SaveGameState(const std::string& filename, int score, float posX, float posY, float dirX, float dirY, sf::Color snakeSavedColor, int timer);
    string ReadPlayerName(const std::string& filename);
    string readDifficultyFromFile(const std::string& fileName);

    //Hardcore Diff
    void GenerateRandomObstacles(int numObstacles);
    bool IsWallOverlapping(const sf::Sprite& wall);
    //bool IsWallOverlapping(const sf::Sprite& newWall) const;
    void GenerateFood();
    bool IsFoodOnObstacle(int x, int y);

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
    std::vector<sf::Sprite> obstacles;
    Snake snake;
    sf::Color snakeColor;
    double speed = 0.1;

    sf::Sound eatSound;
    sf::Sound gameOverSound;
    sf::SoundBuffer eatBuffer;
    sf::SoundBuffer gameOverBuffer;

    sf::Text scoreText;
    sf::Text playerName;
    std::string diff;
    int score;

    sf::Vector2f snakeDirection;
    sf::Time elapsedTime;
    float totalElapsedTime;
    sf::Clock timerClock;
    sf::Time timerInterval = sf::seconds(1.0f);
    sf::Text timerText;

    bool isPaused;
};