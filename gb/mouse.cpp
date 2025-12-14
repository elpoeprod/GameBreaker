/***************
 * GAMEBREAKER::MOUSE
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"

namespace GameBreaker {

    int mybut[4]; //fucking warning i hate it
    int mylastbut[4];
    
    int system::chmouse(int id, int ch1, int ch2) {
        return (gb::_gbsys_->mybut[id]==ch1)&&(gb::_gbsys_->mylastbut[id]==ch2);
    }

    /**
    * check if mouse button was pressed
    * \sa mouse_button - mb::*
    **/
    int mouse::pressed(mb mouse_button)
    {
        if(mouse_button==mb::any) {
            return  _gbsys_->chmouse(1,1,0) or
                    _gbsys_->chmouse(2,1,0) or
                    _gbsys_->chmouse(3,1,0);
        }
        if(mouse_button!=mb::none)
            return _gbsys_->chmouse(mouse_button,1,0);

        return 0;
    }
    /**
    * check if mouse button was released
    * \sa mouse_button - mb::*
    **/
    int mouse::released(mb mouse_button)
    {
        if(mouse_button==mb::any) {
            return  _gbsys_->chmouse(1,0,1) or
                    _gbsys_->chmouse(2,0,1) or
                    _gbsys_->chmouse(3,0,1);
        }
        if(mouse_button!=mb::none)
            return _gbsys_->chmouse(mouse_button,0,1);

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
            return  _gbsys_->chmouse(1,1,1) or
                    _gbsys_->chmouse(2,1,1) or
                    _gbsys_->chmouse(3,1,1);
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
            return  _gbsys_->chmouse(1,0,0) or
                    _gbsys_->chmouse(2,0,0) or
                    _gbsys_->chmouse(3,0,0); 
        }
        if(mouse_button!=mb::none)
            return _gbsys_->chmouse(mouse_button,0,0);

        return 0;
    }

    mb mouse::which() {
        for(int i=0;i<4;i++) {
            if(mybut[i] or mylastbut[i]) 
            	return (mb)i;
        }
        return mb::none;
    }

    int mouse::wheel_up() {
    	return _gbsys_->get_event().wheel.y>0&&_gbsys_->get_event().wheel.y<2;
    }

    int mouse::wheel_down() {
    	return _gbsys_->get_event().wheel.y<0;
    }
}
