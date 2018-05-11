//-----------------------------------------------
//author: Gabriel Reiser
//contact: greiser37@gmail.com
//date last edited: 3/19/18

#ifndef map_hpp
#define map_hpp

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "tile_node.hpp"
#include "ResourceHolder.hpp"

class Map{
public:
    //Constructors
    Map(sf::Vector2u size, unsigned int tSize, const sf::Texture& tex);
    Map();
    
    //Accessor Methods
    unsigned int height();
    unsigned int width();
    unsigned int tileSize();
    
    //Mutator Methods
    void setSize(sf::Vector2u size, unsigned int tSize);
    void setWalkable(sf::Vector2u pos, bool walkable);
    void setTexture(sf::Vector2u pos, int tileNum);
    
    void exportTextures(const std::string& fileName);
    void export
    
    bool walkable(sf::Vector2u pos);
    
    unsigned int interactable(sf::Vector2u pos);
    sf::Vector2f getTilePosition(sf::Vector2u pos);
    void draw(sf::RenderWindow *window, sf::Vector2f viewSize, sf::Vector2u TilePosition, int layer);
    void draw(sf::RenderWindow *window);
    void loadWalkable(const std::string& fileName);
    void loadInteractable(const std::string& fileName);
    void loadTextures(const std::string& fileName,const sf::Texture& spriteSheet, int layerNumber);

private:
    unsigned int numCols;
    unsigned int numRows;
    unsigned int tSize;
    std::vector<std::vector<TileNode>> tiles;
    
    void createTiles2d();
    void openFile(std::ifstream *in, const std::string& fileName);
    void clearTiles();
    sf::IntRect getTextureRect(int texNum);
};

#endif /* map_hpp */
//-----------------------------------------------
