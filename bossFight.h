#ifndef CODE_GAME_BOSSFIGHT_H
#define CODE_GAME_BOSSFIGHT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <vector>
#include <queue>
#include <string>

/*struct Hero{
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
};*/
struct Grenade{
    std::string type;
    bool full=false;
    sf::Texture bomb_texture;
    sf::Sprite bomb_sprite;
};
struct Character{
    std::string name;
    float hp;
    bool isAlive = true;
    bool burn = false;
    bool poison = false;
    bool lessAccuracy = false;
    std::vector<Grenade> Grenades;
    /*----------------------------------------------------------------------------------------------------------*/
    bool gotEquipament = false;
    Grenade* grenades;
    /*----------------------------------------------------------------------------------------------------------*/
    int speed;
    sf::RectangleShape characterHp;
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    sf::Sprite roundedCharacter;
    sf::Text textCharacter;
};


class bossFight{
private:



    int pos_opBattle;
    int posBomb;
    bool pressed_opBattle, theselect_opBattle, pressed, theselect;
    bool enterPrevState;
    bool finishAttck2 = false;

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
    void attack1(Character& alien, Character& hero);
    void attack2(Character& alien, Character& hero);
    void setValues();
    void loopChooseBomb(Character& alien, Character& hero);
    void drawSpecialAttack(Character& alien, Character& hero);
    void runChooseBomb(Character& alien, Character& hero);
    void heal(Character& hero);
    void defineTurns(Character& alien, Character& hero);
    void damageCondition(Character& alien);
    bool Turn(Character& alien, Character& hero);
    bool playerTurn(Character& alien, Character& hero);


    void enemyTurn(Character& alien, Character& hero);
    void writeTextesBattle();
    //void Battle();
    void modeBattle(Character& alien, Character& hero);
    void drawBattle(Character& alien, Character& hero);
    void layoutBattle(Character& alien, Character& hero);
};






#endif //CODE_GAME_BOSSFIGHT_H
