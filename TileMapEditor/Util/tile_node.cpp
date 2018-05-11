//-----------------------------------------------
//author: Gabriel Reiser
//contact: greiser37@gmail.com
//date last edited: 3/19/18

#include "tile_node.hpp"

//-----------------------------------------------
//Constructors for TileNode class
//-----------------------------------------------
TileNode::TileNode(){
    this->walkable = false;
    texture.setFillColor(sf::Color::White);
    textureLayer2.setFillColor(sf::Color::Transparent);

    texture.setSize(sf::Vector2f(16.f,16.f));
    textureLayer2.setSize(sf::Vector2f(16.f,16.f));
    texture.setPosition(0.f,0.f);
    textureLayer2.setPosition(0.f, 0.f);
}
TileNode::TileNode(unsigned int size, sf::Vector2f position){
    this->walkable = true;
    this->interactable = 0;
    texture.setFillColor(sf::Color::White);
    textureLayer2.setFillColor(sf::Color::Transparent);
    texture.setSize(sf::Vector2f(size,size));
    textureLayer2.setSize(sf::Vector2f(size,size));
    texture.setPosition(position);
    textureLayer2.setPosition(position);
}



//-----------------------------------------------
//Accessor functions for state data
//-----------------------------------------------
bool TileNode::isWalkable(){
    return this->walkable;
}
unsigned int TileNode::getInteractable(){
    return this->interactable;
}
sf::RectangleShape TileNode::getRect(int layer){
    if(layer == 1)
        return this->texture;
    if(layer == 2)
        return this->textureLayer2;
}
unsigned int TileNode::getSize(){
    return this->texture.getSize().x;
}
sf::Vector2f TileNode::getPosition(){
    return this->texture.getPosition();
}
sf::IntRect TileNode::getTextureRect(int layer){
    if(layer == 1)
        return this->texture.getTextureRect();
    if(layer == 2)
        return this->textureLayer2.getTextureRect();
}



//SETWALKABLE AND SETITERACTABLE CURRENTLY SETS COLOR FOR ALL TILES
//-----------------------------------------------
//Mutator functions for state data
//-----------------------------------------------
void TileNode::setSize(unsigned int size){
    this->texture.setSize(sf::Vector2f(size, size));
}
void TileNode::setTexture(const sf::Texture& tex, int layer){
    if(layer == 1)
        this->texture.setTexture(&tex);
    
    if(layer == 2){
        textureLayer2.setFillColor(sf::Color::White);
        this->textureLayer2.setTexture(&tex);
    }
}
void TileNode::setTextureRect(sf::IntRect texRect, int layer){
    if(layer == 1){
        this->texture.setTextureRect(texRect);
    }
    if(layer == 2){
        this->textureLayer2.setTextureRect(texRect);
    }
}
void TileNode::setFillColor(sf::Color color, int layer){
    if(layer == 1)
        texture.setFillColor(color);
    if(layer == 2)
        textureLayer2.setFillColor(color);
}
void TileNode::setWalkable(bool walk){
    //TEMPORARY SETTING OF COLORS BEFORE TEXTURES ARE ADDED
    if(walk){
        texture.setFillColor(sf::Color::White);
    }else{
        texture.setFillColor(sf::Color::Red);
    }
    this->walkable = walk;
}
void TileNode::setPosition(sf::Vector2f pos){
    this->texture.setPosition(pos);
}
void TileNode::setInteractable(unsigned int interact){
     //TEMPORARY SETTING OF COLORS BEFORE TEXTURES ARE ADDED
    if(interact == 1){
        if(walkable == false)
            texture.setFillColor(sf::Color::Red);
    }
    if(interact == 2){
        texture.setFillColor(sf::Color::Cyan);
    }
    if(interact == 3){
        texture.setFillColor(sf::Color::Cyan);
    }
    this->interactable = interact;
}
//-----------------------------------------

