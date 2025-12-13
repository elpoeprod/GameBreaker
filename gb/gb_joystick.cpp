/*
 * Joystick(s) handling.
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"

void _gb_find_controllers()
{
    int ii = 0;
    GameBreaker::controllers.resize(SDL_NumJoysticks());
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            GameBreaker::controllers[ii] = SDL_GameControllerOpen(i);
            GameBreaker::gb_working_joystick = ii;
            ii++;
            GameBreaker::joy_count++;
        }
    }
}

namespace GameBreaker {

int myjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
int mylastjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
int gb_working_joystick = -1;

std::vector<SDL_GameController*> controllers;
int joy_count = 0;

	int joy::count()
	{
	    return joy_count;
	}
	
	int joy::working() { 
		return gb_working_joystick; 
	}
	
	int joy::pressed(int joy, int button) { 
		return myjoybut[joy][button] && !mylastjoybut[joy][button]; 
	}
	
	int joy::released(int joy, int button) { 
		return !myjoybut[joy][button] && mylastjoybut[joy][button]; 
	}

	int joy::holding(int joy, int button) { 
		return myjoybut[joy][button] && mylastjoybut[joy][button]; 
	}
	
}
