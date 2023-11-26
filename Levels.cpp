#include "Levels.h"
#include "bossFight.h"

void Game::setValues() {
    window.create(sf::VideoMode(800, 600), "My window");
    characterScaleX = 1.f;
    characterScaleY = 1.f;
    characterTexture.loadFromFile("./Images/chiefsheet.png");
    //backgroundTexture.loadFromFile("./Images/fundo.png");
    enemy1Texture.loadFromFile("./Images/enemy1.png");
    poisonBombTexture.loadFromFile("./Images/poison.png");
    iceBombTexture.loadFromFile("./Images/ice.png");
    fireBombTexture.loadFromFile("./Images/fire.png");
    flashbangTexture.loadFromFile("./Images/flashbang.png");

    character.setTexture(characterTexture);
    //background.setTexture(backgroundTexture);
    enemy1.setTexture(enemy1Texture);
    poisonBomb.setTexture(poisonBombTexture);
    iceBomb.setTexture(iceBombTexture);
    fireBomb.setTexture(fireBombTexture);
    flashbang.setTexture(flashbangTexture);
    // Ajusta a escala inicial junto com o centro da figura

   sf::Vector2f centerM(enemy1Texture.getSize().x,enemy1Texture.getSize().y);
   centerM.x = centerM.x / 2;
   centerM.y = centerM.y / 2;
   enemy1.setOrigin(centerM);

   centerM.x=poisonBombTexture.getSize().x/2;
   centerM.y=poisonBombTexture.getSize().y/2;
   poisonBomb.setOrigin(centerM);
   poisonBomb.setScale(0.1f,0.1f);
   poisonBomb.setPosition(window.getSize().x/2,500);

   centerM.x=iceBombTexture.getSize().x/2;
   centerM.y=iceBombTexture.getSize().y/2;
   iceBomb.setOrigin(centerM);
   iceBomb.setScale(0.5f,0.5f);

   centerM.x=fireBombTexture.getSize().x/2;
   centerM.y=fireBombTexture.getSize().y/2;
   fireBomb.setOrigin(centerM);
   fireBomb.setScale(0.2f,0.2f);
   fireBomb.setPosition(400,525);

   centerM.x=flashbangTexture.getSize().x/2;
   centerM.y=flashbangTexture.getSize().y/2;
   flashbang.setOrigin(centerM);
   flashbang.setScale(0.5f,0.5f);
   flashbang.setPosition(600.f,230.f);
}

void Game::run(sf::Sprite background_level,Character& hero,std::string equipment)
{
    setValues();
    while (window.isOpen())
    {
        processEvents();
        update();
        update_enemy1();
        render(background_level,hero,equipment);
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
        velocity.x = -0.1f;
        frameAtualDireita += velocidadeAnimacao;
        linha =1;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        velocity.x = 0.1f;
        frameAtualEsquerda += velocidadeAnimacao;
        linha=2;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = -std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        velocity.y = -0.1f;
        frameAtualCima += velocidadeAnimacao;
        linha =3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        velocity.y = 0.1f;
        frameAtualBaixo += velocidadeAnimacao;
        linha =0;
    }
    position = character.getPosition();

    // Verifica se o personagem está se movendo
    bool isMoving = (velocity.x != 0.f || velocity.y != 0.f);

        //sf::IntRect textureRect=sf::IntRect(static_cast<int>(frameAtualEsquerda) * textureSize.x, linha * textureSize.y, textureSize.x, textureSize.y);
        //character.setTextureRect(textureRect);
    // Atualiza a lógica da animação
    if (isMoving) {
        // Calcula o frame atual baseado no tempo ou eventos de teclado
        // Substitua esta lógica com a sua própria animação
        if (velocity.x > 0.f) {

            if (frameAtualEsquerda > 4) {
                frameAtualEsquerda = 0.f;
            }
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualEsquerda) * textureSize.x, 
            linha * textureSize.y, textureSize.x, textureSize.y));
        } else if (velocity.x < 0.f) {

            if (frameAtualDireita > 4) {
                frameAtualDireita = 0.f;
            }
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualDireita) * textureSize.x, 
            linha * textureSize.y, textureSize.x, textureSize.y));
        }

        if (velocity.y < 0.f) {

            if (frameAtualCima > 4) {
                frameAtualCima = 0.f;
        }
        character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualCima) * textureSize.x, 
            linha * textureSize.y, textureSize.x, textureSize.y));
        } 
        else if (velocity.y > 0.f) {

            if (frameAtualBaixo > 4) {
                frameAtualBaixo = 0.f;
            }
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualBaixo) * textureSize.x, 
            linha * textureSize.y, textureSize.x, textureSize.y));
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
    sf::IntRect texturerect =character.getTextureRect();
    float velocidadeMovimento = 100.f;
    character.setOrigin(texturerect.width/2.f,texturerect.height/2.f);
    character.move(velocity * velocidadeMovimento * 0.016f);  // Multiplica pelo deltaTime
}
void Game::update_enemy1()
{
    sf::Vector2u textureSize = enemy1Texture.getSize();
    textureSize.x /= 4;  // Assumindo 4 frames na horizontal
    textureSize.y /= 4;  // Assumindo 4 frames na vertical

    float enemyScaleX =2.f;
    float enemyScaleY =2.f;

    enemy1.setScale(enemyScaleX, enemyScaleY);
    sf::Vector2f velocity =velocity_enemy1;

    if (velocity.x > 0.f) {
        frameAtualEsquerda_enemy += velocidadeAnimacao;
        if (frameAtualEsquerda_enemy > 4) {
            frameAtualEsquerda_enemy = 0.f;
        }
        //Seta qual figura vai aparecer
        enemy1.setTextureRect(sf::IntRect(static_cast<int>(frameAtualEsquerda_enemy) * textureSize.x, 2 * textureSize.y, textureSize.x, textureSize.y));
    } else if (velocity.x < 0.f) {
        frameAtualDireita_enemy += velocidadeAnimacao;
        if (frameAtualDireita_enemy > 4) {
            frameAtualDireita_enemy = 0.f;
        }
        enemy1.setTextureRect(sf::IntRect(static_cast<int>(frameAtualDireita_enemy) * textureSize.x, 1 * textureSize.y, textureSize.x, textureSize.y));
    }
    float velocidadeMovimento = 100.f;
    sf::IntRect texturerect=enemy1.getTextureRect();
    enemy1.setOrigin(texturerect.width/2.f,texturerect.height/2.f);
    enemy1.move(velocity_enemy1 * velocidadeMovimento * 0.016f);
    sf::Vector2f position_enemy1=enemy1.getPosition();
    //Verifica se o personagem ultrapassou as bordas da janela
    if (position_enemy1.x <=0) {
        position_enemy1.x = 0;
        enemy1.setPosition(position_enemy1.x,200.f);
        velocity_enemy1.x=0.4f;
    } else if (position_enemy1.x >= 800) {
        position_enemy1.x = 800;
        enemy1.setPosition(position_enemy1.x,200.f);
        velocity_enemy1.x = -0.4f;
    }
    position_enemy1 = enemy1.getPosition();
    enemy1.setPosition(position_enemy1.x,400.f);
}
void Game::render(sf::Sprite background_level,Character& hero,std::string equipment)
{
    window.clear();
    window.draw(background_level);
    for (size_t i = 0; i < 4; i++)
    {
        if (hero.Bombs[i].second == 0)
        {
            if (hero.Bombs[i].first == "FireBomb")
                    window.draw(fireBomb);
            if (hero.Bombs[i].first == "Flashbang")
                    window.draw(fireBomb);
            if (hero.Bombs[i].first == "PoisonBomb")
                    window.draw(fireBomb);
            if (hero.Bombs[i].first == "IceBomb")
                    window.draw(fireBomb);
        }
        
    }
    
    /*if(!hero.fireBomb && equipment== "fire")
        window.draw(fireBomb);
    if(!hero.flashbang && equipment =="flashbang")
        window.draw(flashbang);
    if(!hero.poisonBomb && equipment == "poison")
        window.draw(poisonBomb);
    if(!hero.iceBomb && equipment =="ice")
        window.draw(iceBomb);*/
    window.draw(character);
    window.draw(enemy1);
    window.display();
}