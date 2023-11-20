#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <queue>

class Menu {
    int pos;
    bool pressed, theselect, selectedPlay;

    sf::RenderWindow * window;
    sf::RectangleShape * winclose;
    sf::Font * font;
    sf::Texture * image;
    sf::Sprite * bg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char *> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;


protected:
    void set_values();
    void loop_events();
    void draw_all();

public:
    Menu();
    ~Menu();
    void run_menu();
};



class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Event event;
    sf::Texture characterTexture, backgroundTexture, enemieTexture;
    sf::Sprite character, background, enemie;

    float characterScaleX, characterScaleY;
    sf::Vector2f position;

    // Adiciona variáveis para rastrear a animação em cada direção
    float frameAtualBaixo = 0.f;
    float frameAtualEsquerda = 0.f;
    float frameAtualDireita = 0.f;
    float frameAtualCima = 0.f;
    float velocidadeAnimacao = 0.005f;
    int linha;
};






class bossFight{
private:
    struct Hero{
        float hp = 200;
        bool isAlive = true;
        bool iceBomb = false;
        bool fireBomb = false;
        bool posionBomb = false;
        bool paralyzingBomb = false;
        int speed = 12;
    };
    Hero hero;

    struct Alien{
        float hp = 700;
        bool isAlive = true;
        bool frozen = false;
        bool burn = false;
        bool posion = false;
        bool lessAccuracy = false;
        int speed = 25;
    };
    Alien alien;



    int pos_opBattle;
    bool pressed_opBattle, theselect_opBattle;

    sf::Font * font;
    sf::Texture * image;
    sf::Sprite * bg;

    std::vector<const char *> optionsBattle;
    std::vector<sf::Vector2f> coords_opBattle;
    std::vector<sf::Text> texts_opBattle;
    std::vector<std::size_t> sizes_opBattle;

    std::priority_queue<int> maxPriorityQueue;
public:
    void attack1();
    int chooseBomb();
    void attack2();
    void heal();
    void defineTurns();
    void damageCondition();
    bool Turn();
    bool playerTurn();


    void enemyTurn();
    void writeTextesBattle();
    //void Battle();
    void modeBattle();
};





