#pragma once

#include "MainMenu.hpp"


using namespace sf;
class GamePlay;
class LoadGameState : public Engine::State
{
private:
    /*GamePlay gamePlay;*/
    std::shared_ptr<GameContext> context;
    Text firstSave;
    Text exitButton;
    Text continueButton; // Add the new Continue button

    RectangleShape background;
    Sprite snakeImage;

    Font font;

    bool isExitButtonSelected;
    bool isExitButtonPressed;
    bool isContinueButtonSelected;
    bool isContinueButtonPressed;

    int savedScore; // New member variable to store the saved score
    string playerName;
    string* ReadDataFromFile(const std::string& fileName);

public:
    LoadGameState(std::shared_ptr<GameContext>& context);
    ~LoadGameState();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};
