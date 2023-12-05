#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "bossFight.h"
#include "Graph.h"

class Levels
{
public:

    void run(sf::Sprite,Character& hero,std::string);

private:
    void setValues();
    void processEvents();
    void update(Character& hero,std::string);
    void updateEnemy();
    void render(sf::Sprite,Character& hero,std::string);
    void takeOutBomb(Character &hero,std::string);

    sf::RenderWindow window;
    sf::Event event;
    sf::Texture playerTexture, backgroundTexture, enemyTexture,
    poisonBombTexture, iceBombTexture, fireBombTexture, flashbangTexture;
    sf::Sprite player, background, enemy, poisonBomb, iceBomb, fireBomb, flashbang;
    sf::Vector2f velocityEnemy;

    float currentDownFrames = 0.f;
    float currentLeftFrames = 0.f;
    float currentRightFrames = 0.f;
    float currentUpFrames = 0.f;
    float currentLeftFramesEnemy = 0.f;
    float currentRightFramesEnemy = 0.f;
    float velocityAnimation = 0.007f;
    int lineAnimation=0;
};