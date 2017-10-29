#ifndef MENUSELECTION_H
#define MENUSELECTION_H

#include "button.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MenuSelection {

private:
    sf::Sprite s;
    sf::Texture t;
    bool open;
    bool wantAnimation;
    
public:
    MenuSelection();
    ~MenuSelection();
    int select(sf::RenderWindow* window, std::vector<std::string> &buttonNames);
    void display(sf::RenderWindow* window);
    void display(sf::RenderWindow* window, std::string pathImage);
    void notAnimation();
    void animation();
    
};

#endif // MENUSELECTION_H