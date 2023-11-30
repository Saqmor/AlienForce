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
    void setValues();
    void readPlanetsData();
    void loopSpaceMap (Character& alien, Character& hero);
    void render();
    void moveShip();
    float setAngle(sf::Vector2f direction);
    void fixScale(float scaleX,float scaleY);
    void renderEnd(Character &alien, Character &hero);
    void whoWins(Character &alien, Character &hero);

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Texture heroEndTexture;
    sf::Sprite heroEnd;
    sf::Texture alienEndTexture;
    sf::Sprite alienEnd;

    sf::RectangleShape buttomSave;
    sf::RectangleShape buttomQuit;
    sf::Font font; 
    sf::Text saveText;
    sf::Text quitText;

    sf::Texture rocketTexture;
    sf::Sprite rocket;
    sf::Vector2f rocketPosition;
    std::size_t planet;
    std::vector<std::size_t> track;
    bool print = false;
    bool enterWorld = true;
    struct World{
        sf::CircleShape shape;
        Game game;
        sf::Texture levelBackground; 
        sf::Sprite levelSprite;
    };
    bossFight Fight;
    World* worlds;
    std::vector<sf::Vector2f> coordsWorlds;
    std::vector<float> sizeWorlds;
    std::vector<std::string> equipment;
    sf::Vector2i posMouse;
    sf::Vector2f mouseCoord;
    bool heroWins=false;
    bool alienWins=false;
};

