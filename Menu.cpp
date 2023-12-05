#include "Menu.h"
#include "GameState.h"


Menu::Menu(){
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    setValues();
}

Menu::~Menu(){
    delete window;
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::setValues(){
    window->create(sf::VideoMode(1280,720), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(0,0));

    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("./ethn.otf");
    image->loadFromFile("./Images/menu.png");

    bg->setTexture(*image);

    posMouse = {0,0};
    mouseCoord = {0, 0};

    options = {"AlienForce", "New game", "Continue", "About", "Quit"};
    texts.resize(5);
    coords = {{556,36},{585,191},{583,280},{600,370},{623,457}};
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

void Menu::loopEvents(){
    sf::Event event;
    while(window->pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window->close();
        }

        posMouse = sf::Mouse::getPosition(*window);
        mouseCoord = window->mapPixelToCoords(posMouse);

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
                    selectedNewGame = true;
                    window->close();
                    break;
                case 2:
                    selectedContinue = true;
                    window->close();
                    break;
                case 3:
                    std::cout << "About selected!\n";
                    break;
                case 4:
                    window->close();
                    break;
                default:
                    break;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(winclose->getGlobalBounds().contains(mouseCoord)){
                window->close();
            }
        }
    }
}

void Menu::drawAll(){
    window->clear();
    window->draw(*bg);
    for(auto t : texts){
        window->draw(t);
    }
    window->display();
}

void Menu::runMenu(){
    selectedNewGame = false;
    while(window->isOpen()){
        loopEvents();
        drawAll();
    }
    SpaceMap space(readBase());
    Character alien;
    Character hero;
    space.initializeBombs(alien,hero);

    if (selectedNewGame)
        space.nameBombs(alien,hero);
    if (selectedContinue)
        LoadSave(hero, alien);

    space.setLayoutBombs(alien,hero);
    space.runSpaceMap(alien, hero);
    space.desinitializeBombs(alien,hero);
}
