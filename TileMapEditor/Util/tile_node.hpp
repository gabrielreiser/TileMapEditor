//-----------------------------------------------
//author: Gabriel Reiser
//contact: greiser37@gmail.com
//date last edited: 3/19/18

#ifndef tile_node_hpp
#define tile_node_hpp

#include <SFML/Graphics.hpp>

class TileNode{
public:
    //Constructors
    TileNode();
    TileNode(unsigned int size, sf::Vector2f position);
    
    //Accessor Functions
    bool isWalkable();
    unsigned int getInteractable();
    unsigned int getSize();
    sf::RectangleShape getRect(int layer);
    sf::Vector2f getPosition();
    sf::IntRect getTextureRect(int layer);
    int getTextureKey(){return textureKey;}
    
    
    //Mutator Functions
    void setSize(unsigned int size);
    void setTextureKey(int texNum){textureKey = texNum;}
    void setTexture(const sf::Texture& tex, int layer);
    void setTextureRect(sf::IntRect texRect, int layer);
    void setWalkable(bool walk);
    void setInteractable(unsigned int interact);
    void setPosition(sf::Vector2f pos);
    void setFillColor(sf::Color color, int layer);
    
private:
    //MORE DATA MAY BE ADDED TO EACH NODE IN THE FUTURE
    int textureKey;
    bool walkable;
    unsigned int interactable;
    sf::RectangleShape texture;
    sf::RectangleShape textureLayer2;
};

#endif /* tile_node_hpp */
//-----------------------------------------------
