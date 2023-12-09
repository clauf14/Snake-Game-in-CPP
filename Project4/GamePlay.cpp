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
    snake(4)
{
    srand(time(nullptr));
}

GamePlay::GamePlay(std::shared_ptr<GameContext>& context, int score, float dirX, float dirY, float posX, float posY)
    : context(context),
    score(score),
    snakeDirection({ dirX, dirY }),
    elapsedTime(sf::Time::Zero),
    isPaused(false),
    snake(score + 4, posX, posY)
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

void GamePlay::Init()
{
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
    scoreText.setCharacterSize(18);
}

void GamePlay::LoadGameState(const std::string& filename) {
    //std::ifstream file(filename, std::ios::binary);
    //if (!file.is_open()) {
    //    std::cerr << "Error opening file for loading: " << filename << std::endl;
    //    return;
    //}

    //// Declare variables to store loaded data
    //int loadedScore = 0;
    //float loadedDirectionX = 0.f, loadedDirectionY = 0.f;

    //// Load relevant game state data directly
    //file >> loadedScore >> loadedDirectionX >> loadedDirectionY;

    //if (file.fail()) {
    //    std::cerr << "Failed to read game state from file." << std::endl;
    //}
    //else {
    //    std::cout << "Game loaded successfully. Score: " << loadedScore << std::endl;
    //    std::cout << "Snake Direction: (" << loadedDirectionX << ", " << loadedDirectionY << ")\n";
    //}

    //// Set the loaded score and snake direction in the current game instance
    //setSnakeScore(loadedScore);
    //setSnakeDirection(sf::Vector2f(loadedDirectionX, loadedDirectionY));
    //// Add a print statement to check if the function is reached
    //std::cout << "Reached the end of LoadGameState function." << std::endl;

    //// Close the file
    //file.close();
    //context->states->Add(std::make_unique<GamePlay>(context, loadedScore, loadedDirectionX, loadedDirectionY, 500.f, 400.f), true);
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
                SaveGameState("assets/savedGameScores/scores.txt", snake.getScore(score), snake.getPosX(), snake.getPosY(),
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

        if (elapsedTime.asSeconds() > 0.1)
        {
            for (auto& wall : walls)
            {
                if (snake.IsOn(wall))
                {
                    gameOverSound.play();
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            if (snake.IsOn(food))
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
            else
            {
                snake.Move(snakeDirection);
            }

            if (snake.IsSelfIntersecting())
            {
                gameOverSound.play();
                context->states->Add(std::make_unique<GameOver>(context), true);
            }

            elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::SaveGameState(const std::string& filename, int score, float posX, float posY, float dirX, float dirY) {
    // Open the file in binary mode for writing
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
        return;
    }

    // Save relevant game state data directly
    file << score << '\n';  // Write score on a new line

    // Save snakeDirection components separately on new lines
    file << posX << '\n';
    file << posY << '\n';
    file << dirX << '\n';
    file << dirY << '\n';

    // Debugging output
    std::cout << "Saved Score: " << score << std::endl;
    std::cout << "Saved Snake Direction: (" << dirX << ", " << dirY << ")" << std::endl;
    std::cout << "Saved Snake Position: (" << posX << ", " << posY << ")" << std::endl;
}

void GamePlay::Draw()
{
    context->window->clear();
    context->window->draw(grass);

    for (auto& wall : walls)
    {
        context->window->draw(wall);
    }
    context->window->draw(food);
    context->window->draw(snake);
    context->window->draw(scoreText);

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
