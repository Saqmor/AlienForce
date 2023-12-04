#ifndef CODE_GAME_BOSSFIGHT_H
#define CODE_GAME_BOSSFIGHT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <vector>
#include <queue>
#include <string>

struct Grenade{
    std::string type;
    bool full;
    sf::Texture bombTexture;
    sf::Sprite bombSprite;
};
struct Character{
    std::string name;
    float hp;
    float hpTurn;
    bool isAlive = true;
    bool burn = false;
    bool poison = false;
    bool lessAccuracy = false;
    bool gotEquipament = false;
    Grenade* grenades;
    int speed;
    sf::RectangleShape characterHp;
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    sf::Sprite roundedCharacter;
    sf::Text textCharacter;
};

class bossFight{
private:
    struct Option {
        int position;
        bool theselect;
        std::vector<sf::Text> texts;
        std::vector<std::string> words;
        std::vector<sf::Vector2f> coords;
        std::vector<std::size_t> sizes;
    };
    Option optionFight;
    Option optionAttack2;
    bool finishAttack2 = false;

    sf::Font font;
    sf::RenderWindow window;
    sf::RenderWindow windowAttack2;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture roundedTexture;

    sf::Font fontBar;

    std::priority_queue<int> maxPriorityQueue;

    void setValuesFight(Character& alien, Character& hero);
    void drawFight(Character& alien, Character& hero);
    void layoutFight(Character& alien, Character& hero);
    void defineTurns(Character& alien, Character& hero);
    void Turn(Character& alien, Character& hero);
    void playerTurn(Character& alien, Character& hero);
    void enemyTurn(Character& alien, Character& hero);
    void attack1(Character& alien, Character& hero);
    void attack2(Character& alien, Character& hero);
    void runAttack2(Character& alien, Character& hero);
    void setValuesAttack2();
    void loopAttack2(Character& alien, Character& hero);
    void drawAttack2(Character& alien, Character& hero);
    void heal(Character& hero);
    void damageCondition(Character& alien);

public:
    void modeFight(Character& alien, Character& hero);
};






#endif //CODE_GAME_BOSSFIGHT_H
