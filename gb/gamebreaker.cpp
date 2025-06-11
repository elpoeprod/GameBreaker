#include "gamebreaker.hpp"
#include "3rdparty/soloud/include/soloud.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <time.h>

#ifndef GB_DEFAULT_SAMPLESIZE
#define GB_DEFAULT_SAMPLESIZE 1024
#endif


int myjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
int mylastjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
int gb_working_joystick = -1;

std::vector<SDL_GameController*> controllers;
int joy_count = 0;

void findControllers()
{
    int ii = 0;
    controllers.resize(SDL_NumJoysticks());
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            controllers[ii] = SDL_GameControllerOpen(i);
            gb_working_joystick = ii;
            ii++;
            joy_count++;
        }
    }
}

/**********START*********************/
namespace GameBreaker {

SDL_Color _realcol_={255,255,255,255};
_curfont curfon={nullptr,0,0};
int current_time=0;
double master_vol = 1,
    _gm_halign=0, _gm_valign = 0;

GBWindow* gb_win;


//void *__sel_obj_;

//#define with(a) __sel_obj_=(void *)a;

int joy::count()
{
    return joy_count;
}
int joy::working() { return gb_working_joystick; }
int joy::pressed(int joy, int button) { return myjoybut[joy][button] && !mylastjoybut[joy][button]; }
int joy::released(int joy, int button) { return !myjoybut[joy][button] && mylastjoybut[joy][button]; }
int joy::holding(int joy, int button) { return myjoybut[joy][button] && mylastjoybut[joy][button]; }

int mouse::x = 0;
int mouse::y = 0;

__current date::current={
    .second=0,
    .minute=0,
    .hour=0,
    .day=0,
    .month=0,
    .year=0,
    .century=0,
    .planet=0,
    .millenium=0
};

Uint32 fps_lasttime = SDL_GetTicks();
Uint32 fps_current;
Uint32 fps_frames = 0;
GBFont *_fntDefault__;
int init(int x, int y, int w, int h, std::string label)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_WEBP | IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_AVIF | IMG_INIT_JXL | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_FLAC|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MOD);

    gb_win = new GBWindow;
    gb_win->win = SDL_CreateWindow(label.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
    gb_win->ren = SDL_CreateRenderer(gb_win->win, -1, GB_INIT_WIN_FLAGS);
    gb_win->x = x;
    gb_win->y = y;
    gb_win->w = w;
    gb_win->h = h;
    gb_win->running = 1;
    mouse::x = 0;
    mouse::y = 0;
    for (int i = 0; i < 3; i++) {
        mybut[i] = 0;
        mylastbut[i] = 0;
    }
    for (int i = 0; i < joy::count(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            myjoybut[i][ii] = 0;
            mylastjoybut[i][ii] = 0;
        }
    }
    findControllers();
    time_t tist=time(NULL);
    struct tm ts=*localtime(&tist);
    date::current.second=ts.tm_sec;
    date::current.minute=ts.tm_sec;
    date::current.hour=ts.tm_hour;
    date::current.day=ts.tm_mday;
    date::current.month=ts.tm_mon;
    date::current.year=ts.tm_year;
    date::current.century=math::floor(ts.tm_year/365.25);
    date::current.planet=2;
    date::current.millenium=math::floor(date::current.year);
    _fntDefault__=font::add("3rdparty/sourcesans.ttf",12);
    graphics::draw::set_font(_fntDefault__);
    graphics::draw::color(0xFFFFFF);

    return 1;
}

void io::clear() {
    for (int i = 0; i < 3; i++) {
        mylastbut[i] = 0;
    }
    for (int i = 0; i < controllers.size(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            mylastjoybut[i][ii] = 0;
            myjoybut[i][ii] = 0;
        }
    }
    mykey.clear();
    mylastkey.clear();
}

void update()
{
    //findControllers();
    SDL_SetRenderDrawBlendMode(gb_win->ren, SDL_BlendMode::SDL_BLENDMODE_BLEND);
    for (int i = 1; i < 4; i++) {
        mylastbut[i] = mybut[i];
    }
    for (int i = 0; i < controllers.size(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            mylastjoybut[i][ii] = myjoybut[i][ii];
            myjoybut[i][ii] = SDL_GameControllerGetButton(controllers[i], (SDL_GameControllerButton)ii);
        }
    }
    mylastkey=mykey;

    while (SDL_PollEvent(&gb_win->ev) != 0) {
        switch(gb_win->ev.type) {
            case SDL_KEYDOWN: mykey[SDL_GetKeyName(gb_win->ev.key.keysym.sym)]=1; break;
            case SDL_KEYUP: mykey[SDL_GetKeyName(gb_win->ev.key.keysym.sym)]=0; break;
            case SDL_QUIT: gb_win->running = 0; break;
            case SDL_MOUSEMOTION: mouse::x=gb_win->ev.motion.x; mouse::y=gb_win->ev.motion.y; break;
            case SDL_MOUSEBUTTONDOWN: {
                    mybut[gb_win->ev.button.button] = 1;
            } break;
            case SDL_MOUSEBUTTONUP: {
                    mybut[gb_win->ev.button.button] = 0;
            } break;
        }

    }
    current_time=SDL_GetTicks();
    
#ifdef GB_GAME_END_ON_ESC
    if(keyboard::released(SDLK_ESCAPE)) gb_win->running=0;
#endif
    
    /*
    int i=0;
    repeat(gb_objects.size()) {
        (*gb_objects[i])->hspd=math::lendir_x((*gb_objects[i])->spd,(*gb_objects[i])->direction);
        (*gb_objects[i])->vspd=math::lendir_y((*gb_objects[i])->spd,(*gb_objects[i])->direction);
        (*gb_objects[i])->x+=(*gb_objects[i])->hspd;
        (*gb_objects[i])->y+=(*gb_objects[i])->vspd;
        if((*gb_objects[i])->spd>0)
            (*gb_objects[i])->spd-=(*gb_objects[i])->friction;
        else {
            if((*gb_objects[i])->spd<0)
                (*gb_objects[i])->spd+=(*gb_objects[i])->friction;
            else (*gb_objects[i])->spd=0;
        }
        i++;
    }
    */

    int i=0;
    repeat(gb_objects.size()) {
        gb_objects[i]->hspd=math::lendir_x(gb_objects[i]->spd,gb_objects[i]->direction);
        gb_objects[i]->vspd=math::lendir_y(gb_objects[i]->spd,gb_objects[i]->direction);
        gb_objects[i]->x+=gb_objects[i]->hspd;
        gb_objects[i]->y+=gb_objects[i]->vspd;
        if(gb_objects[i]->spd>0)
            gb_objects[i]->spd-=gb_objects[i]->friction;
        else {
            if(gb_objects[i]->spd<0)
                gb_objects[i]->spd+=gb_objects[i]->friction;
            else gb_objects[i]->spd=0;
        }
        i++;
    }

    fps_frames++;
    if (fps_lasttime < current_time - 1.0*1000) //1.0 is one second; update 1 second
    {
        fps_lasttime = current_time;
        fps_current = fps_frames;
        fps_frames = 0;
    }
}
int running(void) { update(); return gb_win->running; }

/**
 * updates screen
 **/
void screen::draw(double fps)
{
    SDL_RenderPresent(gb_win->ren);
    SDL_Delay(1000.f / fps);
}

void screen::end() {
    gb_win->running=0;
}

void shutdown()
{
    for (int i = 0; i < gb_objects.size(); i++) {
        object::destroy(gb_objects[i]);
    }
    for (int i = 0; i < gb_sprites.size(); i++) {
        graphics::sprite::destroy(gb_sprites[i]);
    }
    for (int i = 0; i < gb_sounds.size(); i++) {
        sound::destroy(gb_sounds[i]);
    }
    for (int i = 0; i < gb_fonts.size(); i++) {
        font::destroy(gb_fonts[i]);
    }

    gb_objects.clear();
    gb_sounds.clear();
    gb_sprites.clear();
    gb_fonts.clear();
    IMG_Quit();
    TTF_Quit();
    __mus_handle->deinit();
}


SDL_Color color::black = { 0, 0, 0, 255 },
          color::white = { 255, 255, 255, 255 },
          color::red = { 255, 0, 0, 255 },
          color::blue = { 0, 0, 255, 255 },
          color::green = { 0, 200, 0, 255 },
          color::lime = { 0, 255, 50, 255 },
          color::gray = { 128, 128, 128, 255 },
          color::lt_gray = { 192, 192, 192, 255 },
          color::dk_gray = { 80, 80, 80, 255 },
          color::fuchsia = { 200, 50, 200, 255 },
          color::purple = { 100, 16, 192, 255 },
          color::aqua = { 50, 255, 255, 255 },
          color::pink = { 255, 128, 128, 255 };

}





