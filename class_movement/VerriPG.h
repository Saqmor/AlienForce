#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

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
};


