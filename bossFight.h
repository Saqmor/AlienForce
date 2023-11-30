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
    sf::Texture bomb_texture;
    sf::Sprite bomb_sprite;
};
struct Character{
    std::string name;
    float hp;
    float hp_turn;
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
    bool took_damage =false;
    sf::Clock recovery_time;
};


class bossFight{
private:
    int pos_opBattle;
    int posBomb;
    bool pressed_opBattle, theselect_opBattle, pressed, theselect_chooseBomb;
    bool finishAttck2 = false;

    sf::Font font;
    sf::RenderWindow window;
    sf::RenderWindow windowAttack2;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture roundedTexture;
    sf::Font font_bar;
    sf::Clock elapsed_time;
    const sf::Time interval = sf::seconds(2);

    std::vector<sf::Text> texts;
    std::vector<std::string> optionsBattle;
    std::vector<sf::Vector2f> coords_opBattle;
    std::vector<sf::Vector2f> coords_attack2;
    std::vector<sf::Text> texts_opBattle;
    std::vector<std::size_t> sizes_opBattle;
    std::vector<std::size_t> sizes;
    std::vector<std::string> choicesBomb;

    std::priority_queue<int> maxPriorityQueue;
public:
    void attack1(Character& alien, Character& hero);
    void attack2(Character& alien, Character& hero);
    void setValues_chooseBomb();
    void loopChooseBomb(Character& alien, Character& hero);
    void drawSpecialAttack(Character& alien, Character& hero);
    void runChooseBomb(Character& alien, Character& hero);
    void heal(Character& hero);
    void defineTurns(Character& alien, Character& hero);
    void damageCondition(Character& alien);
    void Turn(Character& alien, Character& hero);
    void playerTurn(Character& alien, Character& hero);
    void enemyTurn(Character& alien, Character& hero);
    void modeBattle(Character& alien, Character& hero);
    void setValues_Battle(Character& alien, Character& hero);
    void drawBattle(Character& alien, Character& hero);
    void layoutBattle(Character& alien, Character& hero);
};






#endif //CODE_GAME_BOSSFIGHT_H
