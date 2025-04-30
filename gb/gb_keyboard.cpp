#include "gamebreaker.hpp"

namespace GameBreaker {
    std::map<std::string,int> mykey;
    std::map<std::string,int> mylastkey;

    int keyboard::holding(int key) {return mykey[SDL_GetKeyName(key)]&&mylastkey[SDL_GetKeyName(key)];}
    int keyboard::pressed(int key) {return mykey[SDL_GetKeyName(key)]&&!mylastkey[SDL_GetKeyName(key)];}
    int keyboard::released(int key) {return !mykey[SDL_GetKeyName(key)]&&mylastkey[SDL_GetKeyName(key)];}
}