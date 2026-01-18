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
    	if(mouse_button==mb::any) {
    		return 	IsMouseButtonPressed(mb::left) or
    				IsMouseButtonPressed(mb::right) or
    				IsMouseButtonPressed(mb::middle);
    	}
        return IsMouseButtonPressed(mouse_button);
    }
    /**
    * check if mouse button was released
    * \sa mouse_button - mb::*
    **/
    int mouse::released(mb mouse_button)
    {	
    	if(mouse_button==mb::any) {
    		return 	IsMouseButtonReleased(mb::left) or
    				IsMouseButtonReleased(mb::right) or
    				IsMouseButtonReleased(mb::middle);
    	}
		return IsMouseButtonReleased(mouse_button);
    }
    /**
    * check if mouse button is holding
    * \sa mouse_button - mb::*
    **/
    //int __debug__hold=0;
    int mouse::holding(mb mouse_button)
    {
    	if(mouse_button==mb::any) {
    		return 	IsMouseButtonDown(mb::left) or
    				IsMouseButtonDown(mb::right) or
    				IsMouseButtonDown(mb::middle);
    	}
		return IsMouseButtonDown(mouse_button);
    }

    /**
    * opposite of mouse::holding
    * \sa mouse_button - mb::*
    **/
    int mouse::nothing(mb mouse_button)
    {
    	if(mouse_button==mb::any) {
    		return 	IsMouseButtonUp(mb::left) or
    				IsMouseButtonUp(mb::right) or
    				IsMouseButtonUp(mb::middle);
    	}
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
