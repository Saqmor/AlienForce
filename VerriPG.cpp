#include "VerriPG.h"

Game::Game()
        : window(sf::VideoMode(800, 600), "My window"),
          characterScaleX(1.f),
          characterScaleY(1.f)
{
    characterTexture.loadFromFile("./Images/alien (2).png");
    backgroundTexture.loadFromFile("./Images/fundo.png");
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

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (window.pollEvent(event))
    {   
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    sf::Vector2f velocity(0.f, 0.f);

    //Movimentação por setas   
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
    

    //Movimentação Mouse (Melhorar orientação)
    /*
    if (event.type == sf::Event::MouseButtonPressed) {
    // Atualização da posição do objeto pela posição do mouse quando ocorre um clique
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        velocity.x=1.f;
        velocity.y=1.f;
        sf::Vector2f characterPosition = character.getPosition();
        double angle = std::atan2((mousePosition.y-characterPosition.y),(mousePosition.x-characterPosition.x));
        if(mousePosition.x>characterPosition.x)
        velocity.x=1.5*std::cos(std::fabs(angle));
        else
        velocity.x=1.5*std::cos(-std::fabs(angle));
        if(mousePosition.y>characterPosition.y)
        velocity.y=1.5*std::sin(std::fabs(angle));
        else
        velocity.y=1.5*std::sin(-std::fabs(angle));
    } */
    character.move(velocity);

    //std::cout << "Your position on x is: " << position.x << std::endl;}
}
void Game::render()
{
    window.clear();
    window.draw(background);
    window.draw(character);
    //window.draw(enemie);
    window.display();
}