#include "VerriPG.h"

Game::Game()
        : window(sf::VideoMode(800, 600), "My window"),
          characterScaleX(1.f),
          characterScaleY(1.f)
{
    characterTexture.loadFromFile("./Images/alienspreadsheet.png");
    backgroundTexture.loadFromFile("./Images/fundo.png");
    //enemieTexture.loadFromFile("./Images/transforme.png");

    character.setTexture(characterTexture);
    background.setTexture(backgroundTexture);
    enemie.setTexture(enemieTexture);

    // Ajusta a escala inicial junto com o centro da figura
    /*
    sf::Vector2f centerM(static_cast<float>(characterTexture.getSize().x), static_cast<float>(characterTexture.getSize().y));
    centerM.x = centerM.x / 2;
    centerM.y = centerM.y / 2;
    character.setOrigin(centerM); */
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
    sf::Vector2u textureSize = characterTexture.getSize();
    textureSize.x /= 4;  // Assumindo 4 frames na horizontal
    textureSize.y /= 4;  // Assumindo 4 frames na vertical

    float characterScaleX = 2.f; 
    float characterScaleY = 2.f;
    character.setScale(characterScaleX, characterScaleY);
    sf::Vector2f velocity(0.f, 0.f);
    
    //Movimentação por setas   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // left key is pressed: move our character
        velocity.x = -0.02f;
        frameAtualDireita += velocidadeAnimacao;
        linha =1;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        velocity.x = 0.02f;
        frameAtualEsquerda += velocidadeAnimacao;
        linha=2;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = -std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        velocity.y = -0.02f;
        frameAtualCima += velocidadeAnimacao;
        linha =3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        velocity.y = 0.02f;
        frameAtualBaixo += velocidadeAnimacao;
        linha =0;
    }
     position = character.getPosition();
    
      // Verifica se o personagem está se movendo
        bool isMoving = (velocity.x != 0.f || velocity.y != 0.f);

    // Atualiza a lógica da animação
        if (isMoving) {
            // Calcula o frame atual baseado no tempo ou eventos de teclado
            // Substitua esta lógica com a sua própria animação
            
            if (velocity.x > 0.f) {
                
                if (frameAtualEsquerda > 4) {
                    frameAtualEsquerda = 0.f;
                }
                //Seta qual figura vai aparecer
                character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualEsquerda) * textureSize.x, 2 * textureSize.y, textureSize.x, textureSize.y));
            } else if (velocity.x < 0.f) {
                
                if (frameAtualDireita > 4) {
                    frameAtualDireita = 0.f;
                }
                character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualDireita) * textureSize.x, 1 * textureSize.y, textureSize.x, textureSize.y));
            }

            if (velocity.y < 0.f) {
                
                if (frameAtualCima > 4) {
                    frameAtualCima = 0.f;
                }
                character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualCima) * textureSize.x, 3 * textureSize.y, textureSize.x, textureSize.y));
            } else if (velocity.y > 0.f) {
                
                if (frameAtualBaixo > 4) {
                    frameAtualBaixo = 0.f;
                }
                character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualBaixo) * textureSize.x, 0 * textureSize.y, textureSize.x, textureSize.y));
            }
        } else {
            // Se o personagem não estiver se movendo, exibir um frame parado
            character.setTextureRect(sf::IntRect(0, linha*textureSize.y, textureSize.x, textureSize.y));
        }

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
    float velocidadeMovimento = 100.f;
    character.move(velocity * velocidadeMovimento * 0.016f);  // Multiplica pelo deltaTime
}
void Game::render()
{
    window.clear();
    window.draw(background);
    window.draw(character);
    //window.draw(enemie);
    window.display();
}