#include "SpaceMap.h"
#include "GameState.h"
#include <stack>
#include <sstream>
#include <fstream>

SpaceMap::~SpaceMap() {
    delete[] worlds;
}

void SpaceMap::runSpaceMap(Character& alien, Character& hero) {
    worlds = new World[order()];
    set_values();
    window.create(sf::VideoMode(1105, 961), "My window");
    window.setPosition(sf::Vector2i(0,0));
    backgroundTexture.loadFromFile("./Images/mapa_espacial.png");
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    background.setScale(scaleX,scaleY);
    background.setTexture(backgroundTexture);
    fix_scale(scaleX,scaleY);

    while (window.isOpen())
    {
        who_wins(alien,hero);
        if(!alien_wins && !hero_wins)
        {
            loopSpaceMap(alien, hero);
            render();
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                window.close();
            render_end(alien, hero);
        }
    }
}

void SpaceMap::set_values()
{
    add_edges_from_file();
    read_planets_data();
    for(std::size_t i=0;i<order();i++)
    {   
        std::string address ="./Images/mundo";
        std::stringstream ss;
        ss<<i;
        address= address + ss.str() + ".jpg";
        worlds[i].level_background.loadFromFile(address);
        worlds[i].level_sprite.setTexture(worlds[i].level_background);
        
        float scaleX = static_cast<float>(800) / worlds[i].level_background.getSize().x;
        float scaleY = static_cast<float>(600) / worlds[i].level_background.getSize().y;
        worlds[i].level_sprite.setScale(scaleX,scaleY);
    }
    rocketTexture.loadFromFile("./Images/ship.png");
    rocket.setTexture(rocketTexture);
    rocket.setOrigin(rocketTexture.getSize().x/2,rocketTexture.getSize().y/2);
    planet = 0;
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
    
    buttom_save.setSize(sf::Vector2f(130,30));
    buttom_save.setFillColor(sf::Color::Red);
    buttom_save.setOrigin(buttom_save.getSize().x/2.f,buttom_save.getSize().y/2.f);
    buttom_save.setPosition(716,105);

    buttom_quit.setSize(sf::Vector2f(105,30));
    buttom_quit.setFillColor(sf::Color::Blue); 
    buttom_quit.setOrigin(buttom_quit.getSize().x/2.f,buttom_quit.getSize().y/2.f);
    buttom_quit.setPosition(711,155);

    font.loadFromFile("ethn.otf");

    save_text.setFont(font);
    save_text.setString("Save");
    save_text.setCharacterSize(30);
    save_text.setOutlineColor(sf::Color::Black);
    save_text.setPosition(655,87);

    quit_text.setFont(font);
    quit_text.setString("Quit");
    quit_text.setCharacterSize(30);
    quit_text.setOutlineColor(sf::Color::Black);
    quit_text.setPosition(664,137);

    heroEndTexture.loadFromFile("./Images/Win_screen.png");
    heroEnd.setTexture(heroEndTexture);

    alienEndTexture.loadFromFile("./Images/GameOver_screen.png");
    alienEnd.setTexture(alienEndTexture);
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

void SpaceMap::fix_scale(float scaleX,float scaleY)
{
    sf::Vector2f new_position;
    for (size_t i = 0; i < coordsWorlds.size(); i++)
    {
        coordsWorlds[i].x = coordsWorlds[i].x * scaleX;
        coordsWorlds[i].y = coordsWorlds[i].y * scaleY;
        new_position = worlds[i].shape.getPosition();
        new_position.x = new_position.x*scaleX;
        new_position.y = new_position.y*scaleY;
        worlds[i].shape.setPosition(new_position);
    }
    new_position = buttom_quit.getPosition();
    new_position.x = new_position.x*scaleX;
    new_position.y = new_position.y*scaleY;
    buttom_quit.setPosition(new_position);

    new_position = buttom_save.getPosition();
    new_position.x = new_position.x*scaleX;
    new_position.y = new_position.y*scaleY;
    buttom_save.setPosition(new_position);

    new_position=save_text.getPosition();
    new_position.x=new_position.x*scaleX;
    new_position.y=new_position.y*scaleY;
    save_text.setPosition(new_position);

    new_position=quit_text.getPosition();
    new_position.x=new_position.x*scaleX;
    new_position.y=new_position.y*scaleY;
    quit_text.setPosition(new_position);

    rocket.setPosition(coordsWorlds[0]);

    scaleX = static_cast<float>(window.getSize().x) / heroEndTexture.getSize().x;
    scaleY = static_cast<float>(window.getSize().y) / heroEndTexture.getSize().y;
    heroEnd.setScale(scaleX,scaleY);

    scaleX = static_cast<float>(window.getSize().x) / alienEndTexture.getSize().x;
    scaleY = static_cast<float>(window.getSize().y) / alienEndTexture.getSize().y;
    alienEnd.setScale(scaleX,scaleY);
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
                track=min_way(planet,order()-1);
                    move_ship();
                Fight.modeBattle(alien, hero);
            }
            for (std::size_t i = 0; i < order() - 1; ++i) {
                if(worlds[i].shape.getGlobalBounds().contains(mouse_coord)){
                    track=min_way(planet,i);
                    move_ship();
                    worlds[i].game.run(worlds[i].level_sprite,hero,equipment[i]);
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
        } else enterWorld = false;
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
    }
    planet = track.back();
}

void SpaceMap::render() {
    window.clear();
    window.draw(background);
    window.draw(rocket);
    for (int i = 0; i < order(); ++i) {
        window.draw(worlds[i].shape);
    }
    window.draw(buttom_save);
    window.draw(buttom_quit);
    window.draw(save_text);
    window.draw(quit_text);
    window.display();
}

void SpaceMap::who_wins(Character &alien, Character &hero)
{
    if(alien.hp<=0)
        hero_wins = true;
    if(hero.hp<=0)
        alien_wins = true;
}

void SpaceMap::render_end(Character &alien, Character &hero)
{   
    window.clear();
    if(hero_wins)
        window.draw(heroEnd);
    if(alien_wins)
        window.draw(alienEnd);
    window.display();
}

