#ifndef CODE_GAME_MENU_H
#define CODE_GAME_MENU_H

#include "SpaceMap.h"
#include <fstream>

class Menu {
private:
    int pos;
    bool pressed, theselect, selectedNewGame, selectedContinue;

    sf::RenderWindow * window;
    sf::RectangleShape * winclose;
    sf::Font * font;
    sf::Texture * image;
    sf::Sprite * bg;

    sf::Vector2i posMouse;
    sf::Vector2f mouseCoord;

    std::vector<std::string> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    void setValues();
    void loopEvents();
    void drawAll();

public:
    Menu();
    ~Menu();
    void runMenu();
};

#endif //CODE_GAME_MENU_H
