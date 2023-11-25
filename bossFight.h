#ifndef CODE_GAME_BOSSFIGHT_H
#define CODE_GAME_BOSSFIGHT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <queue>

struct Hero{
    float hp = 240;
    bool isAlive = true;
    bool iceBomb = false;
    bool fireBomb = false;
    bool poisonBomb = false;
    bool flashbang = false;
    int speed = 12;
    sf::RectangleShape playerHp;
    sf::Texture heroTexture;
    sf::Sprite heroSprite;
    sf::Sprite roundedHero;
    sf::Text textHero;
};

struct Alien{
    float hp = 700;
    bool isAlive = true;
    bool frozen = false;
    bool burn = false;
    bool poison = false;
    bool lessAccuracy = false;
    int speed = 25;
    sf::RectangleShape bossHp;
    sf::Texture bossTexture;
    sf::Sprite bossSprite;
    sf::Sprite roundedBoss;
    sf::Text textBoss;
};

class bossFight{
private:



    int pos_opBattle;
    int posBomb;
    bool pressed_opBattle, theselect_opBattle, pressed, theselect;
    bool enterPrevState;

    sf::Font font;
    sf::Texture image;
    sf::Sprite bg;
    sf::RenderWindow window;
    sf::RenderWindow windowAttack2;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture roundedTexture;
    sf::Font font_bar;

    std::vector<sf::Text> texts;
    std::vector<const char *> optionsBattle;
    std::vector<sf::Vector2f> coords_opBattle;
    std::vector<sf::Vector2f> coords_attack2;
    std::vector<sf::Text> texts_opBattle;
    std::vector<std::size_t> sizes_opBattle;
    std::vector<std::size_t> sizes;
    std::vector<const char *> choicesBomb;

    std::priority_queue<int> maxPriorityQueue;
public:
    void attack1(Alien& alien, Hero& hero);
    void attack2(Alien& alien, Hero& hero);
    void setValues();
    int loopChooseBomb();
    void drawSpecialAttack(Alien& alien, Hero& hero);
    int runChooseBomb(Alien& alien, Hero& hero);
    void heal(Hero& hero);
    void defineTurns(Alien& alien, Hero& hero);
    void damageCondition(Alien& alien);
    bool Turn(Alien& alien, Hero& hero);
    bool playerTurn(Alien& alien, Hero& hero);


    void enemyTurn(Alien& alien, Hero& hero);
    void writeTextesBattle();
    //void Battle();
    void modeBattle(Alien& alien, Hero& hero);
    void drawBattle(Alien& alien, Hero& hero);
    void layoutBattle(Alien& alien, Hero& hero);
};






#endif //CODE_GAME_BOSSFIGHT_H
