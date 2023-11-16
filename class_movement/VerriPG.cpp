#include "VerriPG.h"

Game::Game()
        : window(sf::VideoMode(800, 600), "My window"),
          characterScaleX(1.f),
          characterScaleY(1.f)
{
    characterTexture.loadFromFile("C:\\Users\\guicr\\Documents\\Documentos\\codigos_exame\\VerriPG_movement\\Movement\\Images\\alien (2).png");
    backgroundTexture.loadFromFile("C:\\Users\\guicr\\Documents\\Documentos\\codigos_exame\\VerriPG_movement\\Movement\\Images\\fundo.png");
    //enemieTexture.loadFromFile("./Images/transforme.png");

    character.setTexture(characterTexture);
    background.setTexture(backgroundTexture);
    enemie.setTexture(enemieTexture);

    // Ajusta a escala inicial
    sf::Vector2f centerM(static_cast<float>(characterTexture.getSize().x), static_cast<float>(characterTexture.getSize().y));
    centerM.x = centerM.x / 2;
    centerM.y = centerM.y / 2;
    character.setOrigin(centerM);
}

Game::~Game()
{
}

void Game::initializeMenu()
{
    menuFont.loadFromFile("C:\\Users\\guicr\\Desktop\\teste_verriPG\\teste_VerriPG\\ethn.otf");
    menuText.setFont(menuFont);
    menuText.setCharacterSize(24);
    menuText.setOutlineColor(sf::Color::Green);
    menuText.setOutlineThickness(4);
    menuText.setPosition(400, 300);
    menuText.setString("Press 'M' to open the menu");
    options = {"War Game", "Play", "Options", "About", "Quit"};
}


void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();

        // Adicione a verificação para abrir o menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !menuPressed)
        {
            menuPressed = true;
            runMenu();
            menuPressed = false;
        }
    }
}

void Game::runMenu()
{
    while (window.isOpen())
    {
        processMenuEvents();
        drawMenu();
    }
}

void Game::processMenuEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        // Adicione aqui os eventos específicos do menu, como seleção de opção
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !menuPressed){
            if( menuPosition < 4){
                ++menuPosition;
                menuPressed = true;
                texts[menuPosition].setOutlineThickness(4);
                texts[menuPosition - 1].setOutlineThickness(0);
                menuPressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !menuPressed){
            if( menuPosition > 1){
                --pos;
                menuPressed = true;
                texts[menuPosition].setOutlineThickness(4);
                texts[menuPosition + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect){
            theselect = true;
            if( menuPosition == 4){
                window->close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(winclose->getGlobalBounds().contains(mouse_coord)){
                window->close();
            }
        }

        // Use menuPosition para controlar a posição atual no menu
        // e atualize menuText.setString() de acordo com a opção selecionada
    }
}

void Game::drawMenu()
{
    window.clear();
    // Desenhe elementos do menu, como fundo, opções, etc.
    window.draw(menuText);
    window.display();
}


void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    sf::Vector2f velocity(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // left key is pressed: move our character
        velocity.x = -1.f;
        // Ajusta a escala para inverter horizontalmente
        characterScaleX = std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        velocity.x = 1.f;
        // Ajusta a escala para inverter horizontalmente
        characterScaleX = -std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        velocity.y = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        velocity.y = 1.f;
    }

    character.setScale(characterScaleX, characterScaleY);
    position = character.getPosition();
    character.move(velocity);

    std::cout << "Your position on x is: " << position.x << std::endl;
}

void Game::render()
{
    window.clear();
    window.draw(background);
    window.draw(character);
    //window.draw(enemie);
    window.display();
}