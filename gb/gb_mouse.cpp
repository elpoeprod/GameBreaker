#include "../include/gamebreaker.hpp"

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
        if(mouse_button==mb::any) {
            return  (mybut[1] && !mylastbut[1]) or
                    (mybut[2] && !mylastbut[2]) or
                    (mybut[3] && !mylastbut[3]);
        }
        if(mouse_button!=mb::none)
            return mybut[mouse_button] && !mylastbut[mouse_button];

        return 0;
    }
    /**
    * check if mouse button was released
    * \sa mouse_button - mb::*
    **/
    int mouse::released(mb mouse_button)
    {
        if(mouse_button==mb::any) {
            return  (!mybut[1] && mylastbut[1]) or
                    (!mybut[2] && mylastbut[2]) or
                    (!mybut[3] && mylastbut[3]);
        }
        if(mouse_button!=mb::none)
            return (!mybut[mouse_button] && mylastbut[mouse_button]);

        return 0;
    }
    /**
    * check if mouse button is holding
    * \sa mouse_button - mb::*
    **/
    //int __debug__hold=0;
    int mouse::holding(mb mouse_button)
    {
        if(mouse_button==mb::any) {
            return  mybut[1] or
                    mybut[2] or
                    mybut[3];
        }
        if(mouse_button!=mb::none)
            return mybut[mouse_button];

        return 0;
    }

    /**
    * opposite of mouse::holding
    * \sa mouse_button - mb::*
    **/
    int mouse::nothing(mb mouse_button)
    {
        if(mouse_button==mb::any) {
            return  (!mybut[1] && !mylastbut[1]) or
                    (!mybut[2] && !mylastbut[2]) or
                    (!mybut[3] && !mylastbut[3]);
        }
        if(mouse_button!=mb::none)
            return !mybut[mouse_button] && !mylastbut[mouse_button];

        return 0;
    }

    mb mouse::which() {
        for(int i=0;i<4;i++) {
            if(mybut[i]) return (mb)i;
        }
        return mb::none;
    }
}