#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <queue>
#include <fstream>
#include <sstream>


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
    int read_base();
};


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

<<<<<<< HEAD

    int pos_opBattle;
    bool pressed_opBattle, theselect_opBattle;
=======
>>>>>>> b522df91163a24b8e126b0e58a6d3d23954329c4

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
<<<<<<< HEAD
};
=======
};

class Game
{
public:

    void run(sf::Sprite);
    void setValues();

private:
    void processEvents();
    void update();
    void update_enemy1();
    void render(sf::Sprite);

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
    void add_edges_from_file();
    void add_edges_from_file2(std::string);

    void show_all_edges();

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
    void move_ship();
    float set_angle(sf::Vector2f direction);
    void read_planets_data();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Texture rocketTexture;
    sf::Sprite rocket;
    sf::Vector2f rocketPosition;
    std::size_t planet;
    std::vector<std::size_t>track;
    bool print = false;

    bool enterWorld = true;
    //std::vector<sf::CircleShape, std::allocator<sf::CircleShape>> worlds;
    //sf::CircleShape worldsArray[8];
    struct World{
        sf::CircleShape shape;
        bossFight Fight;
        Game game;
        sf::Texture level_background; 
        sf::Sprite level_sprite;
    };
    World* worlds;
    std::vector<sf::Vector2f> coordsWorlds;
    std::vector<float> sizeWorlds;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
};

class SpaceShip
{

    public:
    void move(std::vector<int>points);
    void render();
    void move_animation();
    void set_values();

};
>>>>>>> b522df91163a24b8e126b0e58a6d3d23954329c4
