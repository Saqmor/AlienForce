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
    setValues();
    window.create(sf::VideoMode(1105, 961), "My window");
    window.setPosition(sf::Vector2i(0,0));
    backgroundTexture.loadFromFile("./Images/mapa_espacial.png");
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    background.setScale(scaleX,scaleY);
    background.setTexture(backgroundTexture);
    fixScale(scaleX,scaleY);

    while (window.isOpen())
    {
        whoWins(alien,hero);
        if(!alienWins && !heroWins)
        {
            loopSpaceMap(alien, hero);
            render();
        }
        else
        {
            renderEnd(alien, hero);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && endPressed)
                window.close();
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                endPressed = true;
        }
    }
}
void SpaceMap::setLayout()
{
    for (std::size_t i = 0; i < order(); ++i) {
         std::string address ="./Images/mundo";
        std::stringstream ss;
        ss<<i;
        address= address + ss.str() + ".jpg";
        worlds[i].levelBackground.loadFromFile(address);
        worlds[i].levelSprite.setTexture(worlds[i].levelBackground);
        float scaleX = static_cast<float>(800) / worlds[i].levelBackground.getSize().x;
        float scaleY = static_cast<float>(600) / worlds[i].levelBackground.getSize().y;
        worlds[i].levelSprite.setScale(scaleX,scaleY);
        worlds[i].shape.setRadius(sizeWorlds[i]);
        worlds[i].shape.setFillColor(sf::Color::Transparent);
        worlds[i].shape.setOrigin(worlds[i].shape.getRadius(),worlds[i].shape.getRadius());
        worlds[i].shape.setPosition(coordsWorlds[i]);
    }
    buttomSave.setSize(sf::Vector2f(130,30));
    buttomSave.setFillColor(sf::Color::Red);
    buttomSave.setOrigin(buttomSave.getSize().x/2.f,buttomSave.getSize().y/2.f);
    buttomSave.setPosition(716,105);

    buttomQuit.setSize(sf::Vector2f(105,30));
    buttomQuit.setFillColor(sf::Color::Blue); 
    buttomQuit.setOrigin(buttomQuit.getSize().x/2.f,buttomQuit.getSize().y/2.f);
    buttomQuit.setPosition(711,155);

    font.loadFromFile("./System/ethn.otf");

    saveText.setFont(font);
    saveText.setString("Save");
    saveText.setCharacterSize(30);
    saveText.setOutlineColor(sf::Color::Black);
    saveText.setPosition(655,87);

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(30);
    quitText.setOutlineColor(sf::Color::Black);
    quitText.setPosition(664,137);

    heroEndTexture.loadFromFile("./Images/Win_screen.png");
    heroEnd.setTexture(heroEndTexture);

    alienEndTexture.loadFromFile("./Images/GameOver_screen.png");
    alienEnd.setTexture(alienEndTexture);
}
void SpaceMap::setValues()
{
    addEdgesFromFile();
    readPlanetsData();
    setLayout();
    rocketTexture.loadFromFile("./Images/ship.png");
    rocket.setTexture(rocketTexture);
    rocket.setOrigin(rocketTexture.getSize().x/2,rocketTexture.getSize().y/2);
    planet = 0;
    rocketPosition = rocket.getPosition();
    rocket.setScale(0.5f,0.5f);
    posMouse = {0,0};
    mouseCoord = {0, 0};
}

void SpaceMap::readPlanetsData(){
    std::ifstream is;
    is.open("./System/coords_worlds.txt");
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

void SpaceMap::fixScale(float scaleX,float scaleY)
{
    sf::Vector2f newPosition;
    for (size_t i = 0; i < coordsWorlds.size(); i++)
    {
        coordsWorlds[i].x = coordsWorlds[i].x * scaleX;
        coordsWorlds[i].y = coordsWorlds[i].y * scaleY;
        newPosition = worlds[i].shape.getPosition();
        newPosition.x = newPosition.x*scaleX;
        newPosition.y = newPosition.y*scaleY;
        worlds[i].shape.setPosition(newPosition);
    }
    newPosition = buttomQuit.getPosition();
    newPosition.x = newPosition.x*scaleX;
    newPosition.y = newPosition.y*scaleY;
    buttomQuit.setPosition(newPosition);

    newPosition = buttomSave.getPosition();
    newPosition.x = newPosition.x*scaleX;
    newPosition.y = newPosition.y*scaleY;
    buttomSave.setPosition(newPosition);

    newPosition=saveText.getPosition();
    newPosition.x=newPosition.x*scaleX;
    newPosition.y=newPosition.y*scaleY;
    saveText.setPosition(newPosition);

    newPosition=quitText.getPosition();
    newPosition.x=newPosition.x*scaleX;
    newPosition.y=newPosition.y*scaleY;
    quitText.setPosition(newPosition);

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
        posMouse = sf::Mouse::getPosition(window);
        mouseCoord = window.mapPixelToCoords(posMouse);

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && !enterWorld){
            enterWorld = true;
            for (std::size_t i = 0; i < order(); ++i) {
                if(worlds[i].shape.getGlobalBounds().contains(mouseCoord)){
                    track=minWay(planet,i);
                    moveShip();
                    if (i == order() - 1)
                        Fight.modeFight(alien, hero);
                    else
                    worlds[i].level.run(worlds[i].levelSprite,hero,equipment[i]);
                }
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(buttomSave.getGlobalBounds().contains(mouseCoord)){
                    CharactersSave(hero, alien);
                }
                if (buttomQuit.getGlobalBounds().contains(mouseCoord))
                {
                    CharactersSave(hero, alien);
                    window.close();
                }
            }
        } else enterWorld = false;
    }
}

float SpaceMap::setAngle(sf::Vector2f direction)
{
    float angle;
    if(direction.x>0)
        if(direction.y>0)
            angle = M_PI_2 + std::abs(std::acos(direction.x));
        else
            angle = M_PI_2 - std::abs(std::acos(direction.x));
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
void SpaceMap::moveShip()
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

        angle = setAngle(velocity);
        velocity = velocity *2.f;
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
    window.draw(buttomSave);
    window.draw(buttomQuit);
    window.draw(saveText);
    window.draw(quitText);
    window.display();
}

void SpaceMap::whoWins(Character &alien, Character &hero)
{
    if(alien.hp<=0)
        heroWins = true;
    if(hero.hp<=0)
        alienWins = true;
}

void SpaceMap::renderEnd(Character &alien, Character &hero)
{   
    window.clear();
    if(heroWins)
        window.draw(heroEnd);
    if(alienWins)
        window.draw(alienEnd);
    window.display();
}
void SpaceMap::nameBombs(Character &alien, Character &hero)
{
    std::vector<std::string> typeBombs={"IceBomb","FireBomb","PoisonBomb","Flashbang"};
    for (int i = 0; i < 4; ++i) 
    {
        hero.grenades[i].type = typeBombs[i];
        hero.grenades[i].full = false;
        alien.grenades[i].type = typeBombs[i];
        alien.grenades[i].full = false;
    }
}
void SpaceMap::initializeBombs(Character &alien, Character &hero)
{   
    hero.name = "hero";
    alien.name = "alien";
    alien.hp = 700;
    alien.speed = 25;
    hero.hp = 250;
    hero.speed = 12;
    hero.grenades = new Grenade[4];
    alien.grenades = new Grenade[4];
}
void SpaceMap::desinitializeBombs(Character &alien, Character &hero)
{
    delete[] hero.grenades;
    delete[] alien.grenades;
}
void SpaceMap::setLayoutBombs(Character &alien, Character &hero)
{
    std::vector<sf::Vector2f> scales= {{0.15f,0.15f},{0.2f,0.2f},{0.1f,0.1f},{0.5f,0.5f}};
    std::vector<sf::Vector2f> positions = {{400,500},{400,525},{400,500},{600,230}};
    for(size_t i=0;i<4;i++)
    {   
        std::string address = "./Images/" + hero.grenades[i].type + ".png";
        hero.grenades[i].bombTexture.loadFromFile(address);
        hero.grenades[i].bombSprite.setScale(scales[i]);
        hero.grenades[i].bombSprite.setPosition(positions[i]);
        hero.grenades[i].bombSprite.setTexture(hero.grenades[i].bombTexture);
        sf::Vector2f centerM(hero.grenades[i].bombTexture.getSize().x/2.f,hero.grenades[i].bombTexture.getSize().y/2.f);
        hero.grenades[i].bombSprite.setOrigin(centerM);
        hero.grenades[i].bombSprite.setPosition(400,500);
    }

}

