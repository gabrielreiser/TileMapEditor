//
//  Grid.hpp
//  TileMapEditor
//
//  Created by Gabriel Reiser on 5/12/18.
//  Copyright © 2018 Gabriel Reiser. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable{
public:
    Grid(sf::Vector2u textureSize, const int size, const sf::Color color) : tileSize(size), gridColor(color){
        this->texturesSize = textureSize;
        mVertical.setPrimitiveType(sf::Quads);
        mVertical.resize(textureSize.x*4);
        mHorizontal.setPrimitiveType(sf::Quads);
        mHorizontal.resize(textureSize.y*4);
        init();
    }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(mVertical);
        target.draw(mHorizontal);
    }
    void init();
    const int tileSize;
    const sf::Color gridColor;
    sf::Vector2u texturesSize;
    sf::VertexArray mVertical;
    sf::VertexArray mHorizontal;
};



#endif /* Grid_hpp */
