#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Swordfish.h"
#include "TextureManager.h"
#include "XMLParser.h"
#include <iostream>
#include <vector>
#include "Constants.h"
int main(int argc, char** argv)
{
    
    // Resource Managers
    TextureManager textures;
    
    // create main window
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32), "Hello World - SFML",sf::Style::Titlebar|sf::Style::Close);
    

    XMLParser parser;
    parser.loadXML("../data/xml/TestXML.xml");
    std::vector<int> swordfishPositions = parser.getSwordfishPositions();
    
    std::vector<std::shared_ptr<Swordfish>> fish(5);
    std::vector<sf::Vector2f> positions(5);
    std::vector<sf::Vector2f> directions(5);
    
    
    /*Note: to save the memory fot passing texture and texture location, I used shared pointer. However, shared pointer can only be created dynamically, so you need to use make_shared<T>, or you will have segementation fault*/
    textures.addTexture("../data/fish.png");
    textures.addArea("Swordfish",sf::IntRect(512,512,512,256));
    textures.addArea("bubble",sf::IntRect(960,256,64,64));
    
    for(int i=0;i<5;i++)
    {
        fish[i]=std::make_shared<Swordfish>(sf::Vector2f(i*200+1,1),sf::Vector2f(1.0f,1.0f));
        fish[i]->setTexture(textures.get().texture);
        fish[i]->setTextureAreas(textures.get().areas);
        fish[i]->init();
    }
    
    // start main loop
    sf::Clock clock;
    while(App.isOpen())
    {
        // process events
        sf::Event event;
        while (App.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    App.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::A) {
                        positions[0] = sf::Vector2f(1,1);
                        positions[1] = sf::Vector2f(200,1);
                        positions[2] = sf::Vector2f(400,1);
                        positions[3] = sf::Vector2f(600,1);
                        positions[4] = sf::Vector2f(800,1);
                        
                        directions[0] = sf::Vector2f(1.0f,1.0f);
                        directions[1] = sf::Vector2f(1.0f,1.0f);
                        directions[2] = sf::Vector2f(1.0f,1.0f);
                        directions[3] = sf::Vector2f(1.0f,1.0f);
                        directions[4] = sf::Vector2f(1.0f,1.0f);
                        for(int i=0;i<5;i++)
                        {
                            fish[i]=std::make_shared<Swordfish>(positions[i],directions[i]);
                            fish[i]->setTexture(textures.get().texture);
                            fish[i]->setTextureAreas(textures.get().areas);
                            fish[i]->init();
                        }
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        positions[0] = sf::Vector2f(200,1);
                        positions[1] = sf::Vector2f(1,400);
                        positions[2] = sf::Vector2f(500,1);
                        positions[3] = sf::Vector2f(1,700);
                        positions[4] = sf::Vector2f(800,1);
                        
                        directions[0] = sf::Vector2f(1.0f,1.0f);
                        directions[1] = sf::Vector2f(1.0f,0.5f);
                        directions[2] = sf::Vector2f(0.5f,1.0f);
                        directions[3] = sf::Vector2f(1.0f,-0.25f);
                        directions[4] = sf::Vector2f(-1.0f,1.0f);
                        for(int i=0;i<5;i++)
                        {
                            fish[i]=std::make_shared<Swordfish>(positions[i],directions[i]);
                            fish[i]->setTexture(textures.get().texture);
                            fish[i]->setTextureAreas(textures.get().areas);
                            fish[i]->init();
                        }
                    }
                    if (event.key.code == sf::Keyboard::D) {
                        positions[0] = sf::Vector2f(1,WINDOW_HEIGHT);
                        positions[1] = sf::Vector2f(200,WINDOW_HEIGHT);
                        positions[2] = sf::Vector2f(400,WINDOW_HEIGHT);
                        positions[3] = sf::Vector2f(600,WINDOW_HEIGHT);
                        positions[4] = sf::Vector2f(800,WINDOW_HEIGHT);
                        
                        directions[0] = sf::Vector2f(1.0f,-1.0f);
                        directions[1] = sf::Vector2f(1.0f,-1.0f);
                        directions[2] = sf::Vector2f(1.0f,-1.0f);
                        directions[3] = sf::Vector2f(1.0f,-1.0f);
                        directions[4] = sf::Vector2f(1.0f,-1.0f);
                        for(int i=0;i<5;i++)
                        {
                            fish[i]=std::make_shared<Swordfish>(positions[i],directions[i]);
                            fish[i]->setTexture(textures.get().texture);
                            fish[i]->setTextureAreas(textures.get().areas);
                            fish[i]->init();
                        }
                    }
                    if (event.key.code == sf::Keyboard::F) {
                        positions[0] = sf::Vector2f(1,21);
                        positions[1] = sf::Vector2f(WINDOW_WIDTH-20,1);
                        positions[2] = sf::Vector2f(21,WINDOW_HEIGHT);
                        positions[3] = sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT-20);
                        positions[4] = sf::Vector2f(WINDOW_WIDTH/2,1);
                        
                        directions[0] = sf::Vector2f(1.0f,1.0f);
                        directions[1] = sf::Vector2f(-1.0f,1.0f);
                        directions[2] = sf::Vector2f(1.0f,-1.0f);
                        directions[3] = sf::Vector2f(-1.0f,-1.0f);
                        directions[4] = sf::Vector2f(0.0f,1.0f);
                        for(int i=0;i<5;i++)
                        {
                            fish[i]=std::make_shared<Swordfish>(positions[i],directions[i]);
                            fish[i]->setTexture(textures.get().texture);
                            fish[i]->setTextureAreas(textures.get().areas);
                            fish[i]->init();
                        }
                    }
                    if (event.key.code == sf::Keyboard::G) {
                        positions[0] = sf::Vector2f(WINDOW_WIDTH/3,1);
                        positions[1] = sf::Vector2f(WINDOW_WIDTH*2/3,1);
                        positions[2] = sf::Vector2f(1,WINDOW_HEIGHT/4);
                        positions[3] = sf::Vector2f(1,WINDOW_HEIGHT*2/4);
                        positions[4] = sf::Vector2f(1,WINDOW_HEIGHT*3/4);
                        
                        directions[0] = sf::Vector2f(0.0f,1.0f);
                        directions[1] = sf::Vector2f(0.0f,1.0f);
                        directions[2] = sf::Vector2f(1.0f,0.0f);
                        directions[3] = sf::Vector2f(1.0f,0.0f);
                        directions[4] = sf::Vector2f(1.0f,0.0f);
                        for(int i=0;i<5;i++)
                        {
                            fish[i]=std::make_shared<Swordfish>(positions[i],directions[i]);
                            fish[i]->setTexture(textures.get().texture);
                            fish[i]->setTextureAreas(textures.get().areas);
                            fish[i]->init();
                        }
                    }
                default:
                    break;
            }
        }
        // clear screen and fill with blue
        App.clear(sf::Color::Blue);
        
        sf::Vector2i mousePos=sf::Mouse::getPosition(App);
        float deltaTime=clock.restart().asSeconds();
        for(int i=0;i<5;i++)
        {
            fish[i]->update(deltaTime);
            App.draw(*fish[i]);
        }
        App.display();
    }
    
    // Done.
    return 0;
}
