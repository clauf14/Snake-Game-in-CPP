#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"
#include <fstream>
#include <iostream>

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>
#include <random>

GamePlay::GamePlay(std::shared_ptr<GameContext>& context)
    : context(context),
    score(0),
    snakeDirection({ 16.f, 0.f }),
    elapsedTime(sf::Time::Zero),
    isPaused(false),
    snake(4, 16.f, 16.f)
{
    srand(time(nullptr));
}

GamePlay::GamePlay(std::shared_ptr<GameContext>& context, int score, float dirX, float dirY, float posX, float posY, string difficulty)
    : context(context),
    score(score),
    snakeDirection({ dirX, dirY }),
    elapsedTime(sf::Time::Zero),
    isPaused(false),
    snake(4 + score, posX, posY),
    diff(difficulty)
{
    srand(time(nullptr));
}

void GamePlay::setSnakeScore(int newScore) {
    score = newScore;
}

void GamePlay::setSnakeDirection(const sf::Vector2f& newDirection) {
    snakeDirection = newDirection;
}

GamePlay::~GamePlay()
{
}

void GamePlay::GenerateRandomObstacles(int numObstacles)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> xDist(16, context->window->getSize().x - 2 * 16);
    std::uniform_int_distribution<int> yDist(16, context->window->getSize().y - 2 * 16);

    for (int i = 0; i < numObstacles; ++i)
    {
        sf::Sprite newObstacle(context->assets->getTexture(WALL)); // Aici am mutat declaratia

        int x, y;

        do
        {
            x = xDist(gen);
            y = yDist(gen);

            newObstacle.setPosition(x, y);

        } while (IsWallOverlapping(newObstacle));

        obstacles.push_back(newObstacle);
    }
}

bool GamePlay::IsWallOverlapping(const sf::Sprite& wall)
{
    for (const auto& existingWall : obstacles)
    {
        if (wall.getGlobalBounds().intersects(existingWall.getGlobalBounds()))
        {
            return true;
        }
    }

    return false;
}


void GamePlay::GenerateFood()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> xDist(16, context->window->getSize().x - 2 * 16);
    std::uniform_int_distribution<int> yDist(16, context->window->getSize().y - 2 * 16);

    int x, y;

    do
    {
        x = xDist(gen);
        y = yDist(gen);
    } while (IsFoodOnObstacle(x, y));

    food.setPosition(x, y);
}

bool GamePlay::IsFoodOnObstacle(int x, int y)
{
    sf::FloatRect foodRect(x, y, food.getGlobalBounds().width, food.getGlobalBounds().height);

    for (const auto& obstacle : obstacles)
    {
        sf::FloatRect obstacleRect = obstacle.getGlobalBounds();

        if (foodRect.intersects(obstacleRect))
        {
            return true;
        }
    }

    return false;
}

void GamePlay::Init()
{
    diff = readDifficultyFromFile("assets/scores/difficulty.txt");

    if (!eatBuffer.loadFromFile("assets/sounds/eat.wav"))
    {
        return;
    }

    if (!gameOverBuffer.loadFromFile("assets/sounds/gameover.wav"))
    {
        return;
    }

    eatSound.setBuffer(eatBuffer);
    gameOverSound.setBuffer(gameOverBuffer);

    context->assets->addTexture(GRASS, "assets/textures/grass-minecraft.jpg", true);
    context->assets->addTexture(FOOD, "assets/textures/food.png");
    context->assets->addTexture(WALL, "assets/textures/wall2.png", true);

    if (context->selectedSnakeColor == sf::Color(0, 128, 0))        //green
        context->assets->addTexture(SNAKE, "assets/textures/green-snake.png");

    if (context->selectedSnakeColor == sf::Color(248, 131, 121))    ///pink
        context->assets->addTexture(SNAKE, "assets/textures/pink-snake.png");

    if (context->selectedSnakeColor == sf::Color::Blue)
        context->assets->addTexture(SNAKE, "assets/textures/blue-snake.png");

    if (context->selectedSnakeColor == sf::Color::Black)
        context->assets->addTexture(SNAKE, "assets/textures/black-snake.png");

    if (context->selectedSnakeColor == sf::Color(255, 165, 0))      //orange
        context->assets->addTexture(SNAKE, "assets/textures/orange-snake.png");

    if(context->selectedSnakeColor == sf::Color(87,0,246))
        context->assets->addTexture(SNAKE, "assets/textures/purple-snake.png");
    

    grass.setTexture(context->assets->getTexture(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    for (auto& wall : walls)
    {
        wall.setTexture(context->assets->getTexture(WALL));
    }

    walls[0].setTextureRect({ 0, 0, (int)context->window->getSize().x, 16 });
    walls[1].setTextureRect({ 0, 0, (int)context->window->getSize().x, 16 });
    walls[1].setPosition(0, context->window->getSize().y - 16);

    walls[2].setTextureRect({ 0, 0, 16, (int)context->window->getSize().y });
    walls[3].setTextureRect({ 0, 0, 16, (int)context->window->getSize().y });
    walls[3].setPosition(context->window->getSize().x - 16, 0);

    food.setTexture(context->assets->getTexture(FOOD));
    food.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2);

    snake.Init(context->assets->getTexture(SNAKE));

    if (diff == "Hardcore")
    {
        GenerateRandomObstacles(30);
    }

    scoreText.setFont(context->assets->getFont(MAIN_FONT));
    scoreText.setString("Score : " + std::to_string(score));
    scoreText.setPosition(sf::Vector2f(20.f, 20.f));
    scoreText.setCharacterSize(20);

    playerName.setFont(context->assets->getFont(MAIN_FONT));
    playerName.setString("Player name: " + ReadPlayerName("assets/scores/playerName.txt"));
    playerName.setPosition(sf::Vector2f(20.f, 50.f));
    playerName.setCharacterSize(20);
    
    timerText.setFont(context->assets->getFont(MAIN_FONT));
    timerText.setFillColor(sf::Color::White); 
    timerText.setPosition(context->window->getSize().x - 120.f, 20.f);
    timerText.setCharacterSize(20);

    timerClock.restart();
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = { 0.f, -16.f };
                break;
            case sf::Keyboard::Down:
                newDirection = { 0.f, 16.f };
                break;
            case sf::Keyboard::Left:
                newDirection = { -16.f, 0.f };
                break;
            case sf::Keyboard::Right:
                newDirection = { 16.f, 0.f };
                break;
            case sf::Keyboard::Escape:
                SaveGameState("assets/savedGameScores/temporaryScores.txt", snake.getScore(score), snake.getPosX(), snake.getPosY(),
                    snake.getDirX(snakeDirection), snake.getDirY(snakeDirection));
                context->states->Add(std::make_unique<PauseGame>(context));
                break;

            default:
                break;
            }

            if (std::abs(snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(snakeDirection.y) != std::abs(newDirection.y))
            {
                snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(const sf::Time& deltaTime)
{
    if (!isPaused)
    {
        elapsedTime += deltaTime;

        if (timerClock.getElapsedTime() >= timerInterval)
        {
            timerClock.restart();
            totalElapsedTime += timerInterval.asSeconds();
            //std::cout << "Time: " << totalElapsedTime << " seconds" << std::endl;
        }

        if (elapsedTime.asSeconds() > speed)
        {
            if (diff == "Hardcore")
            {
                for (auto& obstacle : obstacles)
                {
                    if (snake.IsOn(obstacle))
                    {
                        gameOverSound.play();
                        saveScoresToFile(score, "assets/scores/hardcoreScores.txt");
                        context->states->Add(std::make_unique<GameOver>(context), true);
                        return;
                    }
                }
            }

            for (auto& wall : walls)
            {
                if (snake.IsOn(wall))
                {
                    gameOverSound.play();
                    if (diff == "Hardcore")
                    {
                        saveScoresToFile(score, "assets/scores/hardcoreScores.txt");
                    }
                    else
                    {
                        saveScoresToFile(score, "assets/scores/peacefulScores.txt");
                    }
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            if (snake.IsOn(food))
            {
                if (diff == "Hardcore")
                {
                    snake.Grow(snakeDirection);
                    eatSound.play();
                    GenerateFood();
                    score += 1;
                    scoreText.setString("Score : " + std::to_string(score));

                    if (score % 5 == 0 && score != 0)
                    {
                        speed -= 0.005;
                    }
                }
                else
                {
                    snake.Grow(snakeDirection);
                    eatSound.play();

                    std::random_device rd;
                    std::mt19937 gen(rd());

                    std::uniform_int_distribution<int> xDist(16, context->window->getSize().x - 2 * 16);
                    std::uniform_int_distribution<int> yDist(16, context->window->getSize().y - 2 * 16);

                    int x = xDist(gen);
                    int y = yDist(gen);

                    food.setPosition(x, y);
                    score += 1;
                    scoreText.setString("Score : " + std::to_string(score));
                }
            }
            else
            {
                snake.Move(snakeDirection);
            }

            if (snake.IsSelfIntersecting())
            {
                gameOverSound.play();
                if (diff == "Hardcore")
                {
                    saveScoresToFile(score, "assets/scores/hardcoreScores.txt");
                }
                else
                {
                    saveScoresToFile(score, "assets/scores/peacefulScores.txt");
                }
                context->states->Add(std::make_unique<GameOver>(context), true);
            }

            elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw()
{
    context->window->clear();
    context->window->draw(grass);

    if (diff == "Hardcore")
    {
        for (auto& obstacle : obstacles)
        {
            context->window->draw(obstacle);
        }
    }
    for (auto& wall : walls)
    {
        context->window->draw(wall);
    }
    context->window->draw(food);
    context->window->draw(snake);
    context->window->draw(scoreText);
    context->window->draw(playerName);

    timerText.setString("Time: " + std::to_string((int)totalElapsedTime) + "s");
    context->window->draw(timerText);

    context->window->display();
}

void GamePlay::Pause()
{
    isPaused = true;
}

void GamePlay::Start()
{
    isPaused = false;
}

void GamePlay::saveScoresToFile(const int& score, const std::string& fileName)
{
    std::ofstream file(fileName);
    if (file.is_open())
    {
        file << score;
        file.close();
    }
}

string GamePlay::ReadPlayerName(const std::string& filename)
{
    std::ifstream file(filename);
    std::string playerName;
    if (file.is_open())
    {
        file >> playerName;
        file.close();
    }
    return playerName;
}

string GamePlay::readDifficultyFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string difficulty;
    if (file.is_open())
    {
        file >> difficulty;
        file.close();
    }
    return difficulty;
}

void GamePlay::SaveGameState(const std::string& filename, int score, float posX, float posY, float dirX, float dirY)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << score << " " << posX << " " << posY << " " << dirX << " " << dirY;
        file.close();
    }
}
