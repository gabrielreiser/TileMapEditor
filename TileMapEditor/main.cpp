#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include "Map.hpp"
#include "ResourceHolder.hpp"
#include "Input.hpp"

int main()
{
    bool box{false};
    bool layer{false};
    Input input;
    
    //Map Box
    sf::RectangleShape mapRect;
    int posX{0};
    int posY{0};
    int width{1};
    int height{1};
    mapRect.setSize(sf::Vector2f(14,14));
    mapRect.setOrigin(-1, -1);
    mapRect.setFillColor(sf::Color(193, 66, 66, 150)); // red
    mapRect.setOutlineColor(sf::Color::Black);
    mapRect.setOutlineThickness(1);
    
    //Texture Box
    sf::RectangleShape rect;
    int rPosX{0};
    int rPosY{0};
    rect.setSize(sf::Vector2f(14,14));
    rect.setOrigin(-1, -1);
    rect.setFillColor(sf::Color(193, 66, 66, 150)); // red
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(1);
    
    sf::Font font;
    if(!font.loadFromFile("sansation.ttf"))
        exit(EXIT_FAILURE);
    sf::Text pos;
    pos.setFont(font);
    pos.setCharacterSize(30);
    pos.setScale(.1, .1);
    pos.setPosition(rect.getPosition().x + 7, rect.getPosition().y + 7);
    pos.setString(std::to_string(posX) + "," + std::to_string(posY));
    
    
    ResourceHolder<sf::Texture, Texture::ID> textures;
    try{
        textures.load(Texture::Pokemon, "Zelda.png");
    }catch(std::runtime_error& e){
        std::cout<<"Fail"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    Map map;
    map.setSize(sf::Vector2u(50,50),16);
    map.loadTextures("TextureNums1.txt", textures.get(Texture::Pokemon), 1);
    //map.loadTextures("TextureNums1-2.txt", textures.get(Texture::Pokemon), 2);
    map.loadWalkable("Walkable1.txt");
    
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");
    window.setFramerateLimit(60);
    
    //View1
    sf::View view1(sf::FloatRect(0, 0, 240, 240));
    view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
    //View2
    sf::View view2(sf::FloatRect(0, 0, 240, 240));
    view2.setViewport(sf::FloatRect(.5f, 0, 0.5f, 1));
    
    sf::RectangleShape viewRect;
    viewRect.setOutlineThickness(4);
    viewRect.setSize(sf::Vector2f(view1.getSize().x-2*viewRect.getOutlineThickness(),view1.getSize().y-2*viewRect.getOutlineThickness()));
    viewRect.setOrigin(view1.getCenter().x-viewRect.getOutlineThickness(),view1.getCenter().y-viewRect.getOutlineThickness());
    viewRect.setPosition(view1.getCenter());
    viewRect.setFillColor(sf::Color::Transparent);
    viewRect.setOutlineColor(sf::Color::Yellow);
    viewRect.setOutlineThickness(4);
    

    //Texture palette
    sf::Sprite palette;
    palette.setTexture(textures.get(Texture::Pokemon));
    int desired{0};
    
    sf::RectangleShape textureBox;
    textureBox.setSize(sf::Vector2f(palette.getLocalBounds().width,palette.getLocalBounds().height));
    textureBox.setPosition(palette.getPosition());
    textureBox.setFillColor(sf::Color::Transparent);
    textureBox.setOutlineColor(sf::Color::Yellow);
    textureBox.setOutlineThickness(4);
    
    
    
    sf::Text lyer;
    lyer.setFont(font);
    lyer.setCharacterSize(50);
    lyer.setScale(.25,.25);
    lyer.setString("1");
    lyer.setPosition(200, 200);
    
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
                    if((posY + height)*16 < map.height()){
                        std::cout<<(posY+width)*16<<" "<<map.height()<<std::endl;
                        mapRect.move(0,16);
                        posY++;
                    }
                }
                if(box == true){
                    if(rect.getPosition().y+16 < palette.getGlobalBounds().top+palette.getGlobalBounds().height){
                        rect.move(0,16);
                        rPosY++;
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                if(box == false){
                    if((posX + width)*16 < map.width()){
                        mapRect.move(16,0);
                        posX++;
                    }
                }
                if(rect.getPosition().x+16 < palette.getGlobalBounds().left+palette.getGlobalBounds().width){
                    if(box == true){
                        rect.move(16,0);
                        rPosX++;
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
                if(box == false){
                    if(posX > 0){
                        mapRect.move(-16,0);
                        posX--;
                    }
                }
                if(rect.getPosition().x-16 >= palette.getGlobalBounds().left){
                    if(box == true){
                        rect.move(-16,0);
                        rPosX--;
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
                if(box == false){
                    if(posY > 0){
                        mapRect.move(0,-16);
                        posY--;
                    }
                }
                if(rect.getPosition().y-16 >= palette.getGlobalBounds().top){
                    if(box == true){
                        rect.move(0,-16);
                        rPosY--;
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                if(layer == false){
                    for(int i = 0; i < width; i++){
                        for(int j = 0; j < height; j++){
                             map.setTexture(sf::Vector2u(posX+i,posY+j), rPosY*(textures.get(Texture::Pokemon).getSize().x/16) + rPosX,1);
                        }
                    }
                }else if(layer == true){
                    for(int i = 0; i < width; i++){
                        for(int j = 0; j < height; j++){
                            map.setTexture(sf::Vector2u(posX+i,posY+j), rPosY*(textures.get(Texture::Pokemon).getSize().x/16) + rPosX,2);
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
                map.exportTextures("NewTexture.txt");
                map.exportWalkable("NewWalkable.txt");
            }
            if(input.getKey(0)){
                for(int i = 0; i < width; i++){
                    for(int j = 0; j < height; j++){
                         map.setWalkable(sf::Vector2u(posX+i,posY+j), false);
                    }
                }
            }

            if(input.getKey(5)){
                for(int i = 0; i < width; i++){
                    for(int j = 0; j < height; j++){
                        map.setWalkable(sf::Vector2u(posX+i,posY+j), true);
                    }
                }
            }
            if(input.getKeyUp(2)){
                box = !box;
            }
            if(input.getKeyUp(3)){
                if((posY+height)*16 < map.height()){
                    mapRect.setSize(sf::Vector2f(mapRect.getSize().x,16+mapRect.getSize().y));
                    height++;
                }else{
                    if(posY > 0){
                        posY--;
                        mapRect.move(0,-16);
                        mapRect.setSize(sf::Vector2f(mapRect.getSize().x,16+mapRect.getSize().y));
                        height++;
                    }
                }
            }
            if(input.getKeyUp(4)){
                if((posX+width)*16 < map.width()){
                    mapRect.setSize(sf::Vector2f(16+mapRect.getSize().x,mapRect.getSize().y));
                    width++;
                }else{
                    if(posX > 0){
                        posX--;
                        mapRect.move(-16,0);
                        mapRect.setSize(sf::Vector2f(16+mapRect.getSize().x,mapRect.getSize().y));
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
                    sf::Vector2f mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    float relPosX = mPos.x - view2.getViewport().left;
                    float relPosY = mPos.y - view2.getViewport().top;
                    int tileNumX = relPosX / 16;
                    int tileNumY = relPosY / 16;
                    rPosX = tileNumX;
                    rPosY = tileNumY;
                    rect.setPosition(palette.getGlobalBounds().left + rPosX*16,palette.getGlobalBounds().top+rPosY*16);
                }
            }
        }
        input.update();
        
        if(mapRect.getPosition().x > view1.getViewport().width){
            view1.setCenter(mapRect.getPosition());
        }
        
        
        window.setView(view1);
        pos.setString(std::to_string(posX) + "," + std::to_string(posY));
        pos.setPosition(mapRect.getPosition().x + 7, mapRect.getPosition().y + 7);
        
        //draw view1
        window.clear();
        map.draw(&window,1);
        if(layer)
            map.draw(&window, 2);
        window.draw(mapRect);
        window.draw(pos);
        window.draw(viewRect);
        //draw view2
        window.setView(view2);
        window.draw(palette);
        window.draw(rect);
        window.draw(textureBox);
        window.draw(lyer);
        //display
 
        window.display();
    }
    
    return 0;
}
