#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_video.h>

namespace GameBreaker {

    void window::set_icon(gb_str ico) {
        SDL_Surface *temp=IMG_Load(ico.c_str());
        SDL_SetWindowIcon(gb_win->win,temp);
        SDL_FreeSurface(temp);
    }

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
    SDL_Point get_pos() {
        int x=0,y=0;
        SDL_GetWindowPosition(gb_win->win, &x,&y);
        return (SDL_Point){x,y};
    }
    /**
    * returns window width
    **/
    int window::get_width() { return gb_win->w; }
    /**
    * returns window height
    **/
    int window::get_height() { return gb_win->h; }

    /**
    * returns window size as a struct {w,h} that can be used somewhere
    **/
    SDL_Point window::get_size() { return (SDL_Point) { gb_win->w, gb_win->h }; }

}