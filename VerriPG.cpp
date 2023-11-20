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

    bossFight Fight;
    Fight.renderBattle();
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
        velocity.x = -0.05f;
        frameAtualDireita += velocidadeAnimacao;
        linha =1;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        velocity.x = 0.05f;
        frameAtualEsquerda += velocidadeAnimacao;
        linha=2;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = -std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        velocity.y = -0.05f;
        frameAtualCima += velocidadeAnimacao;
        linha =3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        velocity.y = 0.05f;
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







int dice(int n) {
    std::random_device dev;
    auto gen = std::mt19937(dev());
    std::uniform_int_distribution<int> dist(1, n);
    return dist(gen);
}

bool prob(int n) {
    if (dice(100) <= n) {
        return true;
    } else {
        return false;
    }
}

void bossFight::attack1(std::queue<int>* QueueTurns){
    if (QueueTurns->front() == 1)
        alien.hp -= 8 + dice(8);
    if (QueueTurns->front() == 2){
        if (alien.lessAccuracy)
            hero.hp -= prob(90) ? 10 + 2 * dice(8) : 0;
        else hero.hp -= 10 + 2 * dice(8);
    }

}

void bossFight::attack2(std::queue<int>* QueueTurns){
    if (QueueTurns->front() == 2)
        hero.hp -= 20 + 2 * dice(12);
    if (QueueTurns->front() == 1){
        switch (2) {
            case 1:
                alien.hp -=  prob(40) ? 50 + 2 * dice(20) : 0;
                QueueTurns->pop();
                QueueTurns->pop();
                break;
            case 2:
                alien.hp -=  prob(60) ? 120 + 2 * dice(20) : 0;
                alien.burn = true;
                break;
            case 3:
                alien.hp -=  prob(80) ? 40 + 2 * dice(20) : 0;
                alien.posion = true;
                break;
            case 4:
                alien.hp -=  prob(50) ? 50 + 2 * dice(20) : 0;
                alien.lessAccuracy = true;
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}


void bossFight::heal() {
    hero.hp += 10 + 2 * dice(6);
}

std::queue<int>* bossFight::defineTurns() {
    std::queue<int>* turn = new std::queue<int>();
    turn->push(1);
    for (int i = 0; i < 2; ++i) {
        turn->push(2);
    }
    return turn;
}

void bossFight::damageCondition() {
    if (alien.burn)
        alien.hp -= 4;
    if (alien.posion)
        alien.hp -= 7;
    if (alien.hp <= 0){
        alien.hp = 0;
        alien.isAlive = false;
    }
}

bool bossFight::playerTurn(std::queue<int>* QueueTurns) {
    /* declarar isso para poder trocar as opções de batalha com as setinhas Left e Right:
    int pos_opBattle;
    bool pressed_opBattle, theselect_opBattle;

    sf::Font * font;
    sf::Texture * image;
    sf::Sprite * bg;

    std::vector<const char *> optionBattle;
    std::vector<sf::Vector2f> coords_opBattle;
    std::vector<sf::Text> texts_opBattle;
    std::vector<std::size_t> sizes_opBattle;
     *
     * */

    pos_opBattle = 0;
    pressed_opBattle = theselect_opBattle = false;
    font->loadFromFile("./ethn.otf");
    //image->loadFromFile("");

    //bg->setTexture(*image);
    optionsBattle = {"Atirar", "Granada especial", "Curar", "Fugir"};
    texts_opBattle.resize(4);
    coords_opBattle = {{10,20},{100,20},{300,20},{500,20}};
    sizes_opBattle = {20,20,20,20,20};

    for (std::size_t i{}; i < texts_opBattle.size(); ++i){
        texts_opBattle[i].setFont(*font);
        texts_opBattle[i].setString(optionsBattle[i]);
        texts_opBattle[i].setCharacterSize(sizes_opBattle[i]);
        texts_opBattle[i].setOutlineColor(sf::Color::Green);
        texts_opBattle[i].setPosition(coords_opBattle[i]);
    }
    texts_opBattle[0].setOutlineThickness(4);
    pos_opBattle = 0;

    damageCondition();
    if (!alien.isAlive)
        return false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pressed_opBattle){
        if( pos_opBattle < 4){
            ++pos_opBattle;
            pressed_opBattle = true;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle - 1].setOutlineThickness(0);
            pressed_opBattle = false;
            theselect_opBattle = false;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed_opBattle){
        if( pos_opBattle > 1){
            --pos_opBattle;
            pressed_opBattle = true;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle + 1].setOutlineThickness(0);
            pressed_opBattle = false;
            theselect_opBattle = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect_opBattle) {
        theselect_opBattle = true;
        switch (pos_opBattle) {
            case 1:
                // Code for "Attack1" option
                attack1(QueueTurns);
                break;
            case 2:
                // Code for "Attack2" option
                attack2(QueueTurns);
                break;
            case 3:
                // Code for "Heal" option
                heal();
                break;
            case 4:
                // Code for "Run" option
                return false;
            default:
                break;
        }
    }
    QueueTurns->pop();
    return true;
}

void bossFight::enemyTurn(std::queue<int>* QueueTurns) {
    if (prob(80))
        attack1(QueueTurns);
    else attack2(QueueTurns);
    QueueTurns->pop();
}

/*void bossFight::Battle(){
    bool endBattle = false;
    std::queue<int>* QueueTurns = defineTurns();
    while (hero.isAlive && alien.isAlive && !endBattle){
        if (QueueTurns->empty())
            QueueTurns = defineTurns();
        if (QueueTurns->front() == 1){
            if (!playerTurn(QueueTurns))
                endBattle = true;
            if (!alien.isAlive){
                alien.hp = 0;
                continue;
            }
        }
        if (QueueTurns->front() == 2){
            enemyTurn(QueueTurns);
            if (!alien.isAlive) {
                alien.hp = 0;
                continue;
            }
            if (!hero.isAlive){
                hero.hp = 0;
                continue;
            }
        }
    }
    if (endBattle)
        saia da imagem da batalha e coloque o personagem em uma coordenada segura
        a ideia é começar a batalha quando o personagem chegar perto
}*/
void bossFight::renderBattle()
{   
    sf::RenderWindow window(sf::VideoMode(800,600),"My window");

    //Imagem de fundo
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./Images/fundo.png");
    background.setTexture(backgroundTexture);

    //Criação de retângulos envolventes  
    sf::Texture roundedTexture;
    roundedTexture.loadFromFile("./Images/rounded(5).png");
    sf::Sprite roundedHero,roundedBoss;
    roundedHero.setTexture(roundedTexture);
    roundedBoss.setTexture(roundedTexture);
    roundedHero.setScale(-1.3f,0.4f);
    roundedBoss.setScale(1.9f,0.4f);
    sf::RectangleShape playerHp(sf::Vector2f(hero.hp,13.f));
    sf::RectangleShape bossHp(sf::Vector2f(alien.hp,13.f));

    //Criação dos personagens
    sf::Texture heroTexture,bossTexture;
    heroTexture.loadFromFile("./Images/hero.png");
    bossTexture.loadFromFile("./Images/boss.png");
    sf::Sprite heroSprite,bossSprite;
    heroSprite.setTexture(heroTexture);
    bossSprite.setTexture(bossTexture);

    //Texto
    sf::Text textHero,textBoss;
    sf::Font font;
    font.loadFromFile("ethn.otf");
    textBoss.setFont(font);
    textBoss.setString("Boss HP");
    textBoss.setCharacterSize(12);
    textHero.setFont(font);
    textHero.setString("Hero HP");
    textHero.setCharacterSize(12); 

    //Pintura    
    playerHp.setFillColor(sf::Color(144,238,144));
    bossHp.setFillColor(sf::Color(144,238,144));
    textBoss.setFillColor(sf::Color(0,128,128));
    textHero.setFillColor(sf::Color(0,128,128));
    roundedBoss.setColor(sf::Color(222,184,135));
    roundedHero.setColor(sf::Color(222,184,135));

    //Posicionamento
    playerHp.setPosition(600.f,400.f);
    bossHp.setPosition(0,64.f);
    roundedBoss.setPosition(-130.f,30.f);
    roundedHero.setPosition(900.f,370.f);
    textBoss.setPosition(20.f,40.f);
    textHero.setPosition(705.f,380.f);
    
    // Ajusta a escala e posicionamento das Sprites Hero e Boss
    sf::Vector2f positionHero(static_cast<float>(heroTexture.getSize().x), static_cast<float>(heroTexture.getSize().y));
    sf::Vector2f positionBoss(static_cast<float>(bossTexture.getSize().x), static_cast<float>(bossTexture.getSize().y));
    positionHero.x = positionHero.x / 2;
    positionHero.y = positionHero.y / 2;
    positionBoss.x = positionBoss.x / 2;
    positionHero.y = positionBoss.y / 2;
    heroSprite.setOrigin(positionHero);
    bossSprite.setOrigin(positionBoss);
    heroSprite.setPosition(150.f,380.f);
    bossSprite.setPosition(675.f,250.f);
    bossSprite.setScale(0.5f,0.5f);
    heroSprite.setScale(0.5f,0.5f);

    bool endBattle = false;
    std::queue<int>* QueueTurns = defineTurns();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (hero.isAlive && alien.isAlive && !endBattle){
                if (QueueTurns->empty())
                    QueueTurns = defineTurns();
                if (QueueTurns->front() == 1){
                    if (!playerTurn(QueueTurns))
                        endBattle = true;
                    if (!alien.isAlive){
                        alien.hp = 0;
                        endBattle = true;
                    }
                }
                else if (QueueTurns->front() == 2){
                    enemyTurn(QueueTurns);
                    if (!alien.isAlive) {
                        alien.hp = 0;
                        endBattle = true;
                    }
                    if (!hero.isAlive){
                        hero.hp = 0;
                        continue;
                    }
                }
            }
            if (endBattle)
                window.close();

            playerHp.setSize(sf::Vector2f(hero.hp, 13));
            bossHp.setSize(sf::Vector2f(0.45*alien.hp, 13));
        }
        window.clear();
        window.draw(background);
        window.draw(roundedBoss);
        window.draw(roundedHero);
        window.draw(playerHp);
        window.draw(bossHp);
        window.draw(textBoss);
        window.draw(textHero);
        window.draw(heroSprite);
        window.draw(bossSprite);
        window.display();
    }
}