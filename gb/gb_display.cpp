/*
 * Display (display::) functions.
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_video.h>

namespace GameBreaker {

    int display::get_width() {
        SDL_Rect rect={0,0,0,0};
        SDL_GetDisplayBounds(display_current, &rect);
        return rect.w;
    }

    int display::get_height() {
        SDL_Rect rect={0,0,0,0};
        SDL_GetDisplayBounds(display_current, &rect);
        return rect.h;
    }

    
    SDL_Point display::get_size() {
        SDL_Rect rect={0,0,0,0};
        SDL_GetDisplayBounds(display_current,&rect);
        return {rect.w,rect.h};
    }
}
