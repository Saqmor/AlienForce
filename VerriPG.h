#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

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
    void update_enemy();
    void clash();
    void render();
    sf::RenderWindow window;
    sf::Event event;
    sf::Texture characterTexture, backgroundTexture, enemieTexture;
    sf::Sprite character, background, enemie;
    float character_hp =300;

    float characterScaleX, characterScaleY;
    sf::Vector2f velocity;

    // Adiciona variáveis para rastrear a animação em cada direção
    float frameAtualBaixo = 0.f;
    float frameAtualEsquerda = 0.f;
    float frameAtualDireita = 0.f;
    float frameAtualCima = 0.f;

    float frameAtualBaixo_enemie = 0.f;
    float frameAtualEsquerda_enemie = 0.f;
    float frameAtualDireita_enemie = 0.f;
    float frameAtualCima_enemie = 0.f;

    float velocidadeAnimacao = 0.01f;
    int linha;
};


