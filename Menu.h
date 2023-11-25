#ifndef CODE_GAME_MENU_H
#define CODE_GAME_MENU_H

#include "SpaceMap.h"
#include <fstream>

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

    std::vector<std::string> options;
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



#endif //CODE_GAME_MENU_H
