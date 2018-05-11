//-----------------------------------------------
//author: Gabriel Reiser
//contact: greiser37@gmail.com
//date last edited: 3/19/18

#include "Input.hpp"

//Type definition
typedef sf::Keyboard::Key key;  //typedef to make setting the constant array keys easier.

bool Input::lastKeys[NUM_KEY_CODES] = {0};  //Initializes all values in lastKeys to 0

//-----------------------------------------------
//Constant array of keys with indices that correspond to their codes
//THIS MAY BE ALTERED IN THE FUTURE AS MORE FUNCTIONALITY IS ADDED.
//-----------------------------------------------
key Input::keys[NUM_KEY_CODES] = {key::A, key::B,key::C,key::D,key::E,key::F,key::G,key::H,key::I,key::J,key::K,key::L,key::M,key::N,key::O,key::P,key::Q,key::R,key::S,key::T,key::U,key::V,key::W,key::X,key::Y,key::Z};



//-----------------------------------------------
//The function returns true if a given key was released since the last frame
//-----------------------------------------------
bool Input::getKeyUp(int keyCode){
    return !getKey(keyCode) && lastKeys[keyCode];
}



//-----------------------------------------------
//The function returns true if a given key was pressed since the last frame
//-----------------------------------------------
bool Input::getKeyDown(int keyCode){
    return getKey(keyCode) && !lastKeys[keyCode];
}



//-----------------------------------------------
//A function to record whether a given key is currently pressed.
//-----------------------------------------------
bool Input::getKey(int keyCode){
    key temp = keys[keyCode];
    return sf::Keyboard::isKeyPressed(temp);
}



//-----------------------------------------------
//Function to update all the keys that are pressed in the current frame.
//Called in every instance of the main game loop.
//-----------------------------------------------
void Input::update(){
    for(int i = 0; i < NUM_KEY_CODES; i++){
        lastKeys[i] = getKey(i);
    }
}
//-----------------------------------------------
