#include "VerriPG.h"

Menu::Menu(){
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu(){
    delete window;
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::set_values(){
    window->create(sf::VideoMode(1280,720), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(0,0));

    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("./ethn.otf");
    image->loadFromFile("./Images/menu.png");

    bg->setTexture(*image);

    pos_mouse = {0,0};
    mouse_coord = {0, 0};

    options = {"Alienverse: Cosmic Invasion", "New game", "Continue", "About", "Quit"};
    texts.resize(5);
    coords = {{572,40},{585,191},{583,280},{600,370},{623,457}};
    sizes = {25,21,24,24,24};

    for (std::size_t i{}; i < texts.size(); ++i){
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Green);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(23,26));
    winclose->setPosition(1178,39);
    winclose->setFillColor(sf::Color::Transparent);

}

void Menu::loop_events(){
    sf::Event event;
    while(window->pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window->close();
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed){
            if( pos < 4){
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed){
            if( pos > 1){
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
            theselect = true;
            switch (pos) {
                case 1:
                    // Code for "Play" option
                    selectedPlay = true;
                    window->close();
                    break;
                case 2:
                    // Code for "Options" option
                    std::cout << "Options selected!\n";
                    break;
                case 3:
                    // Code for "About" option
                    std::cout << "About selected!\n";
                    break;
                case 4:
                    // Code for "Quit" option
                    window->close();
                    break;
                default:
                    break;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(winclose->getGlobalBounds().contains(mouse_coord)){
                //std::cout << "Close the window!" << '\n';
                window->close();
            }
        }
    }
}

void Menu::draw_all(){
    window->clear();
    window->draw(*bg);
    for(auto t : texts){
        window->draw(t);
    }
    window->display();
}

void Menu::run_menu(){
    selectedPlay = false;
    while(window->isOpen()){
        loop_events();
        draw_all();
    }
    if (selectedPlay){
        SpaceMap space(read_base());
        space.runSpaceMap();
    }
}

int Menu::read_base(){
    std::ifstream is;
    int vertex;
    is.open("graph_input.txt");
    is>>vertex;
    is.close();
    return vertex;

}



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
    for (std::size_t i = 0; i < order(); i++){
        is>>a>>b>>r;
        coordsWorlds.emplace_back(a, b);
        sizeWorlds.push_back(r);
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
        worlds[i].shape.setFillColor(sf::Color::Green);
        worlds[i].shape.setOrigin(worlds[i].shape.getRadius(),worlds[i].shape.getRadius());
        worlds[i].shape.setPosition(coordsWorlds[i]);
    }
    /*worlds.setRadius(sizeWorlds[0]);
    worlds.setFillColor(sf::Color::Green);
    worlds.setPosition(coordsWorlds[0]);*/

    pos_mouse = {0,0};
    mouse_coord = {0, 0};
}
/*void SpaceMap::createGraph(std::size_t nvertices) {
    Graph graphMap(nvertices);
    //graphMap->add_num_vertices();
    std::size_t from, to;
    float weight;
    while(std::cin >> from >> to >> weight)
        graphMap.add_edge(from, to, weight);
    numVertices(graphMap.order());
}*/

void SpaceMap::loopSpaceMap() {
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
                worlds[order() - 1].Fight.modeBattle();
            }
            for (std::size_t i = 0; i < order() - 1; ++i) {
                if(worlds[i].shape.getGlobalBounds().contains(mouse_coord)){
                    track=min_way(planet,i);
                    move_ship();
                    worlds[i].game.run(worlds[i].level_sprite);
                    //indo do planet -> i;
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
    window.display();
}


void SpaceMap::runSpaceMap() {
    //createGraph();
    worlds = new World[order()];
    set_values();
    window.create(sf::VideoMode(1105, 961), "My window");
    window.setPosition(sf::Vector2i(0,0));
    backgroundTexture.loadFromFile("./Images/mapa_espacial.png");
    
    background.setTexture(backgroundTexture);
    while (window.isOpen())
    {
        loopSpaceMap();
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

int dice(int n) {
    std::random_device dev;
    auto gen = std::mt19937(dev());
    std::uniform_int_distribution<int> dist(1, n);
    return dist(gen);
}

bool prob(int n) {
    if (dice(100) <= n) {
        return true;
    } else {
        return false;
    }
}

void bossFight::attack1(){
    damageCondition();
    if (maxPriorityQueue.top() == hero.speed)
        alien.hp -= 7 + dice(8);
    if (maxPriorityQueue.top() == alien.speed){
        if (alien.lessAccuracy)
            hero.hp -= prob(85) ? 10 + 2 * dice(8) : 0;
        else hero.hp -= 10 + 2 * dice(8);
    }
    maxPriorityQueue.pop();
}


void bossFight::setValues() {
    choicesBomb = {"Ice Bomb", "Fire Bomb", "Poison Bomb", "Flashbang"};
    texts.resize(4);
    sizes = {20,20,20,20,20};
    coords_attack2 = {{15,500},{160,500},{325,500},{550,500}};

    for (std::size_t i{}; i < texts.size(); ++i){
        texts[i].setFont(font);
        texts[i].setString(choicesBomb[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Green);
        texts[i].setPosition(coords_attack2[i]);
    }
    texts[0].setOutlineThickness(4);
    posBomb = 0;
}

int bossFight::loopChooseBomb() {
    sf::Event event;
    while(window.pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterPrevState) {
            enterPrevState = true;
            switch (posBomb) {
                case 0:
                    return 1;
                case 1:
                    return 2;
                case 2:
                    return 3;
                case 3:
                    return 4;
                default:
                    break;
            }
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            // Se a tecla Enter não estiver pressionada, reinicia theselect_opBattle
            enterPrevState = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pressed) {
            if (posBomb < 3) {
                ++posBomb;
                pressed = true;
                texts[posBomb].setOutlineThickness(4);
                texts[posBomb - 1].setOutlineThickness(0);
                pressed = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed) {
            if (posBomb > 0) {
                --posBomb;
                pressed = true;
                texts[posBomb].setOutlineThickness(4);
                texts[posBomb + 1].setOutlineThickness(0);
                pressed = false;
            }
        }
    }
    return -1;
}

void bossFight::drawSpecialAttack() {
    window.clear();
    window.draw(background);
    window.draw(alien.roundedBoss);
    window.draw(hero.roundedHero);
    window.draw(hero.playerHp);
    window.draw(alien.bossHp);
    window.draw(alien.textBoss);
    window.draw(hero.textHero);
    window.draw(hero.heroSprite);
    window.draw(alien.bossSprite);
    for(auto t : texts){
        window.draw(t);
    }
    window.display();
}

int bossFight::runChooseBomb(){
    int num = -1;
    enterPrevState = true;
    setValues();
    while (num == -1){
        num = loopChooseBomb();
        drawSpecialAttack();
    }
    texts[posBomb].setOutlineThickness(0);
    return num;
}

void bossFight::attack2(){
    damageCondition();
    if (maxPriorityQueue.top() == alien.speed)
        hero.hp -= 60 + 2 * dice(12);
    if (maxPriorityQueue.top() == hero.speed){
        switch (runChooseBomb()) {
            case 1:
                alien.hp -=  prob(40) ? 50 + 2 * dice(20) : 0;
                alien.speed -= 20;
                break;
            case 2:
                alien.hp -=  prob(60) ? 120 + 2 * dice(20) : 0;
                alien.burn = true;
                break;
            case 3:
                alien.hp -=  prob(80) ? 40 + 2 * dice(20) : 0;
                alien.poison = true;
                break;
            case 4:
                alien.hp -=  prob(50) ? 50 + 2 * dice(20) : 0;
                alien.lessAccuracy = true;
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    }
    maxPriorityQueue.pop();
}


void bossFight::heal() {
    hero.hp += 8 + 1 * dice(6);
    maxPriorityQueue.pop();
}

void bossFight::defineTurns() {
    if (alien.speed >= 2 * hero.speed)
        maxPriorityQueue.push(alien.speed);
    if (hero.speed >= 2 * alien.speed)
        maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(hero.speed);
    maxPriorityQueue.push(alien.speed);
}

void bossFight::damageCondition() {
    if (alien.burn)
        alien.hp -= 4;
    if (alien.poison)
        alien.hp -= 7;
    if (alien.hp <= 0){
        alien.hp = 0;
        alien.isAlive = false;
    }
}

bool bossFight::Turn() {
    if (maxPriorityQueue.top() == alien.speed)
        enemyTurn();
    if ( playerTurn())
        return true;
    else return false;
}

bool bossFight::playerTurn() {

    // Verifica se a tecla Enter está pressionada
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect_opBattle) {
        // Verifica se o jogador ainda não selecionou a opção atual
        theselect_opBattle = true;
        std::cout << "entrou ";
        switch (pos_opBattle) {
            case 0:
                // Code for "Attack1" option
                attack1();
                break;
            case 1:
                // Code for "Attack2" option
                attack2();
                break;
            case 2:
                // Code for "Heal" option
                heal();
                break;
            case 3:
                // Code for "Run" option
                return false;
            default:
                break;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        // Se a tecla Enter não estiver pressionada, reinicia theselect_opBattle
        theselect_opBattle = false;
    }

    // Lógica para navegar entre as opções com as teclas direcionais
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !pressed_opBattle) {
        if (pos_opBattle < 3) {
            ++pos_opBattle;
            pressed_opBattle = true;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle - 1].setOutlineThickness(0);
            pressed_opBattle = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed_opBattle) {
        if (pos_opBattle > 0) {
            --pos_opBattle;
            pressed_opBattle = true;
            texts_opBattle[pos_opBattle].setOutlineThickness(4);
            texts_opBattle[pos_opBattle + 1].setOutlineThickness(0);
            pressed_opBattle = false;
        }
    }

    return true;
}


void bossFight::enemyTurn() {
    if (prob(90))
        attack1();
    else attack2();

    if (hero.hp <= 0){
        hero.hp = 0;
        hero.isAlive = false;
    }
}
void bossFight::layoutBattle()
{
    //Criação de retângulos envolventes
    roundedTexture.loadFromFile("./Images/rounded(5).png");
    hero.roundedHero.setTexture(roundedTexture);
    alien.roundedBoss.setTexture(roundedTexture);
    hero.roundedHero.setScale(-1.3f,0.4f);
    alien.roundedBoss.setScale(1.9f,0.4f);

    //Criação dos personagens
    hero.heroTexture.loadFromFile("./Images/hero.png");
    alien.bossTexture.loadFromFile("./Images/alien_boss_true.png");
    hero.heroSprite.setTexture(hero.heroTexture);
    alien.bossSprite.setTexture(alien.bossTexture);

    //Texto
    font_bar.loadFromFile("ethn.otf");
    alien.textBoss.setFont(font_bar);
    alien.textBoss.setString("Boss HP");
    alien.textBoss.setCharacterSize(12);
    hero.textHero.setFont(font_bar);
    hero.textHero.setString("Hero HP");
    hero.textHero.setCharacterSize(12);

    //Pintura
    hero.playerHp.setFillColor(sf::Color(144,238,144));
    alien.bossHp.setFillColor(sf::Color(144,238,144));
    alien.textBoss.setFillColor(sf::Color(0,128,128));
    hero.textHero.setFillColor(sf::Color(0,128,128));
    alien.roundedBoss.setColor(sf::Color(222,184,135));
    hero.roundedHero.setColor(sf::Color(222,184,135));

    //Posicionamento
    hero.playerHp.setPosition(600.f,400.f);
    alien.bossHp.setPosition(0,64.f);
    alien.roundedBoss.setPosition(-130.f,30.f);
    hero.roundedHero.setPosition(900.f,370.f);
    alien.textBoss.setPosition(20.f,40.f);
    hero.textHero.setPosition(705.f,380.f);

    // Ajusta a escala e posicionamento das Sprites Hero e Boss
    sf::Vector2f positionHero(hero.heroTexture.getSize().x,hero.heroTexture.getSize().y);
    sf::Vector2f positionBoss(alien.bossTexture.getSize().x, alien.bossTexture.getSize().y);
    positionHero.x = positionHero.x / 2;
    positionHero.y = positionHero.y / 2;
    positionBoss.x = positionBoss.x / 2;
    positionHero.y = positionBoss.y / 2;
    hero.heroSprite.setOrigin(positionHero);
    alien.bossSprite.setOrigin(positionBoss);
    hero.heroSprite.setPosition(150.f,380.f);
    alien.bossSprite.setPosition(650.f,370.f);
    alien.bossSprite.setScale(0.5f,0.5f);
    hero.heroSprite.setScale(0.5f,0.5f);

}
void bossFight::drawBattle()
{
    layoutBattle();

    window.clear();
    window.draw(background);
    window.draw(alien.roundedBoss);
    window.draw(hero.roundedHero);
    window.draw(hero.playerHp);
    window.draw(alien.bossHp);
    window.draw(alien.textBoss);
    window.draw(hero.textHero);
    window.draw(hero.heroSprite);
    window.draw(alien.bossSprite);
    for(auto t : texts_opBattle){
        window.draw(t);
    }
    window.display();
}
void bossFight::modeBattle()
{
    backgroundTexture.loadFromFile("./Images/background_battle_2.png");
    background.setTexture(backgroundTexture);
    window.create(sf::VideoMode(800,600),"My window");
    pressed_opBattle = theselect_opBattle = false;
    font.loadFromFile("./ethn.otf");
    //image->loadFromFile("");

    //bg->setTexture(*image);
    optionsBattle = {"Atirar", "Especial", "Curar", "Fugir"};
    texts_opBattle.resize(4);
    coords_opBattle = {{70,500},{229,500},{419,500},{600,500}};
    sizes_opBattle = {20,20,20,20,20};

    for (std::size_t i{}; i < texts_opBattle.size(); ++i){
        texts_opBattle[i].setFont(font);
        texts_opBattle[i].setString(optionsBattle[i]);
        texts_opBattle[i].setCharacterSize(sizes_opBattle[i]);
        texts_opBattle[i].setOutlineColor(sf::Color::Green);
        texts_opBattle[i].setPosition(coords_opBattle[i]);
    }
    texts_opBattle[0].setOutlineThickness(4);
    pos_opBattle = 0;


    defineTurns();
    bool endBattle = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (hero.isAlive && alien.isAlive && !endBattle){
                if (maxPriorityQueue.empty())
                    defineTurns();
                if (!Turn())
                    endBattle = true;
                if (!alien.isAlive)
                    endBattle = true;
                if (!hero.isAlive)
                    endBattle = true;
            }
            if (endBattle)
                window.close();


            hero.playerHp.setSize(sf::Vector2f(hero.hp, 13));
            alien.bossHp.setSize(sf::Vector2f(0.45*alien.hp, 13));

        }
        drawBattle();
    }


}


void Game::setValues() {
    window.create(sf::VideoMode(800, 600), "My window");
    characterScaleX = 1.f;
    characterScaleY = 1.f;
    characterTexture.loadFromFile("./Images/chiefsheet.png");
    //backgroundTexture.loadFromFile("./Images/fundo.png");
    enemy1Texture.loadFromFile("./Images/enemy1.png");

    character.setTexture(characterTexture);
    //background.setTexture(backgroundTexture);
    enemy1.setTexture(enemy1Texture);

    // Ajusta a escala inicial junto com o centro da figura

    sf::Vector2f centerM(enemy1Texture.getSize().x,enemy1Texture.getSize().y);
    centerM.x = centerM.x / 2;
    centerM.y = centerM.y / 2;
    enemy1.setOrigin(centerM);
}


void Game::run(sf::Sprite background_level)
{
    setValues();
    while (window.isOpen())
    {
        processEvents();
        update();
        update_enemy1();
        render(background_level);
    }
}

void Game::processEvents()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    sf::Vector2u textureSize = characterTexture.getSize();
    textureSize.x /= 4;  // Assumindo 4 frames na horizontal
    textureSize.y /= 4;  // Assumindo 4 frames na vertical

    float characterScaleX = 2.f;
    float characterScaleY = 2.f;
    character.setScale(characterScaleX, characterScaleY);
    sf::Vector2f velocity(0.f, 0.f);

    //Movimentação por setas
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // left key is pressed: move our character
        velocity.x = -0.1f;
        frameAtualDireita += velocidadeAnimacao;
        linha =1;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        velocity.x = 0.1f;
        frameAtualEsquerda += velocidadeAnimacao;
        linha=2;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = -std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        velocity.y = -0.1f;
        frameAtualCima += velocidadeAnimacao;
        linha =3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        velocity.y = 0.1f;
        frameAtualBaixo += velocidadeAnimacao;
        linha =0;
    }
    position = character.getPosition();

    // Verifica se o personagem está se movendo
    bool isMoving = (velocity.x != 0.f || velocity.y != 0.f);

    // Atualiza a lógica da animação
    if (isMoving) {
        // Calcula o frame atual baseado no tempo ou eventos de teclado
        // Substitua esta lógica com a sua própria animação

        if (velocity.x > 0.f) {

            if (frameAtualEsquerda > 4) {
                frameAtualEsquerda = 0.f;
            }
            //Seta qual figura vai aparecer
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualEsquerda) * textureSize.x, 2 * textureSize.y, textureSize.x, textureSize.y));
        } else if (velocity.x < 0.f) {

            if (frameAtualDireita > 4) {
                frameAtualDireita = 0.f;
            }
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualDireita) * textureSize.x, 1 * textureSize.y, textureSize.x, textureSize.y));
        }

        if (velocity.y < 0.f) {

            if (frameAtualCima > 4) {
                frameAtualCima = 0.f;
            }
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualCima) * textureSize.x, 3 * textureSize.y, textureSize.x, textureSize.y));
        } else if (velocity.y > 0.f) {

            if (frameAtualBaixo > 4) {
                frameAtualBaixo = 0.f;
            }
            character.setTextureRect(sf::IntRect(static_cast<int>(frameAtualBaixo) * textureSize.x, 0 * textureSize.y, textureSize.x, textureSize.y));
        }
    } else {
        // Se o personagem não estiver se movendo, exibir um frame parado
        character.setTextureRect(sf::IntRect(0, linha*textureSize.y, textureSize.x, textureSize.y));
    }

    //Movimentação Mouse (Melhorar orientação)
    /*
    if (event.type == sf::Event::MouseButtonPressed) {
    // Atualização da posição do objeto pela posição do mouse quando ocorre um clique
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        velocity.x=1.f;
        velocity.y=1.f;
        sf::Vector2f characterPosition = character.getPosition();
        double angle = std::atan2((mousePosition.y-characterPosition.y),(mousePosition.x-characterPosition.x));
        if(mousePosition.x>characterPosition.x)
        velocity.x=1.5*std::cos(std::fabs(angle));
        else
        velocity.x=1.5*std::cos(-std::fabs(angle));
        if(mousePosition.y>characterPosition.y)
        velocity.y=1.5*std::sin(std::fabs(angle));
        else
        velocity.y=1.5*std::sin(-std::fabs(angle));
    } */
    float velocidadeMovimento = 100.f;
    character.move(velocity * velocidadeMovimento * 0.016f);  // Multiplica pelo deltaTime
}
void Game::update_enemy1()
{
    sf::Vector2u textureSize = enemy1Texture.getSize();
    textureSize.x /= 4;  // Assumindo 4 frames na horizontal
    textureSize.y /= 4;  // Assumindo 4 frames na vertical

    float enemyScaleX =2.f;
    float enemyScaleY =2.f;

    enemy1.setScale(enemyScaleX, enemyScaleY);
    sf::Vector2f velocity =velocity_enemy1;

    if (velocity.x > 0.f) {
        frameAtualEsquerda_enemy += velocidadeAnimacao;
        if (frameAtualEsquerda_enemy > 4) {
            frameAtualEsquerda_enemy = 0.f;
        }
        //Seta qual figura vai aparecer
        enemy1.setTextureRect(sf::IntRect(static_cast<int>(frameAtualEsquerda_enemy) * textureSize.x, 2 * textureSize.y, textureSize.x, textureSize.y));
    } else if (velocity.x < 0.f) {
        frameAtualDireita_enemy += velocidadeAnimacao;
        if (frameAtualDireita_enemy > 4) {
            frameAtualDireita_enemy = 0.f;
        }
        enemy1.setTextureRect(sf::IntRect(static_cast<int>(frameAtualDireita_enemy) * textureSize.x, 1 * textureSize.y, textureSize.x, textureSize.y));
    }
    float velocidadeMovimento = 100.f;
    enemy1.move(velocity_enemy1 * velocidadeMovimento * 0.016f);
    sf::Vector2f position_enemy1=enemy1.getPosition();
    //Verifica se o personagem ultrapassou as bordas da janela
    if (position_enemy1.x <=0) {
        position_enemy1.x = 0;
        enemy1.setPosition(position_enemy1.x,200.f);
        velocity_enemy1.x=0.4f;
    } else if (position_enemy1.x > window.getSize().x - textureSize.x * enemyScaleX) {
        position_enemy1.x = window.getSize().x - textureSize.x * enemyScaleX;
        enemy1.setPosition(position_enemy1.x,200.f);
        velocity_enemy1.x = -0.4f;
    }
    position_enemy1 = enemy1.getPosition();
    enemy1.setPosition(position_enemy1.x,400.f);
}
void Game::render(sf::Sprite background_level)
{
    window.clear();
    window.draw(background_level);
    window.draw(character);
    window.draw(enemy1);
    window.display();
}