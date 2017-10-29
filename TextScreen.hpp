#ifndef TEXTSCREEN
#define TEXTSCREEN

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TextScreen {

private:
    sf::Text t; 
    sf::Font f;
    sf::Color c;
//    sf::Button b;
    bool open;
    
public:
    TextScreen();
    ~TextScreen();

    void        drawText            (sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black));
    void        drawTextPos         (sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black), float posx = 0, float posy = 0);
    void        displayText         (sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black));
    void        displayTextPos      (sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black), float posx = 0, float posy = 0);
    std::string display_recieve_text(sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black));
    
};

#endif // TEXTSCREEN