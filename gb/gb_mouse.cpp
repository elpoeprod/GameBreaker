#include "gamebreaker.hpp"

/***************
 * GAMEBREAKER::MOUSE
*/

namespace GameBreaker {

    int mybut[4]; //fucking warning i hate it
    int mylastbut[4];

    /**
    * check if mouse button was pressed
    * \sa mouse_button - mb::*
    **/
    int mouse::pressed(mb mouse_button)
    {
        return mybut[mouse_button] && !mylastbut[mouse_button];
    }
    /**
    * check if mouse button was released
    * \sa mouse_button - mb::*
    **/
    int mouse::released(mb mouse_button)
    {
        return !mybut[mouse_button] && mylastbut[mouse_button];
    }
    /**
    * check if mouse button is holding
    * \sa mouse_button - mb::*
    **/
    //int __debug__hold=0;
    int mouse::holding(mb mouse_button)
    {
        //if(__debug__hold<20) __debug__hold++; else {printf("IS HOLDING??????????? %i\n",mybut[mouse_button]);__debug__hold=0;}
        return mybut[mouse_button];// && mylastbut[mouse_button];
    }

    /**
    * opposite of mouse::holding
    * \sa mouse_button - mb::*
    **/
    int mouse::nothing(mb mouse_button)
    {
        return !mybut[mouse_button] && !mylastbut[mouse_button];
    }
}