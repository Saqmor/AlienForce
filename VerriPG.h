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

struct Person{
    int hp = 100;
    bool isAlive = false;
    std::vector<bool> bomb;
};

struct Alien{
    int hp = 300;
    bool isAlive = false;
};

int d(int);
void attack1(Alien* alien, Person* person);
void attack2(Person* person, Alien* alien);
void heal();
void run();
std::queue<int> defineTurns();
void playerTurn();
void enemyTurn();
void Battle(Person* person, Alien* alien);





