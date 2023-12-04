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

void bossFight::modeFight(Character& alien, Character& hero)
{
    setValuesFight(alien, hero);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!alien.isAlive || !hero.isAlive)
                window.close();
            if (maxPriorityQueue.empty())
                defineTurns(alien, hero);
            Turn(alien, hero);
            hero.characterHp.setSize(sf::Vector2f(hero.hp, 13));
            alien.characterHp.setSize(sf::Vector2f(0.45f*alien.hp, 13));
        }
        drawFight(alien, hero);
    }
}

void bossFight::setValuesFight(Character& alien, Character& hero) {
    hero.hpTurn = hero.hp;
    alien.hpTurn = alien.hp;
    backgroundTexture.loadFromFile("./Images/background_battle_2.png");
    background.setTexture(backgroundTexture);
    window.create(sf::VideoMode(800,600),"My window");


    optionFight.theselect = false;
    font.loadFromFile("./ethn.otf");
    optionFight.words = {"Atirar", "Especial", "Curar", "Fugir"};
    optionFight.texts.resize(4);
    optionFight.coords = {{70,500},{229,500},{419,500},{600,500}};
    optionFight.sizes = {20,20,20,20,20};
    for (std::size_t i{}; i < optionFight.texts.size(); ++i){
        optionFight.texts[i].setFont(font);
        optionFight.texts[i].setString(optionFight.words[i]);
        optionFight.texts[i].setCharacterSize(optionFight.sizes[i]);
        optionFight.texts[i].setOutlineColor(sf::Color::Green);
        optionFight.texts[i].setPosition(optionFight.coords[i]);
        optionFight.texts[i].setOutlineThickness(0);
    }
    optionFight.texts[0].setOutlineThickness(4);
    optionFight.position = 0;

    defineTurns(alien, hero);
}

void bossFight::drawFight(Character& alien, Character& hero){
    layoutFight(alien, hero);
    window.clear();
    window.draw(background);
    window.draw(alien.roundedCharacter);
    window.draw(hero.roundedCharacter);
    window.draw(hero.characterHp);
    window.draw(alien.characterHp);
    window.draw(alien.textCharacter);
    window.draw(hero.textCharacter);
    if(hero.hpTurn == hero.hp)
        window.draw(hero.characterSprite);
    if(alien.hpTurn == alien.hp)
        window.draw(alien.characterSprite);
    if(hero.hp<hero.hpTurn){
        hero.hpTurn=hero.hp;
    }
    if(alien.hp<alien.hpTurn){
        alien.hpTurn =alien.hp;
    }
    for(auto t : optionFight.texts){
        window.draw(t);
    }
    window.display();
}

void bossFight::layoutFight(Character& alien, Character& hero){
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
    fontBar.loadFromFile("ethn.otf");
    alien.textCharacter.setFont(fontBar);
    alien.textCharacter.setString("Boss HP");
    alien.textCharacter.setCharacterSize(12);
    hero.textCharacter.setFont(fontBar);
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

void bossFight::defineTurns(Character& alien, Character& hero) {
    if (alien.speed >= 2 * hero.speed)
        maxPriorityQueue.push(alien.speed);
    if (hero.speed >= 2 * alien.speed)
        maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(alien.speed);
}

void bossFight::Turn(Character& alien, Character& hero) {
    if (maxPriorityQueue.top() == alien.speed)
        enemyTurn(alien, hero);
    if (maxPriorityQueue.top() == hero.speed)
        playerTurn(alien, hero);
    if (hero.hp <= 0)
        hero.isAlive = false;
    if (alien.hp <= 0)
        alien.isAlive = false;
}

void bossFight::playerTurn(Character& alien, Character& hero) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !optionFight.theselect) {
        optionFight.theselect = true;
        switch (optionFight.position) {
            case 0:
                attack1(alien, hero);
                break;
            case 1:
                for (int i = 0; i < 4 && !hero.gotEquipament; ++i) {
                    if (hero.grenades[i].full){
                        hero.gotEquipament = true;
                    }
                }
                if (hero.gotEquipament)
                    attack2(alien, hero);
                break;
            case 2:
                heal(hero);
                break;
            case 3:
                window.close();
                break;
            default:
                break;
        }
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        optionFight.theselect = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (optionFight.position < 3) {
            ++optionFight.position;
            optionFight.texts[optionFight.position].setOutlineThickness(4);
            optionFight.texts[optionFight.position - 1].setOutlineThickness(0);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (optionFight.position > 0) {
            --optionFight.position;
            optionFight.texts[optionFight.position].setOutlineThickness(4);
            optionFight.texts[optionFight.position + 1].setOutlineThickness(0);
        }
    }
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

void bossFight::attack2(Character& alien, Character& hero){
    damageCondition(alien);
    if (maxPriorityQueue.top() == alien.speed)
        hero.hp -= 60.f + 2.f * dice(12);
    if (maxPriorityQueue.top() == hero.speed)
        runAttack2(alien, hero);
    maxPriorityQueue.pop();
}

void bossFight::runAttack2(Character& alien, Character& hero){
    setValuesAttack2();
    while (!finishAttack2){
        loopAttack2(alien, hero);
        drawAttack2(alien, hero);
    }
}

void bossFight::setValuesAttack2() {
    optionAttack2.words = {"Ice Bomb", "Fire Bomb", "Poison Bomb", "Flashbang"};
    optionAttack2.texts.resize(4);
    optionAttack2.sizes = {20,20,20,20,20};
    optionAttack2.coords = {{15,500},{160,500},{325,500},{550,500}};

    for (std::size_t i{}; i < optionAttack2.texts.size(); ++i){
        optionAttack2.texts[i].setFont(font);
        optionAttack2.texts[i].setString(optionAttack2.words[i]);
        optionAttack2.texts[i].setCharacterSize(optionAttack2.sizes[i]);
        optionAttack2.texts[i].setOutlineColor(sf::Color::Green);
        optionAttack2.texts[i].setPosition(optionAttack2.coords[i]);
        optionAttack2.texts[i].setOutlineThickness(0);
    }
    optionAttack2.texts[0].setOutlineThickness(4);
    finishAttack2 = false;
    optionAttack2.theselect = true;
    optionAttack2.position = 0;
}

void bossFight::loopAttack2(Character& alien, Character& hero) {
    sf::Event event;
    while(window.pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !optionAttack2.theselect) {
            optionAttack2.theselect = true;
            switch (optionAttack2.position) {
                case 0:
                    if (hero.grenades[0].full){
                        alien.hp -=  prob(40) ? 50.f + 2.f * dice(20) : 0;
                        alien.speed = 5;
                        finishAttack2 = true;
                    }
                    break;
                case 1:
                    if (hero.grenades[1].full){
                        alien.hp -=  prob(60) ? 120.f + 2.f * dice(20) : 0;
                        alien.burn = true;
                        finishAttack2 = true;
                    }
                    break;
                case 2:
                    if (hero.grenades[2].full){
                        alien.hp -=  prob(80) ? 40.f + 2.f * dice(20) : 0;
                        alien.poison = true;
                        finishAttack2 = true;
                    }
                    break;
                case 3:
                    if (hero.grenades[3].full){
                        alien.hp -=  prob(50) ? 50.f + 2.f * dice(20) : 0;
                        alien.lessAccuracy = true;
                        finishAttack2 = true;
                    }
                    break;
                default:
                    break;
            }
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            optionAttack2.theselect = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (optionAttack2.position < 3) {
                ++optionAttack2.position;
                optionAttack2.texts[optionAttack2.position].setOutlineThickness(4);
                optionAttack2.texts[optionAttack2.position - 1].setOutlineThickness(0);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (optionAttack2.position > 0) {
                --optionAttack2.position;
                optionAttack2.texts[optionAttack2.position].setOutlineThickness(4);
                optionAttack2.texts[optionAttack2.position + 1].setOutlineThickness(0);
            }
        }
    }
}

void bossFight::drawAttack2(Character& alien, Character& hero) {
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
    for(auto t : optionAttack2.texts){
        window.draw(t);
    }
    window.display();
}

void bossFight::heal(Character& hero) {
    hero.hp += 8.f + 1.f * dice(6);
    maxPriorityQueue.pop();
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