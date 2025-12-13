/*
 * Keyboard handling
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"

namespace GameBreaker {
    std::map<std::string,int> mykey;
    std::map<std::string,int> mylastkey;

    int keyboard::holding(int key) {
        return mykey[SDL_GetKeyName(key)]&&mylastkey[SDL_GetKeyName(key)];
    }
    
    int keyboard::pressed(int key) {
        return mykey[SDL_GetKeyName(key)]&&!mylastkey[SDL_GetKeyName(key)];
    }
    
    int keyboard::released(int key) {
        return !mykey[SDL_GetKeyName(key)]&&mylastkey[SDL_GetKeyName(key)];
    }
    
    int keyboard::ord(char *key) {
        return (int)key[0];
    };
    
    char *keyboard::chr(int ch) {
		char mych[2]={(char)ch,0};
		char *mymy=mych;
        return mymy;
    } //i think this is bad

}
