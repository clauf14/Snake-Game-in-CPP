#include "HelpState.h"

#include <SFML/Window/Event.hpp>

HelpState::HelpState(std::shared_ptr<GameContext>& context)
    : context(context), isExitButtonSelected(true),
    isExitButtonPressed(false)
{
}

HelpState::~HelpState()
{
}


void HelpState::Init()
{

    this->background.setSize(Vector2f(1280, 720));
    this->background.setFillColor(Color::White);

    context->assets->addTexture(SNAKE_HELP_IMAGE, "assets/textures/snakeHelpImage.jpg");

    snakeImage.setTexture(context->assets->getTexture(SNAKE_HELP_IMAGE));
    snakeImage.setPosition(0, 0);


    context->assets->addFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    // Game Info
    gameInfo.setFont(context->assets->getFont(MAIN_FONT));
    gameInfo.setString("1. Scopul jocului : \n"
        "   - Scopul jocului Snake este sa controlezi un sarpe care se deplaseaza pe ecran pentru a manca mancarea\n si a creste in lungime, evitand coliziunile cu el insusi si peretele.\n"
        "2. Miscarea sarpelui:\n"
        "   - Utilizeaza sagetile directionale 'sageata sus' pentru deplasare in sus, sageata \n jos pentru deplasare in jos\n, sageata stanga pentru deplasare la stanga si sageata dreapta pentru deplasare la dreapta) pentru a \n controla directia sarpelui.\n"
        "3. Colectarea mancarii:\n"
        "   - Pe ecran vor aparea bucati de mancare reprezentate ca un mar.\n"
        "   - Misiunea ta este sa muti sarpele pentru a-l face sa \"manance\" aceste bucati \n de mancare.\n"
        "   - Fiecare bucata de mancare mancata iti va creste lungimea sarpelui cu o unitate.\n"
        "4. Evitarea coliziunilor:\n"
        "   - Trebuie sa eviti sa te ciocnesti de marginile ecranului sau de propria coada.\n"
        "   - Daca capul sarpelui se loveste de o margine sau de coada, jocul se incheie.\n"
        "5. Punctaj:\n"
        "   - Scopul secundar este sa obtii un scor cat mai mare. Fiecare bucata de mancare \n mancata  adauga puncte la scorul tau.\n"
        "   - Scorul tau poate fi comparat cu cel al altor jucatori in mod competitiv.\n"
        "6. Optiuni si variante:\n"
        "   - In functie de versiunea jocului sau platforma pe care o folosesti, pot exista \n variante si optiuni suplimentare, cum ar fi bonusuri\n sau obstacole speciale."")");
    /*gameInfo.setOrigin(gameInfo.getLocalBounds().width / 2,
        gameInfo.getLocalBounds().height / 2);*/
    gameInfo.setPosition(context->window->getSize().x / 2 - 500, //latime (cu - e in stanga, cu + in dreapta)
        context->window->getSize().y / 2 - 320); //inaltime (cu - e in sus, cu + in jos)
    gameInfo.setCharacterSize(16);

    // Exit Button
    exitButton.setFont(context->assets->getFont(MAIN_FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 5 - 180.f ,
        context->window->getSize().y / 2 - 310.f );
    exitButton.setCharacterSize(30);
}

void HelpState::ProcessInput()
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


void HelpState::Update(const sf::Time& deltaTime)
{
    if (isExitButtonSelected)
    {
        exitButton.setFillColor(sf::Color::Black);
    }

    if (isExitButtonPressed)
    {
        context->states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void HelpState::Draw()
{
    context->window->clear(sf::Color::Blue);
    context->window->draw(this->snakeImage);
    context->window->draw(gameInfo);
    context->window->draw(exitButton);
    context->window->display();
}