#pragma once
#include <vector>
#include <float.h>
#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <queue>


class bossFight{
private:
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
    Hero hero;

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
    Alien alien;


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
    void attack1();
    void attack2();
    void setValues();
    int loopChooseBomb();
    void drawSpecialAttack();
    int runChooseBomb();
    void heal();
    void defineTurns();
    void damageCondition();
    bool Turn();
    bool playerTurn();


    void enemyTurn();
    void writeTextesBattle();
    //void Battle();
    void modeBattle();
    void drawBattle();
    void layoutBattle();
};

class Game
{
public:

    void run();
    void setValues();

private:
    void processEvents();
    void update();
    void update_enemy1();
    void render();

    sf::RenderWindow window;
    sf::Event event;
    sf::Texture characterTexture, backgroundTexture, enemy1Texture;
    sf::Sprite character, background, enemy1;

    float characterScaleX, characterScaleY;
    sf::Vector2f position;
    sf::Vector2f velocity_enemy1;

    // Adiciona variáveis para rastrear a animação em cada direção
    float frameAtualBaixo = 0.f;
    float frameAtualEsquerda = 0.f;
    float frameAtualDireita = 0.f;
    float frameAtualCima = 0.f;

    float frameAtualBaixo_enemy = 0.f;
    float frameAtualEsquerda_enemy = 0.f;
    float frameAtualDireita_enemy = 0.f;
    float frameAtualCima_enemy = 0.f;

    float velocidadeAnimacao = 0.01f;
    int linha;
};

class Graph {
private:

    struct element{
        bool used;
        float weight;
    };

    element* matrix;
    std::size_t n;

public:
    // Graph();
    //Graph(struct element, element *matrix , std::size_t n);
    Graph(std::size_t n);


    ~Graph();

    bool edge_exists(std::size_t from, std::size_t to) const;
    void add_edge(std::size_t from, std::size_t to,float);
    void rem_edge(std::size_t from, std::size_t to);
    void add_num_vertices();

    std::vector<std::size_t> neighbors(std::size_t v) const;

    std::size_t order() const;
    float peso_aresta(std::size_t u,std::size_t v) const;

    //Dijkstra
    void start(float* d, std::size_t* p,std::size_t s) const;
    void relax(float* d, std::size_t* p,std::size_t u,std::size_t v) const;
    bool exist_open(bool* open)const;
    std::size_t minimum_dist(bool* open,float* d) const;
    std::size_t* dijkstra(std::size_t s) const;
    std::vector<std::size_t> min_way(std::size_t u,std::size_t v) const;
    void print_min_caminh(std::size_t u,std::size_t v) const;
};

class SpaceMap:public Graph
{
public:
    SpaceMap(std::size_t nvertices):Graph(nvertices){}
    ~SpaceMap();
    void numVertices(std::size_t n);
    void update();
    void loopSpaceMap ();
    void render();
    void runSpaceMap ();
    void set_values();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Sprite Rocket;

    //std::vector<sf::CircleShape, std::allocator<sf::CircleShape>> worlds;
    //sf::CircleShape worldsArray[8];
    struct World{
        sf::CircleShape shape;
        bossFight Fight;
        Game game;
    };
    World* worlds;
    std::vector<sf::Vector2f> coordsWorlds;
    std::vector<float> sizeWorlds;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
};

class SpaceShip
{
    private:
    sf::RenderTexture texture;
    sf::Sprite sprite; 
    sf::Vector2f position;

    public:
    void move(std::vector<int>points);
    void render();
    void move_animation();
    void set_values();

};
/*class SpaceMap {
private:




    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Sprite Rocket;


    std::vector<sf::CircleShape> worlds;
    std::vector<sf::Vector2f> coordsWorlds;
    std::vector<float> sizeWorlds;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    Graph graphmap;

public:

    SpaceMap(std::size_t n);

    void numVertices(std::size_t n);
    void update();
    void loopSpaceMap ();
    void render();
    void runSpaceMap ();


};*/