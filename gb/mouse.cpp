/***************
 * GAMEBREAKER::MOUSE
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"

namespace GameBreaker {

    /**
    * check if mouse button was pressed
    * \sa mouse_button - mb::*
    **/
    int mouse::pressed(mb mouse_button)
    {
        return IsMouseButtonPressed(mouse_button);
    }
    /**
    * check if mouse button was released
    * \sa mouse_button - mb::*
    **/
    int mouse::released(mb mouse_button)
    {
		return IsMouseButtonReleased(mouse_button);
    }
    /**
    * check if mouse button is holding
    * \sa mouse_button - mb::*
    **/
    //int __debug__hold=0;
    int mouse::holding(mb mouse_button)
    {
		return IsMouseButtonDown(mouse_button);
    }

    /**
    * opposite of mouse::holding
    * \sa mouse_button - mb::*
    **/
    int mouse::nothing(mb mouse_button)
    {
        return IsMouseButtonUp(mouse_button);
    }

    mb mouse::which() {
        return mb::none;
    }

    int mouse::wheel_up() {
    	return GetMouseWheelMove()>0;
    }

    int mouse::wheel_down() {
    	return GetMouseWheelMove()<0;
    }
}
