#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "AssetMan.hpp"
#include "StateMan.hpp"

enum AssetID
{
    MAIN_FONT = 0,
    GRASS,
    FOOD,
    WALL,
    SNAKE,
    SNAKE_IMAGE,
    SNAKE_HELP_IMAGE,
    NORMAL_BACKGROUND,
    MENU_BACKGROUND,
    NEW_GAME_BACKGROUND
};

struct GameContext
{
    std::unique_ptr<Engine::AssetMan> assets;
    std::unique_ptr<Engine::StateMan> states;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Color selectedSnakeColor;

    GameContext()
    {
        assets = std::make_unique<Engine::AssetMan>();
        states = std::make_unique<Engine::StateMan>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
public:
    Game();
    ~Game();

    void Run();

private:
    std::shared_ptr<GameContext> context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Music music;
};