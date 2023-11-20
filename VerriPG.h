#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <queue>

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

    void initializeMenu();
    void processMenuEvents();
    void drawMenu();
    void runMenu();

    sf::Font menuFont;
    sf::Text menuText;
    int menuPosition;
    bool menuPressed;
    std::vector<const char *> options;
    std::vector<sf::Vector2f> coords;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    sf::RectangleShape * winclose;

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
        bool isAlive = false;
        bool iceBomb = false;
        bool fireBomb = false;
        bool posionBomb = false;
        bool paralyzingBomb = false;
    };
    Hero hero;

    struct Alien{
        float hp = 700;
        bool isAlive = false;
        bool frozen = false;
        bool burn = false;
        bool posion = false;
        bool lessAccuracy = false;
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

public:
    void attack1(std::queue<int>* QueueTurns);
    void attack2(std::queue<int>* QueueTurns);
    int chooseBomb();
    void heal();
    std::queue<int>* defineTurns();
    void damageCondition();
    bool playerTurn(std::queue<int>* QueueTurns);
    void enemyTurn(std::queue<int>* QueueTurns);
    //void Battle();
    void renderBattle();
};





