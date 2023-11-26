#include "SpaceMap.h"
#include "GameState.h"
#include <stack>
#include <sstream>
#include <fstream>

Graph::Graph(std::size_t nvertices) {
    n = nvertices;
    matrix = new element[(n*(n+1))/2]{false,0};
}

Graph::~Graph() {
    delete[] matrix;
}

bool Graph::edge_exists(std::size_t u, std::size_t v) const {
    if (u < v){
        std::swap(u, v);
    }
    return matrix[u*(u+1)/2+v].used;
}

void Graph::add_edge(std::size_t u, std::size_t v,float w) {
    if (u < v){
        std::swap(u, v);
    }
    matrix[u*(u+1)/2+v].used = true;
    matrix[u*(u+1)/2+v].weight = w;
}

void Graph::rem_edge(std::size_t u, std::size_t v) {
    if (u < v){
        std::swap(u, v);
    }
    matrix[u*(u+1)/2+v].used = false;
}

std::vector<std::size_t> Graph::neighbors(std::size_t v) const {
    std::vector<std::size_t> neigh;
    for (std::size_t from = 0; from < n; ++from){
        if (edge_exists(from, v))
            neigh.push_back(from);
    }
    return neigh;
}

std::size_t Graph::order() const {
    return n;
}

float Graph::peso_aresta(std::size_t u,std::size_t v)const{
    if (u < v){
        std::swap(u,v);
    }
    return matrix[u*(u+1)/2+v].weight;
}

void Graph::start(float* d, std::size_t* p,std::size_t s) const{
    for(std::size_t i=0; i<n;i++){
        d[i]=std::numeric_limits<float>::max()/2;
        p[i]=10*n;
    }
    d[s]=0;
}

void Graph::relax(float* d, std::size_t* p,std::size_t u,std::size_t v) const{
    if(d[u]+ peso_aresta(u,v)<d[v]){
        d[v]=d[u]+ peso_aresta(u,v);
        p[v]=u;
    }
}

bool Graph::exist_open(bool* open)const{
    for(std::size_t i=0; i<n; i++){
        if(open[i])
            return true;
    }
    return false;
}

std::size_t Graph::minimum_dist(bool* open,float* d) const{
    std::size_t i,min;

    for(i=0; i<n; i++){
        if(open[i])
            break;
    }
    min=i;

    for(i=min+1; i<n; i++){
        if(open[i] && d[min]>d[i])
            min=i;
    }
    return min;
}

std::size_t* Graph::dijkstra(std::size_t s) const{
    float* d = new float[n];
    std::size_t* p = new std::size_t[n];
    bool* open = new bool[n];

    for(std::size_t i=0; i<n; i++){
        open[i]=true;
    }

    start(d,p,s);

    while(exist_open(open)){
        std::size_t u = minimum_dist(open,d);
        open[u]=false;

        for(std::size_t i: neighbors(u)){
            if(open[i]){
                relax(d,p,u,i);
            }
        }
    }
    return p;
}


std::vector<std::size_t> Graph::min_way(std::size_t u,std::size_t v) const{

    auto p=dijkstra(u);
    std::stack<std::size_t> aux;
    std::vector<std::size_t> min_way;

    for(std::size_t i=v; i!=u; i=p[i]){
        aux.push(i);
    }

    min_way.push_back(u);
    while(!aux.empty()){
        min_way.push_back(aux.top());
        aux.pop();
    }
    return min_way;
}

void Graph::print_min_caminh(std::size_t u,std::size_t v) const{
    auto m = min_way(u,v);

    std::cout<<std::endl;
    for(std::size_t i=0; i<m.size();i++){
        std::cout<<m[i];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}

void Graph::add_num_vertices() {
    std::cin >> n;
}

void Graph::add_edges_from_file(){
    std::ifstream is;
    std::size_t u,v;
    float w;

    is.open("graph_input.txt");
    is>>w;
    while(is>>u>>v>>w)
        add_edge(u,v,w);
    is.close();
}


void Graph::add_edges_from_file2(std::string name_file){
    std::ifstream is;
    std::size_t u,v;
    float w;

    is>>w;
    is.open(name_file);
    while(is>>u>>v>>w)
        add_edge(u,v,w);
    is.close();
}

void Graph::show_all_edges(){
    std::size_t u,v;

    for(u=0; u<n; u++){
        for(v=u; v<n; v++){
            if(edge_exists(u,v)){
                std::cout<<u<<" "<<v<<" "<<peso_aresta(u,v)<<std::endl;
            }
        }
    }
}


//deletar os ponteiros de struct
SpaceMap::~SpaceMap() {
}

void SpaceMap::read_planets_data(){
    std::ifstream is;
    is.open("coords_worlds.txt");
    float a,b,r;
    std::string word;
    for (std::size_t i = 0; i < order(); i++){
        is>>a>>b>>r>>word;
        coordsWorlds.emplace_back(a, b);
        sizeWorlds.push_back(r);
        equipment.push_back(word);
    }
    is.close();
}

void SpaceMap::set_values()
{
    std::size_t from, to;
    float weight;
    add_edges_from_file();
    read_planets_data();
    //while(std::cin >> from >> to >> weight)
      //  add_edge(from, to, weight);
    //coordsWorlds = {{588,855},{280,685},{786,757},{457,501},{650,394},{822,264},{321,290},{510,120}};
    //sizeWorlds = {50, 57, 39, 52, 36, 59, 48, 53};
    for(std::size_t i=0;i<order();i++)
    {   
        std::string address ="./Images/mundo";
        std::stringstream ss;
        ss<<i;
        address= address + ss.str() + ".jpg";
        worlds[i].level_background.loadFromFile(address);
        worlds[i].level_sprite.setTexture(worlds[i].level_background);
    }
    rocketTexture.loadFromFile("./Images/ship.png");
    rocket.setTexture(rocketTexture);
    rocket.setOrigin(rocketTexture.getSize().x/2,rocketTexture.getSize().y/2);
    rocket.setPosition(coordsWorlds[7]);
    planet =7;
    rocketPosition = rocket.getPosition();
    rocket.setScale(0.5f,0.5f);

    for (std::size_t i = 0; i < order(); ++i) {
        worlds[i].shape.setRadius(sizeWorlds[i]);
        worlds[i].shape.setFillColor(sf::Color::Transparent);
        worlds[i].shape.setOrigin(worlds[i].shape.getRadius(),worlds[i].shape.getRadius());
        worlds[i].shape.setPosition(coordsWorlds[i]);
    }
    pos_mouse = {0,0};
    mouse_coord = {0, 0};
//......................................................................................//  
    buttom_save.setSize(sf::Vector2f(80,40));
    buttom_quit.setSize(sf::Vector2f(80,40));
    buttom_save.setFillColor(sf::Color::Red);
    buttom_quit.setFillColor(sf::Color::Blue);
    buttom_save.setOrigin(buttom_save.getSize().x/2.f,buttom_save.getSize().y/2.f);
    buttom_quit.setOrigin(buttom_quit.getSize().x/2.f,buttom_quit.getSize().y/2.f);
    buttom_save.setPosition(700,100);
    buttom_quit.setPosition(700,200);
//..........................................................................................//
    font.loadFromFile("ethn.otf");

    save_text.setFont(font);
    save_text.setString("Save");
    save_text.setCharacterSize(20);
    save_text.setOutlineColor(sf::Color::Black);
    save_text.setPosition(700,100);

    quit_text.setFont(font);
    quit_text.setString("Quit");
    quit_text.setCharacterSize(20);
    quit_text.setOutlineColor(sf::Color::Black);
    quit_text.setPosition(700,200);
//..........................................................................................//
}

void SpaceMap::loopSpaceMap(Character& alien, Character& hero) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if( event.type == sf::Event::Closed) {
            window.close();
        }
        pos_mouse = sf::Mouse::getPosition(window);
        mouse_coord = window.mapPixelToCoords(pos_mouse);

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && !enterWorld){
            enterWorld = true;
            if(worlds[order() - 1].shape.getGlobalBounds().contains(mouse_coord)){
                worlds[order() - 1].Fight.modeBattle(alien, hero);
            }
            for (std::size_t i = 0; i < order() - 1; ++i) {
                if(worlds[i].shape.getGlobalBounds().contains(mouse_coord)){
                    track=min_way(planet,i);
                    move_ship();
                    worlds[i].game.run(worlds[i].level_sprite,hero,equipment[i]);
                    //indo do planet -> i;
                }
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(buttom_save.getGlobalBounds().contains(mouse_coord)){
                    CharactersSave(hero, alien);
                }
                if (buttom_quit.getGlobalBounds().contains(mouse_coord))
                {
                    CharactersSave(hero, alien);
                    window.close();
                }
                
            }

        }
        enterWorld = false;
    }
}

void SpaceMap::render() {
    window.clear();
    window.draw(background);
    window.draw(rocket);
    for (int i = 0; i < order(); ++i) {
        window.draw(worlds[i].shape);
    }
    //window.draw(character);
    //window.draw(worlds);
//..............................................//
    window.draw(buttom_save);
    window.draw(buttom_quit);
    window.draw(save_text);
    window.draw(quit_text);

//................................................//
    window.display();
}


void SpaceMap::runSpaceMap(Character& alien, Character& hero) {
    worlds = new World[order()];
    set_values();
    window.create(sf::VideoMode(1105, 961), "My window");
    window.setPosition(sf::Vector2i(0,0));
    backgroundTexture.loadFromFile("./Images/mapa_espacial.png");
    
    background.setTexture(backgroundTexture);
    while (window.isOpen())
    {
        loopSpaceMap(alien, hero);
        render();
    }
}
float SpaceMap::set_angle(sf::Vector2f direction)
{
    float angle;
    if(direction.x>0)
       if(direction.y>0)
            angle = M_PI_2 + std::abs(std::acos(direction.x));
        else
            angle =M_PI-2 - std::abs(std::acos(direction.x));
    if(direction.x<=0)
        if(direction.y>0)
        {   
            sf::Vector2f scale=rocket.getScale();
            rocket.setScale(scale.x,-scale.y);
            angle=std::abs(std::asin(direction.y));
        }
        else
            angle=-std::abs(std::asin(direction.y));
    angle =(angle *180)/M_PI;
    return angle;
}
void SpaceMap::move_ship()
{   
    sf::Vector2f velocity;
    for(std::size_t i =0;i<track.size()-1;i++)
    {   
        double angle = std::atan2((coordsWorlds[track[i+1]].y-coordsWorlds[track[i]].y),
        (coordsWorlds[track[i+1]].x-coordsWorlds[track[i]].x));
        if(coordsWorlds[track[i+1]].x>coordsWorlds[track[i]].x)
            velocity.x =std::abs(std::cos(angle));
        else
            velocity.x =-std::abs(std::cos(angle));
        if(coordsWorlds[track[i+1]].y>coordsWorlds[track[i]].y)
            velocity.y=std::abs(std::sin(angle));
        else
            velocity.y=-std::abs(std::sin(angle));
        angle = set_angle(velocity);
        velocity = velocity *3.f;
        rocket.setRotation(angle);
        print = true;
        while(std::abs(rocket.getPosition().x-(coordsWorlds[track[i+1]]).x)>2)
        {   
            rocket.setPosition(rocket.getPosition() + velocity*0.2f);
            window.clear();
            window.draw(background);
            window.draw(rocket);
            for (int i = 0; i < order(); ++i)
                window.draw(worlds[i].shape);
            window.display();   
        }
        rocket.setPosition(coordsWorlds[track[i+1]]);
        rocket.setRotation(0);
        rocket.setScale(0.5f,0.5f);
       //Movimentação Mouse (Melhorar orientação)
    /*
    if (event.type == sf::Event::MouseButtonPressed) {
    // Atualização da posição do objeto pela posição do mouse quando ocorre um clique
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        velocity.x=1.f;
        velocity.y=1.f;
        sf::Vector2f characterPosition = character.getPosition();
        
        if(mousePosition.x>characterPosition.x)
        velocity.x=1.5*std::cos(std::fabs(angle));
        else
        velocity.x=1.5*std::cos(-std::fabs(angle));
        if(mousePosition.y>characterPosition.y)
        velocity.y=1.5*std::sin(std::fabs(angle));
        else
        velocity.y=1.5*std::sin(-std::fabs(angle));
    } */ 
    }
    planet = track.back();
}
