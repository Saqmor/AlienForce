#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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