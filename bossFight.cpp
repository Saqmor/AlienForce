#include "bossFight.h"


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

void bossFight::attack1(Character& alien, Character& hero){
    damageCondition(alien);
    if (maxPriorityQueue.top() == hero.speed)
        alien.hp -= 7.f + dice(8);
    if (maxPriorityQueue.top() == alien.speed){
        if (alien.lessAccuracy)
            hero.hp -= prob(85) ? 10.f + 2.f * dice(8) : 0;
        else hero.hp -= 10.f + 2.f * dice(8);
    }
    maxPriorityQueue.pop();
}


void bossFight::setValues() {
    choicesBomb = {"Ice Bomb", "Fire Bomb", "Poison Bomb", "Flashbang"};
    texts.resize(4);
    sizes = {20,20,20,20,20};
    coords_attack2 = {{15,500},{160,500},{325,500},{550,500}};

    for (std::size_t i{}; i < texts.size(); ++i){
        texts[i].setFont(font);
        texts[i].setString(choicesBomb[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Green);
        texts[i].setPosition(coords_attack2[i]);
/*---------------------------------------------------------------------------------------------------------------*/
        texts[i].setOutlineThickness(0);
/*---------------------------------------------------------------------------------------------------------------*/
    }
    texts[0].setOutlineThickness(4);
    posBomb = 0;
}

void bossFight::loopChooseBomb(Character& alien, Character& hero) {
    sf::Event event;
    while(window.pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterPrevState) {
            enterPrevState = true;
            switch (posBomb) {
                case 0:
/*-----------------------------------------------------------------------------------*/
                    if (hero.Grenades[0].full){
                        alien.hp -=  prob(40) ? 50.f + 2.f * dice(20) : 0;
                        alien.speed -= 20;
                        finishAttck2 = true;
                    }
                    else attack2(alien, hero);
/*-----------------------------------------------------------------------------------*/
                    break;
                case 1:
/*-----------------------------------------------------------------------------------*/
                    if (hero.Grenades[1].full){
                        alien.hp -=  prob(60) ? 120.f + 2.f * dice(20) : 0;
                        alien.burn = true;
                        finishAttck2 = true;
                    }
                    else attack2(alien, hero);
/*-----------------------------------------------------------------------------------*/
                    break;
                case 2:
/*-----------------------------------------------------------------------------------*/
                    if (hero.Grenades[2].full){
                        alien.hp -=  prob(80) ? 40.f + 2.f * dice(20) : 0;
                        alien.poison = true;
                        finishAttck2 = true;
                    }
                    else attack2(alien, hero);
/*-----------------------------------------------------------------------------------*/
                    break;
                case 3:
/*-----------------------------------------------------------------------------------*/
                    if (hero.Grenades[3].full){
                        alien.hp -=  prob(50) ? 50.f + 2.f * dice(20) : 0;
                        alien.lessAccuracy = true;
                        finishAttck2 = true;
                    }
                    else attack2(alien, hero);
/*-----------------------------------------------------------------------------------*/
                    break;
                default:
                    break;
            }
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            // Se a tecla Enter não estiver pressionada, reinicia theselect_opBattle
            enterPrevState = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pressed) {
            if (posBomb < 3) {
                ++posBomb;
                texts[posBomb].setOutlineThickness(4);
                texts[posBomb - 1].setOutlineThickness(0);
                pressed = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed) {
            if (posBomb > 0) {
                --posBomb;
                texts[posBomb].setOutlineThickness(4);
                texts[posBomb + 1].setOutlineThickness(0);
                pressed = false;
            }
        }
    }
}

void bossFight::drawSpecialAttack(Character& alien, Character& hero) {
    window.clear();
    window.draw(background);
    window.draw(alien.roundedCharacter);
    window.draw(hero.roundedCharacter);
    window.draw(hero.characterHp);
    window.draw(alien.characterHp);
    window.draw(alien.textCharacter);
    window.draw(hero.textCharacter);
    window.draw(hero.characterSprite);
    window.draw(alien.characterSprite);
    for(auto t : texts){
        window.draw(t);
    }
    window.display();
}

void bossFight::runChooseBomb(Character& alien, Character& hero){
    enterPrevState = true;
    setValues();
    while (!finishAttck2){
        loopChooseBomb(alien, hero);
        drawSpecialAttack(alien, hero);
    }
}

void bossFight::attack2(Character& alien, Character& hero){
    damageCondition(alien);
    if (maxPriorityQueue.top() == alien.speed)
        hero.hp -= 60.f + 2.f * dice(12);
    if (maxPriorityQueue.top() == hero.speed){
        runChooseBomb(alien, hero);
        /*switch (runChooseBomb(alien, hero)) {
            case 1:
                if (hero.Grenades[0].full){
                    alien.hp -=  prob(40) ? 50.f + 2.f * dice(20) : 0;
                    alien.speed -= 20;
                }
                break;
            case 2:
                if (hero.Grenades[1].full){
                    alien.hp -=  prob(60) ? 120.f + 2.f * dice(20) : 0;
                    alien.burn = true;
                }
                break;
            case 3:
                if (hero.Grenades[2].full){
                    alien.hp -=  prob(80) ? 40.f + 2.f * dice(20) : 0;
                    alien.poison = true;
                }
                break;
            case 4:
                if (hero.Grenades[3].full){
                    alien.hp -=  prob(50) ? 50.f + 2.f * dice(20) : 0;
                    alien.lessAccuracy = true;
                }
                break;
            default:
                std::cout << "Invalid option.\n";
        }*/
    }
    maxPriorityQueue.pop();
}


void bossFight::heal(Character& hero) {
    hero.hp += 8.f + 1.f * dice(6);
    maxPriorityQueue.pop();
}

void bossFight::defineTurns(Character& alien, Character& hero) {
    if (alien.speed >= 2 * hero.speed)
        maxPriorityQueue.push(alien.speed);
    if (hero.speed >= 2 * alien.speed)
        maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(alien.speed);
}

void bossFight::damageCondition(Character& alien) {
    if (alien.burn)
        alien.hp -= 4;
    if (alien.poison)
        alien.hp -= 7;
    if (alien.hp <= 0){
        alien.hp = 0;
        alien.isAlive = false;
    }
}

bool bossFight::Turn(Character& alien, Character& hero) {
    if (maxPriorityQueue.top() == alien.speed)
        enemyTurn(alien, hero);
    if ( playerTurn(alien, hero))
        return true;
    else return false;
}

bool bossFight::playerTurn(Character& alien, Character& hero) {

    // Verifica se a tecla Enter está pressionada
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect_opBattle) {
        // Verifica se o jogador ainda não selecionou a opção atual
        theselect_opBattle = true;
        std::cout << "entrou ";
        switch (pos_opBattle) {
            case 0:
                // Code for "Attack1" option
                attack1(alien, hero);
                break;
            case 1:
                // Code for "Attack2" option
                /*----------------------------------------------------------------------------------------------------------*/
                for (int i = 0; i < hero.Grenades.size() && !hero.gotEquipament; ++i) {
                    if (hero.Grenades[i].full){
                        hero.gotEquipament = true;
                    }
                }
                /*----------------------------------------------------------------------------------------------------------*/
                if (hero.gotEquipament)
                    attack2(alien, hero);
                break;
            case 2:
                // Code for "Heal" option
                heal(hero);
                break;
            case 3:
                // Code for "Run" option
                return false;
            default:
                break;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        // Se a tecla Enter não estiver pressionada, reinicia theselect_opBattle
        theselect_opBattle = false;
    }

    // Lógica para navegar entre as opções com as teclas direcionais
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pressed_opBattle) {
        if (pos_opBattle < 3) {
            ++pos_opBattle;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle - 1].setOutlineThickness(0);
            pressed_opBattle = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed_opBattle) {
        if (pos_opBattle > 0) {
            --pos_opBattle;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle + 1].setOutlineThickness(0);
            pressed_opBattle = false;
        }
    }

    return true;
}


void bossFight::enemyTurn(Character& alien, Character& hero) {
    if (prob(90))
        attack1(alien, hero);
    else attack2(alien, hero);

    if (hero.hp <= 0){
        hero.hp = 0;
        hero.isAlive = false;
    }
}
void bossFight::layoutBattle(Character& alien, Character& hero)
{
    //Criação de retângulos envolventes
    roundedTexture.loadFromFile("./Images/rounded(5).png");
    hero.roundedCharacter.setTexture(roundedTexture);
    alien.roundedCharacter.setTexture(roundedTexture);
    hero.roundedCharacter.setScale(-1.3f,0.4f);
    alien.roundedCharacter.setScale(1.9f,0.4f);

    //Criação dos personagens
    hero.characterTexture.loadFromFile("./Images/hero.png");
    alien.characterTexture.loadFromFile("./Images/alien_boss_true.png");
    hero.characterSprite.setTexture(hero.characterTexture);
    alien.characterSprite.setTexture(alien.characterTexture);

    //Texto
    font_bar.loadFromFile("ethn.otf");
    alien.textCharacter.setFont(font_bar);
    alien.textCharacter.setString("Boss HP");
    alien.textCharacter.setCharacterSize(12);
    hero.textCharacter.setFont(font_bar);
    hero.textCharacter.setString("Hero HP");
    hero.textCharacter.setCharacterSize(12);

    //Pintura
    hero.characterHp.setFillColor(sf::Color(144,238,144));
    alien.characterHp.setFillColor(sf::Color(144,238,144));
    alien.textCharacter.setFillColor(sf::Color(0,128,128));
    hero.textCharacter.setFillColor(sf::Color(0,128,128));
    alien.roundedCharacter.setColor(sf::Color(222,184,135));
    hero.roundedCharacter.setColor(sf::Color(222,184,135));

    //Posicionamento
    hero.characterHp.setPosition(600.f,400.f);
    alien.characterHp.setPosition(0,64.f);
    alien.roundedCharacter.setPosition(-130.f,30.f);
    hero.roundedCharacter.setPosition(900.f,370.f);
    alien.textCharacter.setPosition(20.f,40.f);
    hero.textCharacter.setPosition(705.f,380.f);

    // Ajusta a escala e posicionamento das Sprites Hero e Boss
    sf::Vector2f positionHero(static_cast<float>(hero.characterTexture.getSize().x), static_cast<float>(hero.characterTexture.getSize().y));
    sf::Vector2f positionBoss(static_cast<float>(alien.characterTexture.getSize().x), static_cast<float>(alien.characterTexture.getSize().y));
    positionHero.x = positionHero.x / 2;
    positionHero.y = positionHero.y / 2;
    positionBoss.x = positionBoss.x / 2;
    positionHero.y = positionBoss.y / 2;
    hero.characterSprite.setOrigin(positionHero);
    alien.characterSprite.setOrigin(positionBoss);
    hero.characterSprite.setPosition(150.f,380.f);
    alien.characterSprite.setPosition(650.f,370.f);
    alien.characterSprite.setScale(0.5f,0.5f);
    hero.characterSprite.setScale(0.5f,0.5f);

}
void bossFight::drawBattle(Character& alien, Character& hero)
{
    layoutBattle(alien, hero);

    window.clear();
    window.draw(background);
    window.draw(alien.roundedCharacter);
    window.draw(hero.roundedCharacter);
    window.draw(hero.characterHp);
    window.draw(alien.characterHp);
    window.draw(alien.textCharacter);
    window.draw(hero.textCharacter);
    window.draw(hero.characterSprite);
    window.draw(alien.characterSprite);
    for(auto t : texts_opBattle){
        window.draw(t);
    }
    window.display();
}
void bossFight::modeBattle(Character& alien, Character& hero)
{
    backgroundTexture.loadFromFile("./Images/background_battle_2.png");
    background.setTexture(backgroundTexture);
    window.create(sf::VideoMode(800,600),"My window");

    pressed_opBattle = theselect_opBattle = false;
    font.loadFromFile("./ethn.otf");
    //image->loadFromFile("");

    //bg->setTexture(*image);
    optionsBattle = {"Atirar", "Especial", "Curar", "Fugir"};
    texts_opBattle.resize(4);
    coords_opBattle = {{70,500},{229,500},{419,500},{600,500}};
    sizes_opBattle = {20,20,20,20,20};

    for (std::size_t i{}; i < texts_opBattle.size(); ++i){
        texts_opBattle[i].setFont(font);
        texts_opBattle[i].setString(optionsBattle[i]);
        texts_opBattle[i].setCharacterSize(sizes_opBattle[i]);
        texts_opBattle[i].setOutlineColor(sf::Color::Green);
        texts_opBattle[i].setPosition(coords_opBattle[i]);
/*---------------------------------------------------------------------------------------------------------------*/
        texts_opBattle[i].setOutlineThickness(0);
/*---------------------------------------------------------------------------------------------------------------*/
    }
    texts_opBattle[0].setOutlineThickness(4);
    pos_opBattle = 0;


    defineTurns(alien, hero);
    bool endBattle = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (hero.isAlive && alien.isAlive && !endBattle){
                if (maxPriorityQueue.empty())
                    defineTurns(alien, hero);
                if (!Turn(alien, hero))
                    endBattle = true;
                if (!alien.isAlive)
                    endBattle = true;
                if (!hero.isAlive)
                    endBattle = true;
            }
            if (endBattle)
                window.close();


            hero.characterHp.setSize(sf::Vector2f(hero.hp, 13));
            alien.characterHp.setSize(sf::Vector2f(0.45f*alien.hp, 13));

        }
        drawBattle(alien, hero);
    }


}