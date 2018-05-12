#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include "Map.hpp"
#include "ResourceHolder.hpp"
#include "Input.hpp"
#include "Grid.hpp"

constexpr int TILESIZE{16};
constexpr int MAPWIDTH{15};
constexpr int MAPHEIGHT{15};

int main()
{
    ResourceHolder<sf::Texture, Texture::ID> textures;
    ResourceHolder<sf::Font, Fonts::ID> fonts;
    try{
        textures.load(Texture::Pokemon, "Zelda.png");
        fonts.load(Fonts::Sansation, "sansation.ttf");
    }catch(std::runtime_error& e){
        std::cout<<"Fail"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    
    
    bool box{false};
    bool layer{false};
    Input input;
    
    

    //Selector Box for map
    sf::RectangleShape selectorMap;
    int mapPosX{0};
    int mapPosY{0};
    int width{1};
    int height{1};
    selectorMap.setSize(sf::Vector2f(TILESIZE,TILESIZE));
    selectorMap.setOrigin(0, 0);
    selectorMap.setFillColor(sf::Color(193, 66, 66, 150)); // red
    selectorMap.setOutlineColor(sf::Color::Black);
    selectorMap.setOutlineThickness(.2);
    
    //Selector Box for Textures
    sf::RectangleShape selectorTexture;
    selectorTexture.setSize(sf::Vector2f(TILESIZE,TILESIZE));
    selectorTexture.setOrigin(0, 0);
    selectorTexture.setFillColor(sf::Color(193, 66, 66, 150)); // red
    selectorTexture.setOutlineColor(sf::Color::Black);
    selectorTexture.setOutlineThickness(.2);
    
    //Text to show what tile we are currently on
    sf::Text mapPosition;
    mapPosition.setFont(fonts.get(Fonts::Sansation));
    mapPosition.setCharacterSize(30);
    mapPosition.setScale(.1, .1);
    mapPosition.setPosition(selectorTexture.getPosition().x + 7, selectorTexture.getPosition().y + 7);
    mapPosition.setString(std::to_string(mapPosX) + "," + std::to_string(mapPosY));
    
    //Text to show the position of the texture selector
    sf::Text texturePosition;
    texturePosition.setFont(fonts.get(Fonts::Sansation));
    texturePosition.setCharacterSize(30);
    texturePosition.setScale(.1, .1);
    texturePosition.setPosition(selectorTexture.getPosition().x + 7, selectorTexture.getPosition().y + 7);
    texturePosition.setString(std::to_string(selectorTexture.getPosition().x) + "," + std::to_string(selectorTexture.getPosition().y));
    
    //Text to show the current layer
    sf::Text lyer;
    lyer.setFont(fonts.get(Fonts::Sansation));
    lyer.setCharacterSize(50);
    lyer.setScale(.25,.25);
    lyer.setString("1");
    lyer.setPosition(200, 200);
    
    //Setting up map data
    Map map;
    map.setSize(sf::Vector2u(MAPWIDTH,MAPHEIGHT),TILESIZE);
    map.loadTextures("TextureNums1.txt", textures.get(Texture::Pokemon), 1);
    //map.loadTextures("TextureNums1-2.txt", textures.get(Texture::Pokemon), 2);
    map.loadWalkable("Walkable1.txt");
    
    //Creating Window and two separate views
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");
    window.setFramerateLimit(60);
    //View1
    sf::View view1(sf::FloatRect(0, 0, 240, 240));
    view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
    //View2
    sf::View view2(sf::FloatRect(0, 0, 240, 240));
    view2.setViewport(sf::FloatRect(.5f, 0, 0.5f, 1));
    
    //Texture palette
    sf::Sprite palette;
    palette.setTexture(textures.get(Texture::Pokemon));
    int desired{0};
    
    //Create Texture Grid
    Grid grid(textures.get(Texture::Pokemon).getSize(), TILESIZE, sf::Color::White);
              
    
    //Main program loop to check for input
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window.close();
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
                if(box == false){
                    if((mapPosY + height)*TILESIZE < map.height()){
                        selectorMap.move(0,TILESIZE);
                        mapPosY++;
                    }
                }
                if(box == true){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
                        if(selectorTexture.getPosition().y+1 < palette.getGlobalBounds().top+palette.getGlobalBounds().height){
                            selectorTexture.move(0,1);
                        }
                    }else{
                        if(selectorTexture.getPosition().y+TILESIZE < palette.getGlobalBounds().top+palette.getGlobalBounds().height){
                            int y = static_cast<int>(selectorTexture.getPosition().y)%TILESIZE;
                            selectorTexture.move(0,TILESIZE-y);
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                if(box == false){
                    if((mapPosX + width)*TILESIZE < map.width()){
                        selectorMap.move(TILESIZE,0);
                        mapPosX++;
                    }
                }
                if(box == true){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
                        if(selectorTexture.getPosition().x+TILESIZE <palette.getGlobalBounds().left+palette.getGlobalBounds().width){
                            selectorTexture.move(1,0);
                        }
                    }else{
                        if(selectorTexture.getPosition().x+TILESIZE < palette.getGlobalBounds().left+palette.getGlobalBounds().width){
                            int x = static_cast<int>(selectorTexture.getPosition().x)%TILESIZE;
                            selectorTexture.move(TILESIZE-x,0);
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
                if(box == false){
                    if(mapPosX > 0){
                        selectorMap.move(-TILESIZE,0);
                        mapPosX--;
                    }
                }
                if(box == true){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
                        if(selectorTexture.getPosition().x-TILESIZE >= palette.getGlobalBounds().left){
                            selectorTexture.move(-1,0);
                        }
                    }else{
                        if(selectorTexture.getPosition().x-TILESIZE >= palette.getGlobalBounds().left){
                            if(static_cast<int>(selectorTexture.getPosition().x)%TILESIZE == 0){
                                selectorTexture.move(-TILESIZE,0);
                            }else{
                                int x =static_cast<int>(selectorTexture.getPosition().x)%TILESIZE;
                                selectorTexture.move(-x,0);
                            }
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
                if(box == false){
                    if(mapPosY > 0){
                        selectorMap.move(0,-TILESIZE);
                        mapPosY--;
                    }
                }
                if(box == true){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
                        if(selectorTexture.getPosition().y-TILESIZE >= palette.getGlobalBounds().top){
                                selectorTexture.move(0,-1);
                        }
                    }else{
                        if(selectorTexture.getPosition().y-TILESIZE >= palette.getGlobalBounds().top){
                            if(static_cast<int>(selectorTexture.getPosition().y)%TILESIZE == 0){
                                selectorTexture.move(0,-TILESIZE);
                            }else{
                                int y =static_cast<int>(selectorTexture.getPosition().y)%TILESIZE;
                                selectorTexture.move(0,-y);
                            }
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                if(layer == false){
                    for(int i = 0; i < width; i++){
                        for(int j = 0; j < height; j++){
                            sf::IntRect temp;
                            int left = static_cast<int>(selectorTexture.getPosition().x);
                            int top = static_cast<int>(selectorTexture.getPosition().y);
                            temp = sf::IntRect(left,top,TILESIZE,TILESIZE);
                            
                            int tileNum = ((top/TILESIZE)*textures.get(Texture::Pokemon).getSize().x)/TILESIZE + left/TILESIZE;
                            
                            
                            map.setTexture(sf::Vector2u(mapPosX+i,mapPosY+j), tileNum, 1);
        
                        std::cout<<static_cast<int>(selectorTexture.getPosition().y)*(textures.get(Texture::Pokemon).getSize().x/TILESIZE) + static_cast<int>(selectorTexture.getPosition().x)<<std::endl;
                        }
                    }
                   
                } /*
                     
                     else if(layer == true){
                    for(int i = 0; i < width; i++){
                        for(int j = 0; j < height; j++){
                            map.setTexture(sf::Vector2u(mapPosX+i,mapPosY+j), texturePosY*(textures.get(Texture::Pokemon).getSize().x/TILESIZE) + texturePosX,2);
                        }
                    }
                }
                   */
            }
                   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
                map.exportTextures("NewTexture.txt");
                map.exportWalkable("NewWalkable.txt");
            }
            if(input.getKey(0)){
                for(int i = 0; i < width; i++){
                    for(int j = 0; j < height; j++){
                         map.setWalkable(sf::Vector2u(mapPosX+i,mapPosY+j), false);
                    }
                }
            }

            if(input.getKey(5)){
                for(int i = 0; i < width; i++){
                    for(int j = 0; j < height; j++){
                        map.setWalkable(sf::Vector2u(mapPosX+i,mapPosY+j), true);
                    }
                }
            }
            if(input.getKeyUp(2)){
                box = !box;
            }
            if(input.getKeyUp(3)){
                if((mapPosY+height)*TILESIZE < map.height()){
                    selectorMap.setSize(sf::Vector2f(selectorMap.getSize().x,TILESIZE+selectorMap.getSize().y));
                    height++;
                }else{
                    if(mapPosY > 0){
                        mapPosY--;
                        selectorMap.move(0,-TILESIZE);
                        selectorMap.setSize(sf::Vector2f(selectorMap.getSize().x,TILESIZE+selectorMap.getSize().y));
                        height++;
                    }
                }
            }
            if(input.getKeyUp(4)){
                if((mapPosX+width)*TILESIZE < map.width()){
                    selectorMap.setSize(sf::Vector2f(TILESIZE+selectorMap.getSize().x,selectorMap.getSize().y));
                    width++;
                }else{
                    if(mapPosX > 0){
                        mapPosX--;
                        selectorMap.move(-TILESIZE,0);
                        selectorMap.setSize(sf::Vector2f(TILESIZE+selectorMap.getSize().x,selectorMap.getSize().y));
                        width++;
                    }
                }
            }
            if(input.getKeyUp(6)){
                layer = !layer;
                if(layer == false){
                    lyer.setString("1");
                }else{
                    lyer.setString("2");
                }
            }
            if(input.getKeyUp(7)){
                view1.zoom(1.25);
            }
            if(input.getKeyUp(8)){
                view1.zoom(.75);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(palette.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                    int x = static_cast<int>(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x);
                    x = x - x%TILESIZE;
                    int y = static_cast<int>(window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
                    y = y - y%TILESIZE;
                    selectorTexture.setPosition(sf::Vector2f(x,y));
                }
            }
        }
        input.update();
        
        if(selectorMap.getPosition().x > view1.getViewport().width){
            view1.setCenter(selectorMap.getPosition());
        }
        view2.setCenter(selectorTexture.getPosition());
        
        
        window.setView(view1);
        
        //Updating Position Information for the two selectors
        mapPosition.setString(std::to_string(mapPosX) + "," + std::to_string(mapPosY));
        mapPosition.setPosition(selectorMap.getPosition().x + 7, selectorMap.getPosition().y + 7);
        
        texturePosition.setString(std::to_string(static_cast<int>(selectorTexture.getPosition().x)) + "," + std::to_string(static_cast<int>(selectorTexture.getPosition().y)));
        texturePosition.setPosition(selectorTexture.getPosition().x + 7, selectorTexture.getPosition().y + 7);
        
        //draw view1
        
        
        window.clear(sf::Color::Black);
        map.draw(&window,1);
        if(layer)
            map.draw(&window, 2);
        window.draw(selectorMap);
        window.draw(mapPosition);
        //draw view2
        window.setView(view2);
        window.draw(palette);
        window.draw(selectorTexture);
        window.draw(lyer);
        window.draw(texturePosition);
        window.draw(grid);
        //display
 
        window.display();
    }
    
    return 0;
}
