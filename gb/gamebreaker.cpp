/*
    This file is meant to handle rendering stuff on the screen(s),
    Find controllers, handle joystick, mouse and keyboard input,
    And initialize/end system.
*/

#include "../include/gamebreaker.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <dirent.h>
#include <time.h>
#include <algorithm>

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

double  view_xview[GB_MAX_ROOM_CAMERAS]={0,0,0,0,0,0,0,0},
        view_yview[GB_MAX_ROOM_CAMERAS]={0,0,0,0,0,0,0,0},
        view_angle[GB_MAX_ROOM_CAMERAS]={0,0,0,0,0,0,0,0};
int     view_wview[GB_MAX_ROOM_CAMERAS]={0,0,0,0,0,0,0,0},
        view_hview[GB_MAX_ROOM_CAMERAS]={0,0,0,0,0,0,0,0};

/**********START*********************/
namespace GameBreaker {

SDL_Color _realcol_={255,255,255,255};
_curfont curfon={nullptr,0,0};
int current_time=0;
double master_vol = 1,
    _gm_halign=0, _gm_valign = 0;

GBRoom *room_current;
int myrealcurroom=-1;
std::string keyboard_string="";

int display_current=0;

int display::mouse_x=0;
int display::mouse_y=0;

GBWindow* gb_win;
SoLoud::Soloud *__mus_handle=new SoLoud::Soloud;

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

int room::width=0;
int room::height=0;

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



int init(int x, int y, std::string label)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_WEBP | IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_AVIF | IMG_INIT_JXL | IMG_INIT_TIF);
    __mus_handle->init();

    gb_win = new GBWindow;
    gb_win->cur_win=0;
    gb_win->win = SDL_CreateWindow(label.c_str(), x, y, 640,480, SDL_WINDOW_SHOWN);
    gb_win->ren = SDL_CreateRenderer(gb_win->win, -1, GB_INIT_WIN_FLAGS);
    gb_win->x = x;
    gb_win->y = y;
    gb_win->w = 640;
    gb_win->h = 480;
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
    date::current.planet=3; //0 - sun
    date::current.millenium=math::floor((date::current.year/1000)+1);
    
    //_fntDefault__=font::add("default.ttf",12);
    //graphics::draw::set_font(_fntDefault__);
    graphics::draw::color(0xFFFFFF);
    room_current=nullptr;

    return 1;
}

void io::clear() {
    for (int i = 0; i < 3; i++) {
        mylastbut[i] = 0;
    }
    for (int i = 0; i < (int)controllers.size(); i++) {
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
    // Sets blend mode to default because yeah
    SDL_SetRenderDrawBlendMode(gb_win->ren, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    // Mouse event
    for (int i = 1; i < 4; i++) {
        mylastbut[i] = mybut[i];
    }

    // Joystick event
    for (int i = 0; i < (int)controllers.size(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            mylastjoybut[i][ii] = myjoybut[i][ii];
            myjoybut[i][ii] = SDL_GameControllerGetButton(controllers[i], (SDL_GameControllerButton)ii);
        }
    }
    mylastkey=mykey;

    // Events
    while (SDL_PollEvent(&gb_win->ev) != 0) {
        switch(gb_win->ev.type) {
			//Keyboard
            case SDL_KEYDOWN: 
            	mykey[SDL_GetKeyName(gb_win->ev.key.keysym.sym)]=1; 
            	if(gb_win->ev.key.keysym.sym==SDLK_RETURN)
            		keyboard_string+="\n";
            	else 
            		keyboard_string+=SDL_GetKeyName(gb_win->ev.key.keysym.sym);
            	break;
            
            case SDL_KEYUP: mykey[SDL_GetKeyName(gb_win->ev.key.keysym.sym)]=0; break;

            //Exit
            case SDL_QUIT: gb_win->running = 0; break;

			//Mouse
            case SDL_MOUSEMOTION: 
                mouse::x=gb_win->ev.motion.x; 
                mouse::y=gb_win->ev.motion.y; 
            break;

            case SDL_MOUSEBUTTONDOWN: {
                    mybut[gb_win->ev.button.button] = 1;
            } break;

            case SDL_MOUSEBUTTONUP: {
                    mybut[gb_win->ev.button.button] = 0;
            } break;
        }

    }
    current_time=SDL_GetTicks(); //current time
    
#ifdef GB_GAME_END_ON_ESC
    if(keyboard::released(SDLK_ESCAPE)) gb_win->running=0; // if pressed then end game
#endif

	time_t tist=time(NULL);
    struct tm ts=*localtime(&tist);
    date::current.second=ts.tm_sec;
    date::current.minute=ts.tm_sec;
    date::current.hour=ts.tm_hour;
    date::current.day=ts.tm_mday;

    SDL_GetGlobalMouseState(&display::mouse_x,&display::mouse_y);

    for(int i=0;i<GB_MAX_ROOM_CAMERAS;i++) {
        room_current->view[i].x=view_xview[i];
        room_current->view[i].y=view_yview[i];
        room_current->view[i].w=view_wview[i];
        room_current->view[i].h=view_hview[i];
        room_current->view[i].angle=view_angle[i];
    }

    room::width=room_current->width;
    room::height=room_current->height;

	if(room_current->background_visible) {
		/*if(room_current->background_image!=nullptr) {
			graphics::draw::sprite_ext(room_current->background_image,0,0,room_current->width/room_current->background_image->w,
			room_current->height/room_current->background_image->h,0,(room_current->background_color));
		}*/
		auto _col=graphics::draw::color_get();
		graphics::draw::color_sdl(room_current->background_color);
		int _room_borders=100;
		graphics::draw::rect(view_xview[0]-_room_borders,view_yview[0]-_room_borders,room::width+_room_borders,room::height+_room_borders,0);
		graphics::draw::color_sdl(_col);
	}
    int __i=0; // For ALL object count
    int _iobj=0; // For CURRENT ROOM object count
    	//puts("1");
        repeat(room_current->objects.size()) {
        	//puts("2");
        	__i=0;
            repeat(gb_objects.size()) {
            	//puts("3");
                if((gb_objects[__i]->id==room_current->objects[_iobj].obj_id)==1) {

					if(gb_objects[__i]->spr!=nullptr) {
						if(gb_objects[__i]->image_index<gb_objects[__i]->spr->frames-1) 
							gb_objects[__i]->image_index+=gb_objects[__i]->image_speed;
						else
							gb_objects[__i]->image_index=0;
					}
                
                    // Speed
                    gb_objects[__i]->hspd=math::lendir_x(gb_objects[__i]->spd,gb_objects[__i]->direction);
                    gb_objects[__i]->vspd=math::lendir_y(gb_objects[__i]->spd,gb_objects[__i]->direction);
                    // Position
                    gb_objects[__i]->x+=gb_objects[__i]->hspd;
                    gb_objects[__i]->y+=gb_objects[__i]->vspd;
                    if(gb_objects[__i]->spd>0)
                        gb_objects[__i]->spd-=gb_objects[__i]->friction;
                    else {
                        if(gb_objects[__i]->spd<0)
                            gb_objects[__i]->spd+=gb_objects[__i]->friction;
                        else gb_objects[__i]->spd=0;
                    }

					if(room_current->id!=myrealcurroom) {
						myrealcurroom=room_current->id;
						if(room_current->objects[_iobj].event_create)
							room_current->objects[_iobj].event_create();
					}
					for(int j=0;j<GB_MAX_OBJ_ALARMS;j++) {
						if(gb_objects[__i]->alarm[j]>0) {
							gb_objects[__i]->alarm[j]--;
						}
						else {
							if(gb_objects[__i]->alarm[j]==0) {
								gb_objects[__i]->alarm[j]=-1;
								if(gb_objects[__i]->event_alarm[j])
									gb_objects[__i]->event_alarm[j]();
							}
						}
					}
					
					//puts("3");
                    //Events
                    if(gb_objects[__i]->event_step_begin)
                        gb_objects[__i]->event_step_begin();
					//puts("3.1");
                    if(gb_objects[__i]->event_step)
                        gb_objects[__i]->event_step();
                    //puts("3.2");
                    if(gb_objects[__i]->event_step_end)
                        gb_objects[__i]->event_step_end();

					//puts("4");
                    //this fucking sucks
                    //WARNING VERY UNREADABLE CODE
                    auto si=gb_objects.size();
                    int myvec[si];
                    for(long unsigned int i=0;i<si;i++) {
                        myvec[i]=gb_objects[i]->depth;
                    }
                    //printf("\n");
                    std::sort(myvec,myvec+(sizeof(myvec)/sizeof(myvec[0])),std::greater<int>());
                    /*for(long unsigned int i=0;i<si;i++) {
                    	printf("%i\n",myvec[i]);
                    }
                    printf("\n");
                    */
                    for(long unsigned int i=0;i<si;i++) {
                    	for(long unsigned ii=0;ii<si;ii++) {
	                        if(gb_objects[i]->depth==myvec[ii]&&(gb_objects[i]->id==room_current->objects[_iobj].obj_id)==1) {
	                            if(gb_objects[i]->event_draw!=nullptr)
	                                gb_objects[i]->event_draw();
	                        }
                        }
                    }
                }
                __i++;
            }
            _iobj++;
        }

    fps_frames++;
    if (fps_lasttime < current_time - 1.0*1000) //1.0 is one second; update 1 second
    {
        fps_lasttime = current_time;
        fps_current = fps_frames;
        fps_frames = 0;
    }
}
void run() {
    if(room_current==nullptr) {
        show::error("WARNING\nThe current room was "
                    "not set and the program will now exit.\n"
                    "Did you forgot to put `GameBreaker::room::current()` function "
                    "before `GameBreaker::run()`?",1); 
        exit(0x0000000); 
        return;
    }
    while(gb_win->running) {
        update(); 
        screen::draw(room_current->speed);
    }
}

/**
 * updates screen
 **/
void screen::draw(double fps)
{	
	int camdraw=room_current->view_current;
    SDL_RenderSetScale(gb_win->ren,
        /*(float)gb_win->w/room_current->view[room_current->view_current].w,
        (float)gb_win->h/room_current->view[room_current->view_current].h*/
        room_current->port[camdraw].w/room_current->view[camdraw].w,
        room_current->port[camdraw].h/room_current->view[camdraw].h
    );
    //SDL_Rect rect={0,0,room_current->port[room_current->view_current].w,room_current->port[room_current->view_current].h};
    //SDL_RenderSetViewport(gb_win->ren,&rect);
    SDL_SetWindowSize(gb_win->win, 
                room_current->port[camdraw].w,
                room_current->port[camdraw].h);
    
    SDL_RenderPresent(gb_win->ren);
    SDL_Delay(1000.f / fps);
}

void screen::end() {
    gb_win->running=0;
}

void shutdown()
{
    for (int i = 0; i < (int)gb_objects.size(); i++) {
        object::destroy(gb_objects[i]);
    }
    for (int i = 0; i < (int)gb_sprites.size(); i++) {
        graphics::sprite::destroy(gb_sprites[i]);
    }
    for (int i = 0; i < (int)gb_sounds.size(); i++) {
        audio::destroy(gb_sounds[i]);
    }
    for (int i = 0; i < (int)gb_fonts.size(); i++) {
        font::destroy(gb_fonts[i]);
    }

    gb_objects.clear();
    gb_sounds.clear();
    gb_sprites.clear();
    gb_fonts.clear();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    __mus_handle->deinit();
}


const SDL_Color color::black = { 0, 0, 0, 255 },
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





