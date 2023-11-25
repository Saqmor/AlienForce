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

void bossFight::attack1(){
    damageCondition();
    if (maxPriorityQueue.top() == hero.speed)
        alien.hp -= 7 + dice(8);
    if (maxPriorityQueue.top() == alien.speed){
        if (alien.lessAccuracy)
            hero.hp -= prob(85) ? 10 + 2 * dice(8) : 0;
        else hero.hp -= 10 + 2 * dice(8);
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
    }
    texts[0].setOutlineThickness(4);
    posBomb = 0;
}

int bossFight::loopChooseBomb() {
    sf::Event event;
    while(window.pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterPrevState) {
            enterPrevState = true;
            switch (posBomb) {
                case 0:
                    return 1;
                case 1:
                    return 2;
                case 2:
                    return 3;
                case 3:
                    return 4;
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
                pressed = true;
                texts[posBomb].setOutlineThickness(4);
                texts[posBomb - 1].setOutlineThickness(0);
                pressed = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed) {
            if (posBomb > 0) {
                --posBomb;
                pressed = true;
                texts[posBomb].setOutlineThickness(4);
                texts[posBomb + 1].setOutlineThickness(0);
                pressed = false;
            }
        }
    }
    return -1;
}

void bossFight::drawSpecialAttack() {
    window.clear();
    window.draw(background);
    window.draw(alien.roundedBoss);
    window.draw(hero.roundedHero);
    window.draw(hero.playerHp);
    window.draw(alien.bossHp);
    window.draw(alien.textBoss);
    window.draw(hero.textHero);
    window.draw(hero.heroSprite);
    window.draw(alien.bossSprite);
    for(auto t : texts){
        window.draw(t);
    }
    window.display();
}

int bossFight::runChooseBomb(){
    int num = -1;
    enterPrevState = true;
    setValues();
    while (num == -1){
        num = loopChooseBomb();
        drawSpecialAttack();
    }
    texts[posBomb].setOutlineThickness(0);
    return num;
}

void bossFight::attack2(){
    damageCondition();
    if (maxPriorityQueue.top() == alien.speed)
        hero.hp -= 60 + 2 * dice(12);
    if (maxPriorityQueue.top() == hero.speed){
        switch (runChooseBomb()) {
            case 1:
                alien.hp -=  prob(40) ? 50 + 2 * dice(20) : 0;
                alien.speed -= 20;
                break;
            case 2:
                alien.hp -=  prob(60) ? 120 + 2 * dice(20) : 0;
                alien.burn = true;
                break;
            case 3:
                alien.hp -=  prob(80) ? 40 + 2 * dice(20) : 0;
                alien.poison = true;
                break;
            case 4:
                alien.hp -=  prob(50) ? 50 + 2 * dice(20) : 0;
                alien.lessAccuracy = true;
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    }
    maxPriorityQueue.pop();
}


void bossFight::heal() {
    hero.hp += 8 + 1 * dice(6);
    maxPriorityQueue.pop();
}

void bossFight::defineTurns() {
    if (alien.speed >= 2 * hero.speed)
        maxPriorityQueue.push(alien.speed);
    if (hero.speed >= 2 * alien.speed)
        maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(alien.speed);
}

void bossFight::damageCondition() {
    if (alien.burn)
        alien.hp -= 4;
    if (alien.poison)
        alien.hp -= 7;
    if (alien.hp <= 0){
        alien.hp = 0;
        alien.isAlive = false;
    }
}

bool bossFight::Turn() {
    if (maxPriorityQueue.top() == alien.speed)
        enemyTurn();
    if ( playerTurn())
        return true;
    else return false;
}

bool bossFight::playerTurn() {

    // Verifica se a tecla Enter está pressionada
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect_opBattle) {
        // Verifica se o jogador ainda não selecionou a opção atual
        theselect_opBattle = true;
        std::cout << "entrou ";
        switch (pos_opBattle) {
            case 0:
                // Code for "Attack1" option
                attack1();
                break;
            case 1:
                // Code for "Attack2" option
                attack2();
                break;
            case 2:
                // Code for "Heal" option
                heal();
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
            pressed_opBattle = true;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle - 1].setOutlineThickness(0);
            pressed_opBattle = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed_opBattle) {
        if (pos_opBattle > 0) {
            --pos_opBattle;
            pressed_opBattle = true;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle + 1].setOutlineThickness(0);
            pressed_opBattle = false;
        }
    }

    return true;
}


void bossFight::enemyTurn() {
    if (prob(90))
        attack1();
    else attack2();

    if (hero.hp <= 0){
        hero.hp = 0;
        hero.isAlive = false;
    }
}
void bossFight::layoutBattle()
{
    //Criação de retângulos envolventes
    roundedTexture.loadFromFile("./Images/rounded(5).png");
    hero.roundedHero.setTexture(roundedTexture);
    alien.roundedBoss.setTexture(roundedTexture);
    hero.roundedHero.setScale(-1.3f,0.4f);
    alien.roundedBoss.setScale(1.9f,0.4f);

    //Criação dos personagens
    hero.heroTexture.loadFromFile("./Images/hero.png");
    alien.bossTexture.loadFromFile("./Images/alien_boss_true.png");
    hero.heroSprite.setTexture(hero.heroTexture);
    alien.bossSprite.setTexture(alien.bossTexture);

    //Texto
    font_bar.loadFromFile("ethn.otf");
    alien.textBoss.setFont(font_bar);
    alien.textBoss.setString("Boss HP");
    alien.textBoss.setCharacterSize(12);
    hero.textHero.setFont(font_bar);
    hero.textHero.setString("Hero HP");
    hero.textHero.setCharacterSize(12);

    //Pintura
    hero.playerHp.setFillColor(sf::Color(144,238,144));
    alien.bossHp.setFillColor(sf::Color(144,238,144));
    alien.textBoss.setFillColor(sf::Color(0,128,128));
    hero.textHero.setFillColor(sf::Color(0,128,128));
    alien.roundedBoss.setColor(sf::Color(222,184,135));
    hero.roundedHero.setColor(sf::Color(222,184,135));

    //Posicionamento
    hero.playerHp.setPosition(600.f,400.f);
    alien.bossHp.setPosition(0,64.f);
    alien.roundedBoss.setPosition(-130.f,30.f);
    hero.roundedHero.setPosition(900.f,370.f);
    alien.textBoss.setPosition(20.f,40.f);
    hero.textHero.setPosition(705.f,380.f);

    // Ajusta a escala e posicionamento das Sprites Hero e Boss
    sf::Vector2f positionHero(hero.heroTexture.getSize().x,hero.heroTexture.getSize().y);
    sf::Vector2f positionBoss(alien.bossTexture.getSize().x, alien.bossTexture.getSize().y);
    positionHero.x = positionHero.x / 2;
    positionHero.y = positionHero.y / 2;
    positionBoss.x = positionBoss.x / 2;
    positionHero.y = positionBoss.y / 2;
    hero.heroSprite.setOrigin(positionHero);
    alien.bossSprite.setOrigin(positionBoss);
    hero.heroSprite.setPosition(150.f,380.f);
    alien.bossSprite.setPosition(650.f,370.f);
    alien.bossSprite.setScale(0.5f,0.5f);
    hero.heroSprite.setScale(0.5f,0.5f);

}
void bossFight::drawBattle()
{
    layoutBattle();

    window.clear();
    window.draw(background);
    window.draw(alien.roundedBoss);
    window.draw(hero.roundedHero);
    window.draw(hero.playerHp);
    window.draw(alien.bossHp);
    window.draw(alien.textBoss);
    window.draw(hero.textHero);
    window.draw(hero.heroSprite);
    window.draw(alien.bossSprite);
    for(auto t : texts_opBattle){
        window.draw(t);
    }
    window.display();
}
void bossFight::modeBattle()
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
    }
    texts_opBattle[0].setOutlineThickness(4);
    pos_opBattle = 0;


    defineTurns();
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
                    defineTurns();
                if (!Turn())
                    endBattle = true;
                if (!alien.isAlive)
                    endBattle = true;
                if (!hero.isAlive)
                    endBattle = true;
            }
            if (endBattle)
                window.close();


            hero.playerHp.setSize(sf::Vector2f(hero.hp, 13));
            alien.bossHp.setSize(sf::Vector2f(0.45*alien.hp, 13));

        }
        drawBattle();
    }


}
