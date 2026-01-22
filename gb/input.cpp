/***************
 * GAMEBREAKER::INPUT
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




	// Keyboard

	int vk_nokey=0,
		vk_anykey=512,
		vk_enter=KEY_ENTER,
		vk_ret=vk_enter,
		vk_shift=KEY_LEFT_SHIFT,
		vk_control=KEY_LEFT_CONTROL,
		vk_alt=KEY_LEFT_ALT,
		vk_escape=KEY_ESCAPE,
		vk_space=KEY_SPACE,
		vk_backspace=KEY_BACKSPACE,
		vk_tab=KEY_TAB,
		vk_pause=KEY_PAUSE,
		vk_printscreen=KEY_PRINT_SCREEN,
		vk_left=KEY_LEFT,
		vk_right=KEY_RIGHT,
		vk_up=KEY_UP,
		vk_down=KEY_DOWN,
		vk_home=KEY_HOME,
		vk_end=KEY_END,
		vk_pageup=KEY_PAGE_UP,
		vk_pagedown=KEY_PAGE_DOWN,
		vk_del=KEY_DELETE,
		vk_ins=KEY_INSERT,
		vk_f1=KEY_F1,
		vk_f2=KEY_F2,
		vk_f3=KEY_F3,
		vk_f4=KEY_F4,
		vk_f5=KEY_F5,
		vk_f6=KEY_F6,
		vk_f7=KEY_F7,
		vk_f8=KEY_F8,
		vk_f9=KEY_F9,
		vk_f10=KEY_F10,
		vk_f11=KEY_F11,
		vk_f12=KEY_F12,
		vk_numpad0=KEY_KP_0,
		vk_numpad1=KEY_KP_1,
		vk_numpad2=KEY_KP_2,
		vk_numpad3=KEY_KP_3,
		vk_numpad4=KEY_KP_4,
		vk_numpad5=KEY_KP_5,
		vk_numpad6=KEY_KP_6,
		vk_numpad7=KEY_KP_7,
		vk_numpad8=KEY_KP_8,
		vk_numpad9=KEY_KP_9,
		vk_divide=KEY_KP_DIVIDE,
		vk_multiply=KEY_KP_MULTIPLY,
		vk_subtract=KEY_KP_SUBTRACT,
		vk_add=KEY_KP_ADD,
		vk_decimal=KEY_KP_DECIMAL,
		vk_lshift=KEY_LEFT_SHIFT,
		vk_rshift=KEY_RIGHT_SHIFT,
		vk_lalt=KEY_LEFT_ALT,
		vk_ralt=KEY_RIGHT_ALT,
		vk_lcontrol=KEY_LEFT_CONTROL,
		vk_rcontrol=KEY_RIGHT_CONTROL;

	int keyboard::pressed(int key) {
		return IsKeyPressed(key);
	}

	int keyboard::holding(int key) {
		return IsKeyDown(key);
	}

	int keyboard::released(int key) {
		return IsKeyReleased(key);
	}




	// Joystick

	int joy_cross=GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
		joy_triangle=GAMEPAD_BUTTON_RIGHT_FACE_UP,
		joy_circle=GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
		joy_square=GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
		joy_select=GAMEPAD_BUTTON_MIDDLE_LEFT,
		joy_dpad_up=GAMEPAD_BUTTON_LEFT_FACE_UP,
		joy_dpad_down=GAMEPAD_BUTTON_LEFT_FACE_DOWN,
		joy_dpad_left=GAMEPAD_BUTTON_LEFT_FACE_LEFT,
		joy_dpad_right=GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
		joy_rbumper=GAMEPAD_BUTTON_RIGHT_TRIGGER_2,
		joy_lbumper=GAMEPAD_BUTTON_LEFT_TRIGGER_2,
		joy_ltrigger=GAMEPAD_BUTTON_LEFT_TRIGGER_1,
		joy_rtrigger=GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
		joy_middle=GAMEPAD_BUTTON_MIDDLE,
		joy_start=GAMEPAD_BUTTON_MIDDLE_RIGHT,
		joy_lthumb=GAMEPAD_BUTTON_LEFT_THUMB,
		joy_rthumb=GAMEPAD_BUTTON_RIGHT_THUMB,
		joy_unknown=0,
		joy_axis_lx=GAMEPAD_AXIS_LEFT_X,
		joy_axis_ly=GAMEPAD_AXIS_LEFT_Y,
		joy_axis_rx=GAMEPAD_AXIS_RIGHT_X,
		joy_axis_ry=GAMEPAD_AXIS_RIGHT_Y,
		joy_axis_ltrigger=GAMEPAD_AXIS_LEFT_TRIGGER,
		joy_axis_rtrigger=GAMEPAD_AXIS_RIGHT_TRIGGER;

	int joystick::exists(int id) {
		return IsGamepadAvailable(id);
	}

	str joystick::name(int id) {
		return GetGamepadName(id);
	}	

	int joystick::pressed(int id, int button) {
		return IsGamepadButtonPressed(id, button);
	}

	int joystick::holding(int id, int button) {
		return IsGamepadButtonDown(id, button);
	}

	int joystick::released(int id, int button) {
		return IsGamepadButtonReleased(id, button);
	}

	int joystick::axes(int id) {
		return GetGamepadAxisCount(id);
	}

	real joystick::axis_pos(int id, int axis) {
		return GetGamepadAxisMovement(id, axis);
	}
}
