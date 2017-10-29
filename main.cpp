//GRAVITY
#include <time.h>       /* time */
#include <string>       /*strings*/
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.h"
#include "Portada.hpp"
#include "TextScreen.hpp"
#include "MenuSelection.hpp"

struct Penguin : public sf::Sprite {
  Penguin() {
      vel.x = 0; vel.y = 5;
  }

  void update(float dt) {
      move(vel.x*dt, vel.y*dt);
      vel.y += 110*dt;
  }

  void setVel(sf::Vector2f v){
      vel = v;
  }

  sf::Vector2f vel;

};

int main(int argc, const char* argv[]){
    
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(400,600), "0hgame3!!!!!!", sf::Style::Close);
    sf::Vector2f screenSize = sf::Vector2f(window.getSize().x,window.getSize().y);    
    float deltatime = 0;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(65);
    Portada portada;
    
    //Cover
    portada.notAnimation();
    portada.display(&window, "res/pics/portada.png");
    
    //Rules
    portada.animation();
    portada.display(&window, "res/pics/rules1.png");
    
    //GAME
    
     sf::Clock timer;

     sf::Texture penguinUp;
     penguinUp.loadFromFile("res/pics/penguinUp.png");
     sf::Texture penguinDown;
     penguinDown.loadFromFile("res/pics/penguinDown.png");
     sf::Texture cloudTex;
     cloudTex.loadFromFile("res/pics/cloud.png");

     sf::Text penguinsAlive;
     sf::Font font;
     font.loadFromFile("res/fonts/font.otf");
     penguinsAlive.setFont(font);
     penguinsAlive.setCharacterSize(screenSize.x/20);
     penguinsAlive.setPosition(0,0);
     penguinsAlive.setColor(sf::Color::White);

     std::vector<Penguin> penguins;
     std::vector<sf::Sprite> clouds;

     float timePassed = 0;

     float timeToSpawnCloud = 0;
     float timeToSpawnPenguin = 0;

    while(window.isOpen()){
        
        deltatime = timer.restart().asSeconds();
        timePassed += deltatime;
        timeToSpawnCloud += deltatime;
        timeToSpawnPenguin += deltatime;

        if(int(timeToSpawnPenguin) % 6 == 0){
            ++timeToSpawnPenguin;
            Penguin newPenguin;
            newPenguin.setTexture(penguinDown);
            newPenguin.setOrigin(newPenguin.getLocalBounds().width/2.0f, newPenguin.getLocalBounds().height/2.0f);
            newPenguin.setPosition(sf::Vector2f(std::rand()%int(screenSize.x), 0));
            float scaleFactor = screenSize.x/8.0f / newPenguin.getGlobalBounds().width;
            newPenguin.setScale(scaleFactor, scaleFactor);
            penguins.push_back(newPenguin);
        }

        if(int(timeToSpawnCloud) % 6 == 0){
            ++timeToSpawnCloud;
            sf::Sprite newCloud;
            newCloud.setTexture(cloudTex);
            newCloud.setOrigin(newCloud.getLocalBounds().width/2.0f, newCloud.getLocalBounds().height/2.0f);
            newCloud.setPosition(sf::Vector2f(0, std::rand()%int(screenSize.y)));
            float scaleFactor = (screenSize.x/8.0f) / newCloud.getGlobalBounds().width;
            scaleFactor += (std::rand()%10 / 10.0f);
            newCloud.setScale(scaleFactor, scaleFactor);
            clouds.push_back(newCloud);
        }

        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close(); 
            if (event.type == sf::Event::Resized) {window.setSize(sf::Vector2u(event.size.width, event.size.height));}
            if (sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (Penguin& penguin : penguins){
                        if(penguin.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
                            penguin.setVel(sf::Vector2f(rand()%100-50.0f, -200.0f));
                            penguin.setTexture(penguinUp);
                        }
                    }
                }
            }
        }

        for(int i = 0; i < penguins.size(); ++i){
            float penguinsize = penguins[i].getGlobalBounds().width/2;
            if(penguins[i].getPosition().x - penguinsize < 0 && penguins[i].vel.x < 0) penguins[i].vel.x *= -1;
            if(penguins[i].getPosition().x + penguinsize > screenSize.x && penguins[i].vel.x > 0) penguins[i].vel.x *= -1;
            if(penguins[i].getPosition().y > screenSize.y + penguinsize){
                penguins.erase(penguins.begin()+i);
                --i;
            }
        }

        for(sf::Sprite& cloud:clouds){
            cloud.move(100*deltatime, 0);
        }

        for(Penguin& peng : penguins){
            peng.update(deltatime);
            if(peng.vel.y > 0) peng.setTexture(penguinDown);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        
             penguinsAlive.setString("penguinsAlive:"+std::to_string(penguins.size()));

        window.clear(sf::Color::Blue);
        for(auto penguin: penguins){
            window.draw(penguin);
        }
        for(auto cloud: clouds){
            window.draw(cloud);
        }
        window.draw(penguinsAlive);
        window.display();
    }
}
