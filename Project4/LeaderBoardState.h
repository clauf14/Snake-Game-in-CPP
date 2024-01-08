#pragma once

#include <memory>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"

using namespace std;
using namespace sf;

class LeaderBoardState : public Engine::State
{
public:
    LeaderBoardState(std::shared_ptr<GameContext>& context);
    ~LeaderBoardState();

    void readNamesAndScoresFromFile(const std::string& namesFileName, const std::string& scoresFileName);
    vector<pair<std::string, int>> sortMapByValue(const std::map<std::string, int>& inputMap);

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    shared_ptr<GameContext> context;

    Color blueColor;
    Text peacefulLeaders;
    Text peacefulDif;
    Text hardcoreDif;
    Text exitButton;
    Sprite background;

    map<string, int> scoreAndName;
    std::vector<std::pair<std::string, int>> scoreVector;
    std::vector<std::pair<std::string, int>> sortedVector;

    bool isExitButtonSelected;
    bool isExitButtonPressed;
};


