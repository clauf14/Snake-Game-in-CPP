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

    void readNamesAndScoresFromFile(const std::string& namesFileName, const std::string& scoresFileName,
        std::map<std::string, int>& scoreAndName, std::vector<std::pair<std::string, int>>& sortedVector);
    vector<pair<std::string, int>> sortMapByValue(std::map<std::string, int>& inputMap);

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    shared_ptr<GameContext> context;

    Color blueColor;
    Text peacefulLeaders;
    Text hardcoreLeaders;
    Text peacefulDif;
    Text hardcoreDif;
    Text exitButton;
    Sprite background;

    map<string, int> peacefulScoreAndName;
    map<string, int> hardcoreScoreAndName;
    std::vector<std::pair<std::string, int>> peacefulSortedVector;
    std::vector<std::pair<std::string, int>> hardcoreSortedVector;

    bool isExitButtonSelected;
    bool isExitButtonPressed;
};


