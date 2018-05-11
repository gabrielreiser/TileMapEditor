//-----------------------------------------------
//author: Gabriel Reiser
//contact: greiser37@gmail.com
//date last edited: 3/19/18

#ifndef Input_hpp
#define Input_hpp

#include <SFML/Graphics.hpp>

class Input{
public:
    static void update();
    static bool getKeyUp(int keyCode);
    static bool getKeyDown(int keyCode);
    static bool getKey(int keyCode);
private:
    static const int NUM_KEY_CODES = 50;    //Constant refer to the number of possible key codes.
    static sf::Keyboard::Key keys[NUM_KEY_CODES];
    static bool lastKeys[NUM_KEY_CODES];    //All keys pressed in a given frame
};

#endif /* Input_hpp */
//-----------------------------------------------
