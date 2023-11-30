#include "Levels.h"
#include "bossFight.h"
#include "Graph.h"

class SpaceMap:public Graph
{
public:
    SpaceMap(std::size_t nvertices):Graph(nvertices){}
    ~SpaceMap();
    void numVertices(std::size_t n);
    void runSpaceMap (Character& alien, Character& hero);
    void set_values();
    void read_planets_data();
    void loopSpaceMap (Character& alien, Character& hero);
    void render();
    void move_ship();
    float set_angle(sf::Vector2f direction);
    void fix_scale(float scaleX,float scaleY);
    void render_end(Character &alien, Character &hero);
    void who_wins(Character &alien, Character &hero);

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Texture heroEndTexture;
    sf::Sprite heroEnd;
    sf::Texture alienEndTexture;
    sf::Sprite alienEnd;

    sf::RectangleShape buttom_save;
    sf::RectangleShape buttom_quit;
    sf::Font font; 
    sf::Text save_text;
    sf::Text quit_text;

    sf::Texture rocketTexture;
    sf::Sprite rocket;
    sf::Vector2f rocketPosition;
    std::size_t planet;
    std::vector<std::size_t>track;
    bool print = false;
    bool enterWorld = true;
    struct World{
        sf::CircleShape shape;
        Game game;
        sf::Texture level_background; 
        sf::Sprite level_sprite;
    };
    bossFight Fight;
    World* worlds;
    std::vector<sf::Vector2f> coordsWorlds;
    std::vector<float> sizeWorlds;
    std::vector<std::string> equipment;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    bool hero_wins=false;
    bool alien_wins=false;
};
