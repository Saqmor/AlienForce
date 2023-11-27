#include "Levels.h"
#include "bossFight.h"

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
    void loopSpaceMap (Character& alien, Character& hero);
    void render();
    void runSpaceMap (Character& alien, Character& hero);
    void set_values();
    void move_ship();
    float set_angle(sf::Vector2f direction);
    void read_planets_data();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

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
    std::vector<std::string> equipment;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
};
