#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "bossFight.h"

class Game
{
public:

    void run(sf::Sprite,Hero &hero,std::string);
    void setValues();

private:
    void processEvents();
    void update();
    void update_enemy1();
    void render(sf::Sprite,struct Hero &hero,std::string);

    sf::RenderWindow window;
    sf::Event event;
    sf::Texture characterTexture, backgroundTexture, enemy1Texture,
    poisonBombTexture,iceBombTexture,fireBombTexture,flashbangTexture;
    
    sf::Sprite character, background, enemy1,poisonBomb,iceBomb,fireBomb,flashbang;

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