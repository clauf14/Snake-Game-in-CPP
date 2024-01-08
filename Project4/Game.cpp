#include <SFML/Graphics/CircleShape.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"

Game::Game() : context(std::make_shared<GameContext>())
{
    context->window->create(sf::VideoMode(1280, 720), "Snake Game", sf::Style::Close);
    context->states->Add(std::make_unique<MainMenu>(context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    if (!music.openFromFile("assets/sounds/background.ogg"))
        return; // error

    music.play();
    music.setVolume(15);
    music.setLoop(true);

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            context->states->ProcessStateChange();
            context->states->GetCurrent()->ProcessInput();
            context->states->GetCurrent()->Update(TIME_PER_FRAME);
            context->states->GetCurrent()->Draw();
        }
    }
}