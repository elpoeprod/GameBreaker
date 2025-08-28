#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_video.h>

namespace GameBreaker {

	/**
	* sets an icon for the window
	**/
    void window::set_icon(gb_str ico) {
        SDL_Surface *temp=IMG_Load(ico.c_str());
        SDL_SetWindowIcon(gb_win->win,temp);
        SDL_FreeSurface(temp);
    }

    /**
    * sets a title for the window
    **/
    void window::set_title(gb_str title) {
        SDL_SetWindowTitle(gb_win->win,title.c_str());

    }
    
    /**
    * sets window width and height
    **/
    void window::set_size(int w, int h)
    {
        SDL_SetWindowSize(gb_win->win, w, h);
        gb_win->w = w;
        gb_win->h = h;
    }
    
    /**
    * sets window position (x and y)
    **/
    void window::set_pos(int x, int y)
    {
        SDL_SetWindowPosition(gb_win->win, x, y);
        gb_win->x = x;
        gb_win->y = y;
    }

    /**
    * gets window coordinates on screen
    **/
    SDL_Point get_pos() {
        int x=0,y=0;
        SDL_GetWindowPosition(gb_win->win, &x,&y);
        return (SDL_Point){x,y};
    }
    
    /**
    * returns window width
    **/
    int window::get_width() { 
    	return gb_win->w; 
    }

    /**
    * returns window height
    **/
    int window::get_height() { 
    	return gb_win->h; 
    }

    /**
    * returns window size as a struct {w,h} that can be used somewhere
    **/
    SDL_Point window::get_size() { 
    	return (SDL_Point) { gb_win->w, gb_win->h }; 
    }

    SDL_Renderer* window::get_renderer() { 
    	return gb_win->ren; 
    }

    void window::set_priority(int num) {
        SDL_SetThreadPriority((SDL_ThreadPriority)num); // 0 - low, 3 - high like on drugs
    }

    int window::get_ontop() {
    	return SDL_GetWindowFlags(gb_win->win)&SDL_WINDOW_ALWAYS_ON_TOP;
    }

    void window::set_ontop(int enable) {
		SDL_SetWindowAlwaysOnTop(gb_win->win,enable>0.5?SDL_TRUE:SDL_FALSE);
    	return;
    }

    void window::show_borders(int enable) {
		SDL_SetWindowBordered(gb_win->win,enable>0.5?SDL_TRUE:SDL_FALSE);
    	return;
    }
    void window::grab(int enable) {
		SDL_SetWindowGrab(gb_win->win,enable>0.5?SDL_TRUE:SDL_FALSE);
    	return;
    }

}
