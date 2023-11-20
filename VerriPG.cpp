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
    coords = {{590,40},{610,191},{590,282},{600,370},{623,457}};
    sizes = {20,28,24,24,24};

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
        Game game;
        game.run();
    }
}



Game::Game()
        : window(sf::VideoMode(800, 600), "My window"),
          characterScaleX(1.f),
          characterScaleY(1.f)
{
    characterTexture.loadFromFile("./Images/alienspreadsheet.png");
    backgroundTexture.loadFromFile("./Images/fundo.png");
    //enemieTexture.loadFromFile("./Images/transforme.png");

    character.setTexture(characterTexture);
    background.setTexture(backgroundTexture);
    enemie.setTexture(enemieTexture);

    // Ajusta a escala inicial junto com o centro da figura
    /*
    sf::Vector2f centerM(static_cast<float>(characterTexture.getSize().x), static_cast<float>(characterTexture.getSize().y));
    centerM.x = centerM.x / 2;
    centerM.y = centerM.y / 2;
    character.setOrigin(centerM); */
}

Game::~Game()
{
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }

    bossFight Fight;
    Fight.modeBattle();
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
        velocity.x = -0.02f;
        frameAtualDireita += velocidadeAnimacao;
        linha =1;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // right key is pressed: move our character
        velocity.x = 0.02f;
        frameAtualEsquerda += velocidadeAnimacao;
        linha=2;
        // Ajusta a escala para inverter horizontalmente
        //characterScaleX = -std::abs(characterScaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // up key is pressed: move our character
        velocity.y = -0.02f;
        frameAtualCima += velocidadeAnimacao;
        linha =3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        velocity.y = 0.02f;
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
void Game::render()
{
    window.clear();
    window.draw(background);
    window.draw(character);
    //window.draw(enemie);
    window.display();
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
        alien.hp -= 8 + dice(8);
    if (maxPriorityQueue.top() == alien.speed){
        if (alien.lessAccuracy)
            hero.hp -= prob(90) ? 10 + 2 * dice(8) : 0;
        else hero.hp -= 10 + 2 * dice(8);
    }
    maxPriorityQueue.pop();
}

void bossFight::attack2(){
    damageCondition();
    if (maxPriorityQueue.top() == alien.speed)
        hero.hp -= 20 + 2 * dice(12);
    if (maxPriorityQueue.top() == hero.speed){
        switch (2) {
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
                alien.posion = true;
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
    hero.hp += 10 + 2 * dice(6);
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
    if (alien.posion)
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        // Verifica se o jogador ainda não selecionou a opção atual
        if (!theselect_opBattle) {
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
        }
    } else {
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
    if (prob(80))
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
    alien.bossTexture.loadFromFile("./Images/boss.png");
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
    sf::Vector2f positionHero(static_cast<float>(hero.heroTexture.getSize().x), static_cast<float>(hero.heroTexture.getSize().y));
    sf::Vector2f positionBoss(static_cast<float>(alien.bossTexture.getSize().x), static_cast<float>(alien.bossTexture.getSize().y));
    positionHero.x = positionHero.x / 2;
    positionHero.y = positionHero.y / 2;
    positionBoss.x = positionBoss.x / 2;
    positionHero.y = positionBoss.y / 2;
    hero.heroSprite.setOrigin(positionHero);
    alien.bossSprite.setOrigin(positionBoss);
    hero.heroSprite.setPosition(150.f,380.f);
    alien.bossSprite.setPosition(675.f,250.f);
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
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();
    backgroundTexture.loadFromFile("./Images/fundo.png");
    background.setTexture(backgroundTexture);
    window.create(sf::VideoMode(800,600),"My window");
   
    pressed_opBattle = theselect_opBattle = false;
    font->loadFromFile("./ethn.otf");
    //image->loadFromFile("");

    //bg->setTexture(*image);
    optionsBattle = {"Atirar", "Especial", "Curar", "Fugir"};
    texts_opBattle.resize(4);
    coords_opBattle = {{40,500},{200,500},{350,500},{550,500}};
    sizes_opBattle = {20,20,20,20,20};

    for (std::size_t i{}; i < texts_opBattle.size(); ++i){
        texts_opBattle[i].setFont(*font);
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