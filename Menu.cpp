#include "Menu.h"
#include "GameState.h"


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

    options = {"AlienForce", "New game", "Continue", "About", "Quit"};
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
                    selectedContinue = true;
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
    Character alien;
    alien.hp = 700;
    alien.speed = 25;
    Character hero;
    hero.hp = 250;
    hero.speed = 12;
    if (selectedPlay){
        hero.name = "hero";
        alien.name = "alien";
    }
    if (selectedContinue){
        LoadSave(hero, alien);
    }

    SpaceMap space(read_base());
    space.runSpaceMap(alien, hero);
}

int Menu::read_base(){
    std::ifstream is;
    int vertex;
    is.open("graph_input.txt");
    is>>vertex;
    is.close();
    return vertex;

}