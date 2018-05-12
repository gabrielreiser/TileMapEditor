//-----------------------------------------------
//author: Gabriel Reiser
//contact: greiser37@gmail.com
//date last edited: 3/19/18

#include "Map.hpp"



//-----------------------------------------------
//Construct that takes the number of columns and the number of rows and the tile size.
//-----------------------------------------------
Map::Map(sf::Vector2u size, unsigned int tSize, const sf::Texture& tex){
    this->numRows = size.y;
    this->numCols = size.x;
    this->tSize = tSize;
    createTiles2d();
}



//-----------------------------------------------
//Default Constructor for the Map class, automatically sets the
//number of rows and columns and tile size.
//-----------------------------------------------
Map::Map(){
    numRows = 0;
    numCols = 0;
    tSize = 16;
    createTiles2d();
}



//-----------------------------------------------
//Function creates a 2D tiles vector of a certain size, while deleting
//the current 2D tile vector
//-----------------------------------------------
void Map::setSize(sf::Vector2u size, unsigned int tSize){
    this->numRows = size.x;
    this->numCols = size.y;
    this->tSize = tSize;
    createTiles2d();
}



//-----------------------------------------------
//Accessor functions for state data
//-----------------------------------------------
unsigned int Map::width(){
    return this->numCols*tSize;
}
unsigned int Map::height(){
    return this->numRows*tSize;
}
unsigned int Map::tileSize(){
    return this->tSize;
}



//-----------------------------------------------
//Function to load bool into tileNodes to see if they are walkable (1=walkable, 0=not walkable)
//-----------------------------------------------
void Map::loadWalkable(const std::string& fileName){
    if(this->tiles.empty()){
        createTiles2d();
        std::cout<<"Had to build in load walkable"<<std::endl;
    }
    std::ifstream inFS;
    openFile(&inFS, fileName);
    for(int i = 0; i<numCols; i++){
        for(int j = 0; j<numRows; j++){
            int c = inFS.peek();
            if(c == EOF){
                std::cerr<<"loadWalkable: Declared map size too big for file grid size."<<std::endl;
                inFS.close();
                exit(EXIT_FAILURE);
            }
            bool in{false};
            inFS>>in;
            tiles.at(j).at(i).setWalkable(in);
        }
    }
    inFS.close();
}



//-----------------------------------------------
//Function to load interactive code into tileNodes that
//correspond to unique attributes
//-----------------------------------------------
void Map::loadInteractable(const std::string& fileName){
    if(this->tiles.empty()){
        createTiles2d();
        std::cout<<"Had to build tiles in load interactable"<<std::endl;
    }
    std::ifstream inFS;
    openFile(&inFS, fileName);
    for(int i = 0; i<numCols; i++){
        for(int j = 0; j<numRows; j++){
            int c = inFS.peek();
            if(c == EOF){
                std::cerr<<"loadInteractable: Declared map size too big for file grid size."<<std::endl;
                inFS.close();
                exit(EXIT_FAILURE);
            }
            unsigned int in;
            inFS>>in;
            tiles.at(j).at(i).setInteractable(in);
        }
    }
    inFS.close();
}



//-----------------------------------------------
//Function to load the texture sheet the map will be using
//and also assign each individual tile a certain texture.
//We are using a double for loop so the speed is pretty slow as
//the numbers get higher
//-----------------------------------------------
void Map::loadTextures(const std::string& fileName,const sf::Texture& spriteSheet, int layerNumber){
    if(this->tiles.empty()){
        createTiles2d();
        std::cout<<"Had to build tiles in load Textures"<<std::endl;
    }
    std::ifstream inFS;
    openFile(&inFS, fileName);
    for(int i = 0; i<numCols; i++){
        for(int j = 0; j<numRows; j++){
            int texNum;
            inFS>>texNum;
            if(texNum == -1){
                tiles.at(j).at(i).setFillColor(sf::Color::Transparent, layerNumber);
                tiles.at(j).at(i).setTexture(spriteSheet,layerNumber);
            }else{
                tiles.at(j).at(i).setTexture(spriteSheet,layerNumber);
                tiles.at(j).at(i).setTextureRect(getTextureRect(texNum),layerNumber);
                tiles.at(j).at(i).setTextureKey(texNum);
            }
        }
    }
    inFS.close();
}


//-----------------------------------------------
//Function to return the proper texture rectangle, given a
//certain texture key number. This is a helper function
//for loadTextures.
//-----------------------------------------------
sf::IntRect Map::getTextureRect(int texNum){
    int topX = texNum * tSize;
    int topY = 0;
    while(topX >= 128){
        topX -= 128;
        topY += tSize;
    }
    int width = tSize;
    int height = tSize;
    sf::IntRect temp(topX,topY,width,height);
    return temp;
}



//-----------------------------------------------
//Drawing function that only draws the tiles that will be seen on the screen.
//FUNCTION RELIANT ON HAVING A RECTANGULAR MAP
//-----------------------------------------------
void Map::draw(sf::RenderWindow *window, sf::Vector2f viewSize, sf::Vector2u tilePos, int layer){
    if(this->tiles.empty()){
        std::cerr<<"Cannot Draw empty map"<<std::endl;
        exit(EXIT_FAILURE);
    }
    int fromX = tilePos.x - (viewSize.x/tSize) - 2;
    int toX  =  tilePos.x + (viewSize.x/tSize)/2 + 2;
    int fromY = tilePos.y - (viewSize.y/tSize) - 2;
    int toY  =  tilePos.y + (viewSize.y/tSize)/2 + 2;

    if(fromX < 0){fromX = 0;}
    if(toX > tiles.size()){toX = tiles.size();}
    if(fromY < 0){fromY = 0;}
    if(toY > tiles.at(0).size()){toY = tiles.at(0).size();}
    

    if(layer == 1){
        for(int i = fromX; i<toX; i++){
            for(int j = fromY; j<toY; j++){
                if(i > tiles.size() - 1  || j > tiles.at(i).size() - 1)
                    break;
                if(layer == 1){
                    window->draw(tiles.at(i).at(j).getRect(1));
                    if(tilePos.y>j){
                        window->draw(tiles.at(i).at(j).getRect(2));
                    }
                }
            }
        }
    }else if(layer == 2){
        fromY = tilePos.y;
        for(int i = fromX; i<toX; i++){
            for(int j = fromY; j<toY; j++){
                window->draw(tiles.at(i).at(j).getRect(2));
            }
        }
    }
}

void Map::draw(sf::RenderWindow *window, int layer){
    if(layer == 1){
        for(int i = 0; i < numCols; i++){
            for(int j = 0; j < numRows; j++){
                window->draw(tiles.at(i).at(j).getRect(1));
            }
        }
    }else if(layer == 2){
        for(int i = 0; i < numCols; i++){
            for(int j = 0; j < numRows; j++){
                window->draw(tiles.at(i).at(j).getRect(2));
            }
        }
    }
}

//-----------------------------------------------
//Method to create 2d vector of tileNodes
//-----------------------------------------------
void Map::createTiles2d(){
    clearTiles();
    for(int col = 0; col<numCols; col++){
        std::vector<TileNode> colVec;
        for(int row = 0; row<numRows; row++){
            TileNode temp(tSize,sf::Vector2f(col*tSize, row*tSize));
            colVec.push_back(temp);
        }
        this->tiles.push_back(colVec);
    }
}



//-----------------------------------------------
//Small function to help with opening files
//-----------------------------------------------
void Map::openFile(std::ifstream *in, const std::string& fileName){
    in->open(fileName);
    if (!in->is_open()) {
        std::cerr<<"Map: Unable to open file"<<std::endl;
        in->close();
        exit(EXIT_FAILURE);
    }
}



//-----------------------------------------------
//Function to return true if a certain tile is walkable
//-----------------------------------------------
bool Map::walkable(sf::Vector2u pos){
    if(pos.x > tiles.size() - 1 || tiles.at(0).size() - 1 < pos.y){
        return false;
    }
    return tiles.at(pos.x).at(pos.y).isWalkable();
}



//-----------------------------------------------
//Sets the value for walkable at a given tile node to the value
//the user passes in
//-----------------------------------------------
void Map::setWalkable(sf::Vector2u pos, bool walkable){
    this->tiles.at(pos.x).at(pos.y).setWalkable(walkable);
}

void Map::setTexture(sf::Vector2u pos, int tileNum, int layer){
    if(layer == 1){
        tiles.at(pos.x).at(pos.y).setTextureRect(getTextureRect(tileNum), 1);
        tiles.at(pos.x).at(pos.y).setTextureKey(tileNum);
    }else if(layer == 2){
        tiles.at(pos.x).at(pos.y).setTextureRect(getTextureRect(tileNum), 2);
        tiles.at(pos.x).at(pos.y).setFillColor(sf::Color::White, 2);
    }
}



//-----------------------------------------------
//Function to return the unique int key for the interactivity of a tile
//-----------------------------------------------
unsigned int Map::interactable(sf::Vector2u pos){
    if(pos.x > tiles.size() - 1 || tiles.at(0).size() - 1 < pos.y){
        return 0;
    }
    return tiles.at(pos.x).at(pos.y).getInteractable();
}



//-----------------------------------------------
//Function to return the position of a certain tile
//-----------------------------------------------
sf::Vector2f Map::getTilePosition(sf::Vector2u pos){
    if(numCols < pos.x || numRows < pos.y){
        std::cerr<<"getTilePosition: Tile not in range"<<std::endl;
        exit(EXIT_FAILURE);
    }else{
        return tiles.at(pos.x).at(pos.y).getPosition();
    }
}



//-----------------------------------------------
//Method to clear the tiles 2D vector
//-----------------------------------------------
void Map::clearTiles(){
    for(int i = 0; i < tiles.size(); i++){
        tiles.at(i).clear();
    }
    tiles.clear();
}
//-----------------------------------------------




void Map::exportTextures(const std::string& fileName){
    std::ofstream ofs (fileName);
    if(ofs.is_open()){
        for(int i = 0; i < numCols; i++){
            for(int j = 0; j < numRows; j++){
                ofs<<std::to_string(tiles.at(j).at(i).getTextureKey());
                ofs<<" ";
            }
            ofs<<std::endl;
        }
    }else{
        ofs.close();
        exit(EXIT_FAILURE);
    }
    ofs.close();
}

void Map::exportWalkable(const std::string& fileName){
    std::ofstream ofs(fileName);
    if(ofs.is_open()){
        for(int i = 0; i < numCols; i++){
            for(int j = 0; j < numRows; j++){
                ofs<<std::to_string(tiles.at(j).at(i).isWalkable());
                ofs<<" ";
            }
            ofs<<std::endl;
        }
    }else{
        ofs.close();
        exit(EXIT_FAILURE);
    }
    ofs.close();
}
