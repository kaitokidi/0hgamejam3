#include "TextScreen.hpp"


    TextScreen::TextScreen() {
        open = true;
        f.loadFromFile("res/fonts/font.otf");
        t.setFont(f);
    }
    
    TextScreen::~TextScreen(){}

    std::string TextScreen::display_recieve_text(sf::RenderWindow* window, std::string s, sf::Color c ){
        open = true;
        std::string recieved = "";
        t.setString(recieved);
        t.setPosition(window->getSize().x/2 - ((s.size()/2)*t.getCharacterSize()), window->getSize().y/2 - t.getCharacterSize()/2);
        window->clear(c);
        float oldSize;
        
        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    return "closed";
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window->close();
                        return "closed";
                    }
                    break;
                case sf::Event::TextEntered:
                    oldSize = t.getGlobalBounds().width;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) { recieved.erase(recieved.end()-1, recieved.end()); }
                    else { recieved += event.text.unicode; }
                    t.setString(recieved);
                    if(t.getGlobalBounds().left >= 0.2)t.move(-(t.getGlobalBounds().width-oldSize)/2, 0);
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        open = false;
                    }
                default:
                    break;
                }
            }

            window->draw(t);
            window->display();
            window->clear();
        }
    }
        
        
    void TextScreen::displayText(sf::RenderWindow* window, std::string s , sf::Color c ){
        open = true;
        t.setString(s);
        t.setPosition(window->getSize().x/2 - t.getGlobalBounds().width/2, window->getSize().y/2 - t.getGlobalBounds().height/2);
//         window->clear(c);
            bool closing = true;
            float time = 0;
            sf::Clock timer; sf::Sprite dark; sf::Texture text;
            text.loadFromFile("res/pics/black.png");
            dark.setTexture(text);
            dark.setOrigin(dark.getLocalBounds().width/2,dark.getLocalBounds().height/2);
            dark.setPosition(window->getSize().x/2,window->getSize().y/2);
            float scale = window->getSize().x/dark.getGlobalBounds().width;
            while(closing){            
                dark.setScale(scale,scale);
                time += timer.restart().asSeconds();
                if(time > 0.1){ scale *= 0.5;time = 0; }
                window->clear();
                window->draw(t);
                window->draw(dark);
                window->display();
                if(dark.getGlobalBounds().width < 0.1) closing = false;
            }
            //clean events 
            sf::Event e; while (window->pollEvent(e)) { }
            
        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    exit(0);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) { window->close(); exit(0); }
                    if (event.key.code == sf::Keyboard::Return) open = false;
                    if (event.key.code == sf::Keyboard::Space) open = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        open = false;
                    }
                default:
                    break;
                }
            }
            window->clear();
            window->draw(t);
            window->display();
                
        }
    }
    
    void TextScreen::drawText(sf::RenderWindow* window, std::string s , sf::Color c ){
        open = true;
        t.setString(s);
        t.setPosition(window->getSize().x/2 - ((s.size()/2)*t.getCharacterSize()), window->getSize().y/2 - t.getCharacterSize()/2);
        window->clear(c);

        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    exit(0);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) { window->close(); exit(0); }
                    if (event.key.code == sf::Keyboard::Return) open = false;
                    if (event.key.code == sf::Keyboard::Space) open = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        open = false;
                    }
                default:
                    break;
                }
            }
            window->clear();
            window->draw(t);
           
        }
    }
    
    void TextScreen::displayTextPos(sf::RenderWindow* window, std::string s , sf::Color c , float posx, float posy ){
        open = true;
        t.setString(s);
        t.setPosition(posx, posy);
        t.setColor(c);
        
        window->draw(t);
        window->display();
    }
    
    void TextScreen::drawTextPos(sf::RenderWindow* window, std::string s , sf::Color c , float posx, float posy ){
        open = true;
        t.setString(s);
        t.setPosition(posx, posy);
        t.setColor(c);

        window->draw(t);
    }