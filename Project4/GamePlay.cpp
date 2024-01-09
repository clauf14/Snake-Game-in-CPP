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

// Set the score
void GamePlay::setSnakeScore(int newScore) {
    score = newScore;
}

// Set the snake direction
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
        int x = xDist(gen);
        int y = yDist(gen);

        // Adaugă o bucată de perete la coordonatele generate
        sf::Sprite obstacle(context->assets->getTexture(WALL));
        obstacle.setPosition(x, y);
        obstacles.push_back(obstacle);
    }
}

void GamePlay::GenerateFood()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> xDist(16, context->window->getSize().x - 2 * 16);
    std::uniform_int_distribution<int> yDist(16, context->window->getSize().y - 2 * 16);

    // Generează inițial o poziție pentru mâncare
    int x, y;

    // Verifică dacă poziția generată se află pe un obstacol
    do
    {
        x = xDist(gen);
        y = yDist(gen);
    } while (IsFoodOnObstacle(x, y));

    // Setează poziția pentru mâncare
    food.setPosition(x, y);
}

bool GamePlay::IsFoodOnObstacle(int x, int y)
{
    // Verifică dacă mâncarea se află pe oricare obstacol
    for (const auto& obstacle : obstacles)
    {
        if (obstacle.getGlobalBounds().contains(x, y))
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

    scoreText.setFont(context->assets->getFont(MAIN_FONT));
    scoreText.setString("Score : " + std::to_string(score));
    scoreText.setPosition(sf::Vector2f(20.f, 20.f));
    scoreText.setCharacterSize(20);

    playerName.setFont(context->assets->getFont(MAIN_FONT));
    playerName.setString("Player name: " + ReadPlayerName("assets/scores/playerName.txt"));
    playerName.setPosition(sf::Vector2f(20.f, 50.f));
    playerName.setCharacterSize(20);

    if (diff == "Hardcore")
    {
        GenerateRandomObstacles(30);
    }
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
                        return;  // Ieșiți imediat din funcție dacă șarpele a murit
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

                    if (score % 3 == 0 && score != 0)
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

void GamePlay::saveScoresToFile(const int& score, const std::string& fileName)
{
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open())
    {
        file << score << std::endl;
        file.close();
        std::cout << "Score saved to file: " << score << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << fileName << std::endl;
    }
}

string GamePlay::ReadPlayerName(const std::string& filename)
{
    std::ifstream file("assets/scores/playerName.txt", std::ios::binary);

    string data = "";
    file >> data;

    return data;
}

string GamePlay::readDifficultyFromFile(const std::string& fileName)
{
    std::ifstream file("assets/scores/difficulty.txt", std::ios::binary);

    string diff = "";
    file >> diff;

    return diff;
}

void GamePlay::SaveGameState(const std::string& filename, int score, float posX, float posY, float dirX, float dirY) {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
        return;
    }
    
    std::string fileContent = ReadPlayerName("assets/scores/playerName.txt");
    std::string dif = readDifficultyFromFile("assets/scores/difficulty.txt");

    file << fileContent << '\n';
    file << score << '\n';
    file << posX << '\n';
    file << posY << '\n';
    file << dirX << '\n';
    file << dirY << '\n';
    file << dif << '\n';
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
