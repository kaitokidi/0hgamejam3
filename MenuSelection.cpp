#include "MenuSelection.hpp"


    MenuSelection::MenuSelection() {
        open = true;
    }
    
    MenuSelection::~MenuSelection(){}
    
    void MenuSelection::notAnimation(){
        wantAnimation = false;
    }
    void MenuSelection::animation(){
        wantAnimation = true;
    }
    
    int MenuSelection::select(sf::RenderWindow* window, std::vector<std::string> &buttonNames){
        int qttyButtons = buttonNames.size();
        sf::Vector2f buttonSize(window->getSize().x/(qttyButtons+2), window->getSize().y/6);
        sf::Font font;
        sf::Texture text;
        if(!font.loadFromFile("res/fonts/font.otf")){ std::cerr << "Can't find the font file" << std::endl; }
        
        
        open = true;
        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) window->close();
                    break;
                default:
                    break;
                }

            }

            window->display();       
        }
    }
    
    void MenuSelection::display(sf::RenderWindow* window, std::string pathImage){
        open = true;
            t.loadFromFile(pathImage);
            s = sf::Sprite();
            s.setTexture(t);
            s.scale(window->getSize().y/s.getGlobalBounds().height,window->getSize().y/s.getGlobalBounds().height);
            s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, 0);
        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) window->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        open = false;
                    }
                    break;
                default:
                    break;
                }
                //ANDROID
                     if(event.type == sf::Event::TouchEnded)  open = false;
                     break;
            }

            window->clear();
            window->draw(s);

            window->display();
                
        }
        
        sf::Clock timer;
        sf::Sprite dark;
        sf::Texture text;
        bool closing = true;
        text.loadFromFile("res/pics/black.png");
        
        dark.setTexture(text);
        dark.setOrigin(dark.getLocalBounds().width/2,dark.getLocalBounds().height/2);
        dark.setPosition(window->getSize().x/2,window->getSize().y/2);
        float scale = 1/dark.getGlobalBounds().width;;
        
        float time = 0;
        while(closing and wantAnimation){            
            dark.setScale(scale,scale);
            time += timer.restart().asSeconds();
            if(time > 0.1){
                scale *= 1.5;
                time = 0;
            }
            window->clear();
            window->draw(s);
            window->draw(dark);
            window->display();
            if(dark.getGlobalBounds().width > window->getSize().x) closing = false;
        }
        //clean events 
        sf::Event e; while (window->pollEvent(e)) { }
    }
