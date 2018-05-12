//
//  Grid.cpp
//  TileMapEditor
//
//  Created by Gabriel Reiser on 5/12/18.
//  Copyright © 2018 Gabriel Reiser. All rights reserved.
//

#include "Grid.hpp"

void Grid::init(){
    int cnt{0};
    for(int i = 0; i < texturesSize.x; i+=tileSize){
        mVertical[cnt].position = sf::Vector2f(i,0);
        mVertical[cnt].color = gridColor;
        cnt++;
        mVertical[cnt].position = sf::Vector2f(i+1,0);
        mVertical[cnt].color = gridColor;
        cnt++;
        mVertical[cnt].position = sf::Vector2f(i+1,texturesSize.y);
        mVertical[cnt].color = gridColor;
        cnt++;
        mVertical[cnt].position = sf::Vector2f(i,texturesSize.y);
        mVertical[cnt].color = gridColor;
        cnt++;
    }
    cnt = 0;
    for(int i = 0; i < texturesSize.y; i+=tileSize){
        mHorizontal[cnt].position = sf::Vector2f(0,i);
        mHorizontal[cnt].color = gridColor;
        cnt++;
        mHorizontal[cnt].position = sf::Vector2f(0,i+1);
        mHorizontal[cnt].color = gridColor;
        cnt++;
        mHorizontal[cnt].position = sf::Vector2f(texturesSize.x,i+1);
        mHorizontal[cnt].color = gridColor;
        cnt++;
        mHorizontal[cnt].position = sf::Vector2f(texturesSize.x,i);
        mHorizontal[cnt].color = gridColor;
        cnt++;
    }
}
