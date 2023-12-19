#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "LoadGameState.h"
#include <fstream> // Include for file operations

class GamePlay;
class PauseGame : public Engine::State
{
public:
    PauseGame(std::shared_ptr<GameContext>& context);
    ~PauseGame();

    void saveZeroScore(const string& outputFile);
    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void saveNamesToFile(const std::string& name, const std::string& fileName);
    void Draw() override;

private:
    /*GamePlay gamePlay;*/
    string* writeTemporaryDataToFinal(const std::string& fromFile, const std::string& toFile);
    std::shared_ptr<GameContext> context;
    sf::Text pauseTitle;
    sf::Text saveButton;
    Text exitButton;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

    bool isSaveButtonPressed;
    bool isSaveButtonSelected;
};