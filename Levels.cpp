#include "Levels.h"
#include "bossFight.h"
#include "GameState.h"

void Levels::setValues(){
    window.create(sf::VideoMode(800, 600), "My window");

    float playerScaleX = 2.f;
    float playerScaleY = 2.f;
    playerTexture.loadFromFile("./Images/chiefsheet.png");
    enemyTexture.loadFromFile("./Images/enemy1.png");
    player.setTexture(playerTexture);
    player.setScale(playerScaleX,playerScaleY);
    enemy.setTexture(enemyTexture);
    
    sf::Vector2f centerM(enemyTexture.getSize().x,enemyTexture.getSize().y);
    centerM.x = centerM.x / 2;
    centerM.y = centerM.y / 2;
    enemy.setOrigin(centerM);
}

void Levels::run(sf::Sprite backgroundLevel,Character& hero,std::string equipment){
    setValues();
    while (window.isOpen())
    {
        processEvents();
        updateEnemy();
        update(hero,equipment);
        render(backgroundLevel,hero,equipment);
    }
}

void Levels::processEvents(){
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

}

void Levels::update(Character& hero, std::string equipment){
    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x /= 4;
    textureSize.y /= 4;

    sf::Vector2f velocity(0.f, 0.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        velocity.x = -0.05f;
        currentRightFrames += velocityAnimation;
        lineAnimation = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        velocity.x = 0.05f;
        currentLeftFrames += velocityAnimation;
        lineAnimation = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

        velocity.y = -0.05f;
        currentUpFrames += velocityAnimation;
        lineAnimation = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        velocity.y = 0.05f;
        currentDownFrames += velocityAnimation;
        lineAnimation = 0;
    }

    bool isMoving = (velocity.x != 0.f || velocity.y != 0.f);
    if (isMoving) {

        if (velocity.x > 0.f) {

            if (currentLeftFrames > 4) {
                currentLeftFrames = 0.f;
            }
            player.setTextureRect(sf::IntRect(static_cast<int>(currentLeftFrames) * textureSize.x, 
            lineAnimation * textureSize.y, textureSize.x, textureSize.y));
        } else if (velocity.x < 0.f) {

            if (currentRightFrames > 4) {
                currentRightFrames = 0.f;
            }
            player.setTextureRect(sf::IntRect(static_cast<int>(currentRightFrames) * textureSize.x, 
            lineAnimation * textureSize.y, textureSize.x, textureSize.y));
        }

        if (velocity.y < 0.f) {

            if (currentUpFrames > 4) {
                currentUpFrames = 0.f;
        }
        player.setTextureRect(sf::IntRect(static_cast<int>(currentUpFrames) * textureSize.x, 
            lineAnimation * textureSize.y, textureSize.x, textureSize.y));
        } 
        else if (velocity.y > 0.f) {

            if (currentDownFrames > 4) {
                currentDownFrames = 0.f;
            }
            player.setTextureRect(sf::IntRect(static_cast<int>(currentDownFrames) * textureSize.x, 
            lineAnimation * textureSize.y, textureSize.x, textureSize.y));
        }
    } else {

        player.setTextureRect(sf::IntRect(0, lineAnimation*textureSize.y, textureSize.x, textureSize.y));
    }

    sf::IntRect texturerect = player.getTextureRect();
    float velocityMoviment = 100.f;
    player.setOrigin(texturerect.width/2.f,texturerect.height/2.f);
    player.move(velocity * velocityMoviment * 0.016f); 
    
    for (size_t i = 0; i < 4; i++){
        if(!hero.grenades[i].full){
                if(hero.grenades[i].type == equipment &&
                std::abs(player.getPosition().x-hero.grenades[i].bombSprite.getPosition().x)<10 && 
                std::abs(player.getPosition().y-hero.grenades[i].bombSprite.getPosition().y)<10)
                hero.grenades[i].full=true;
        }
    }

    if(std::abs(player.getPosition().x-enemy.getPosition().x)<30 &&
        std::abs(player.getPosition().y-enemy.getPosition().y)<60){
        player.setPosition(400,50);
        takeOutBomb(hero,equipment);
    }
}
void Levels::updateEnemy(){
    sf::Vector2u textureSize = enemyTexture.getSize();
    textureSize.x /= 4;
    textureSize.y /= 4;

    float enemyScaleX =2.f;
    float enemyScaleY =2.f;

    enemy.setScale(enemyScaleX, enemyScaleY);
    sf::Vector2f velocity =velocityEnemy;

    if (velocity.x > 0.f) {
        currentLeftFramesEnemy += velocityAnimation;
        if (currentLeftFramesEnemy > 4) {
            currentLeftFramesEnemy = 0.f;
        }
        enemy.setTextureRect(sf::IntRect(static_cast<int>(currentLeftFramesEnemy) * textureSize.x, 2 * textureSize.y, textureSize.x, textureSize.y));
    } else if (velocity.x < 0.f) {
        currentRightFramesEnemy += velocityAnimation;
        if (currentRightFramesEnemy > 4) {
            currentRightFramesEnemy = 0.f;
        }
        enemy.setTextureRect(sf::IntRect(static_cast<int>(currentRightFramesEnemy) * textureSize.x, 1 * textureSize.y, textureSize.x, textureSize.y));
    }
    float velocityMoviment = 100.f;
    sf::IntRect texturerect=enemy.getTextureRect();
    enemy.setOrigin(texturerect.width/2.f,texturerect.height/2.f);
    enemy.move(velocityEnemy * velocityMoviment * 0.016f);
    sf::Vector2f positionEnemy = enemy.getPosition();

    if (positionEnemy.x <=0) {
        positionEnemy.x = 0;
        enemy.setPosition(positionEnemy.x,200.f);
        velocityEnemy.x=0.1f;
    } else if (positionEnemy.x >= 800) {
        positionEnemy.x = 800;
        enemy.setPosition(positionEnemy.x,200.f);
        velocityEnemy.x = -0.1f;
    }
    positionEnemy = enemy.getPosition();
    enemy.setPosition(positionEnemy.x,400.f);
}
void Levels::render(sf::Sprite backgroundLevel,Character& hero,std::string equipment){
    window.clear();
    window.draw(backgroundLevel);

    for (size_t i = 0; i < 4; i++){
        if (!hero.grenades[i].full && hero.grenades[i].type==equipment){
            window.draw(hero.grenades[i].bombSprite);
        }
    }

    window.draw(player);
    window.draw(enemy);
    window.display();
}
void Levels::takeOutBomb(Character &hero, std::string equipment){
    for (size_t i = 0; i<4; i++){
        if(hero.grenades[i].type == equipment && hero.grenades[i].full)
        hero.grenades[i].full = false;
    }
}
