#include "LeaderBoardState.h"

LeaderBoardState::LeaderBoardState(std::shared_ptr<GameContext>& context)
    : context(context),
     isExitButtonSelected(true),isExitButtonPressed(false),
    scoreAndName(),
    scoreVector(scoreAndName.begin(), scoreAndName.end())
{
    // Other constructor code, if needed
}

LeaderBoardState::~LeaderBoardState()
{
}

void LeaderBoardState::readNamesAndScoresFromFile(const std::string& namesFileName, const std::string& scoresFileName)
{
    ifstream namesFile(namesFileName);
    ifstream scoresFile(scoresFileName);

    if (!namesFile.is_open() || !scoresFile.is_open()) {
        std::cerr << "One or both files don't exist" << std::endl;
        return;
    }

    std::string nume;
    int score;

    while (namesFile >> nume && scoresFile >> score) {
        scoreAndName[nume] = score;
    }

    if (scoreAndName.empty()) {
        std::cerr << "Atenție: scoreAndName este gol." << std::endl;
    }

    namesFile.close();
    scoresFile.close();

    // Sortează map-ul după scor și salvează rezultatul în sortedVector
    sortedVector = sortMapByValue(scoreAndName);
}

vector<pair<std::string, int>> LeaderBoardState::sortMapByValue(const std::map<std::string, int>& inputMap)
{
    // Convert the map to a vector of pairs
    std::vector<std::pair<std::string, int>> vectorPairs(inputMap.begin(), inputMap.end());

    // Sort the vector based on values (scores) in descending order
    std::sort(vectorPairs.begin(), vectorPairs.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    cout << "Sorted Vector:" << endl;
    for (const auto& entry : vectorPairs) {
        std::cout << "Nume: " << entry.first << ", Scor: " << entry.second << std::endl;
    }

    return vectorPairs;
}

void LeaderBoardState::Init()
{
    // Mapping players informations
    readNamesAndScoresFromFile("assets/scores/names.txt", "assets/scores/scores.txt");
    std::vector<std::pair<std::string, int>> sortedVector = sortMapByValue(scoreAndName);
    cout << endl << "After sorting:" << endl;
    for (const auto& entry : sortedVector) {
        std::cout << "Leader: " << entry.first << ", Score: " << entry.second << std::endl;
    }

    context->assets->addTexture(NORMAL_BACKGROUND, "assets/textures/normalBackground.jpg");
    background.setTexture(context->assets->getTexture(NORMAL_BACKGROUND));

    // Peaceful Difficulty Title
    peacefulDif.setFont(context->assets->getFont(MAIN_FONT));
    peacefulDif.setString("Peaceful Difficulty");
    peacefulDif.setOrigin(peacefulDif.getLocalBounds().width / 2,
        peacefulDif.getLocalBounds().height / 2);
    peacefulDif.setPosition(context->window->getSize().x / 2 - 350.f,
        context->window->getSize().y / 2 - 250.f);

    peacefulLeaders.setFont(context->assets->getFont(MAIN_FONT));
    peacefulLeaders.setCharacterSize(30);
    peacefulLeaders.setFillColor(sf::Color::White);
    peacefulDif.setOrigin(peacefulDif.getLocalBounds().width / 2,
        peacefulDif.getLocalBounds().height / 2);

    // Hardcore Difficulty Title
    hardcoreDif.setFont(context->assets->getFont(MAIN_FONT));
    hardcoreDif.setString("Hardcore Difficulty");
    hardcoreDif.setOrigin(hardcoreDif.getLocalBounds().width / 2,
        hardcoreDif.getLocalBounds().height / 2);
    hardcoreDif.setPosition(context->window->getSize().x / 2 + 350.f,
        context->window->getSize().y / 2 - 250.f);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2 + 230.f);
    exitButton.setCharacterSize(30);
}

void LeaderBoardState::ProcessInput()
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
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                context->states->PopCurrent();
                break;
            }
            case sf::Keyboard::Down:
            {
                if (isExitButtonSelected)
                {
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Up:
            {
                if (isExitButtonSelected)
                {
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                isExitButtonPressed = false;

                if (isExitButtonSelected)
                {
                    isExitButtonPressed = true;
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void LeaderBoardState::Update(const sf::Time& deltaTime)
{
    if (isExitButtonSelected)
    {
        exitButton.setFillColor(Color::Black);
    }
    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void LeaderBoardState::Draw()
{
    context->window->draw(background);
    int i = 1;
    for (const auto& entry : sortedVector)
    {
        if (i <= 10)
        {   
            peacefulLeaders.setString(std::to_string(i) + ". " + entry.first + "   " + std::to_string(entry.second));
            peacefulLeaders.setPosition(160, 130 + i * 40);
            context->window->draw(peacefulLeaders);
        }
        i++;
    }
    context->window->draw(peacefulDif);
    context->window->draw(hardcoreDif);
    context->window->draw(exitButton);
    context->window->display();
}