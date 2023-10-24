#include "MainMenu.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    : m_context(context), m_isPlayButtonSelected(true),
    m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
    m_isExitButtonPressed(false), m_isLoadGameButtonSelected(false),
    m_isLoadGameButtonPressed(false), m_isSelectColorButtonSelected(false),
    m_isSelectColorButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "Pacifico-Regular.ttf");

    // Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake Game");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
        m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2 - 25.f,
        m_context->m_window->getSize().y / 2 - 130.f);
    m_gameTitle.setCharacterSize(35);

    // Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
    m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 50.f );
    m_playButton.setCharacterSize(20);

    // Load Game Button
    m_loadGameButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_loadGameButton.setString("Load Game");
    m_loadGameButton.setOrigin(m_playButton.getLocalBounds().width / 2,
    m_loadGameButton.getLocalBounds().height / 2);
    m_loadGameButton.setPosition(m_context->m_window->getSize().x / 2 - 35.f,
        m_context->m_window->getSize().y / 2 - 0.f);
    m_loadGameButton.setCharacterSize(20);

    // Select Color Button
    m_selectColorButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_selectColorButton.setString("Select Color");
    m_selectColorButton.setOrigin(m_playButton.getLocalBounds().width / 2,
    m_selectColorButton.getLocalBounds().height / 2);
    m_selectColorButton.setPosition(m_context->m_window->getSize().x / 2 - 40.f,
        m_context->m_window->getSize().y / 2 + 50.f);
    m_selectColorButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
    m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 100.f);
    m_exitButton.setCharacterSize(20);
}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Down:
            {
                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isLoadGameButtonSelected = true;
                }
                else if (m_isLoadGameButtonSelected)
                {
                    m_isLoadGameButtonSelected = false;
                    m_isSelectColorButtonSelected = true;
                }
                else if (m_isSelectColorButtonSelected)
                {
                    m_isSelectColorButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                else
                {
                    m_isExitButtonSelected = false;
                    m_isPlayButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Up:
            {
                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                else if (m_isExitButtonSelected)
                {
                    m_isExitButtonSelected = false;
                    m_isSelectColorButtonSelected = true;
                }
                else if (m_isSelectColorButtonSelected)
                {
                    m_isSelectColorButtonSelected = false;
                    m_isLoadGameButtonSelected = true;
                }
                else
                {
                    m_isLoadGameButtonSelected = false;
                    m_isPlayButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // Handle button presses here, similar to the existing code
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;
                m_isLoadGameButtonPressed = false;
                m_isSelectColorButtonPressed = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else if (m_isExitButtonSelected)
                {
                    m_isExitButtonPressed = true;
                }
                else if (m_isLoadGameButtonSelected)
                {
                    m_isLoadGameButtonPressed = true;
                }
                else if (m_isSelectColorButtonSelected)
                {
                    m_isSelectColorButtonPressed = true;
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


void MainMenu::Update(const sf::Time& deltaTime)
{
    if (m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
        m_loadGameButton.setFillColor(sf::Color::White);
        m_selectColorButton.setFillColor(sf::Color::White);
    }
    else if (m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_playButton.setFillColor(sf::Color::White);
        m_loadGameButton.setFillColor(sf::Color::White);
        m_selectColorButton.setFillColor(sf::Color::White);
    }
    else if (m_isLoadGameButtonSelected)
    {
        m_loadGameButton.setFillColor(sf::Color::Black);
        m_playButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
        m_selectColorButton.setFillColor(sf::Color::White);
    }
    else if (m_isSelectColorButtonSelected)
    {
        m_selectColorButton.setFillColor(sf::Color::Black);
        m_playButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
        m_loadGameButton.setFillColor(sf::Color::White);
    }

    if (m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
}

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_loadGameButton);
    m_context->m_window->draw(m_selectColorButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}