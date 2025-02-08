#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

namespace GameMaker {
typedef struct GMSound {
    Mix_Chunk* chunk;
    double vol;
    double pos;
    int type;
    double x, y;
    double pan;
    int channel;
} GMSound;

typedef struct GMSprite {
    int offx, offy;
    int w, h;
    int frames;
    SDL_Texture* tex;
} GMSprite;

typedef struct GMObject {
    double x, y;
} GMObject;

extern double master_vol;

typedef struct GMWin {
    std::string label;
    int x, y, w, h;
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_Event ev;
    int running;
} GMWindow;

extern int init(int x, int y, int w, int h, std::string label);
extern int running(void);
extern void update();

class joy {public:
    static int count();
    static int button_pressed(int joy, int button);
    static int button_released(int joy, int button);
    static int button_holding(int joy, int button);
};

class window {
public:
    static void size(int w, int h);
    static void pos(int x, int y);
    static int get_x();
    static int get_y();
    static int get_width();
    static int get_height();
};

class sound {
public:
    static GMSound* add(std::string fname, int type);
    static void set_pos(GMSound* snd, double pos);
    static void play(GMSound *snd);
    static void loop(GMSound *snd, int loops);
    static void pause(GMSound *snd);
    static void stop(GMSound *snd);
    static void set_vol(GMSound *snd, double vol);
    static void destroy(GMSound* snd);
};
class color {
public:
    static SDL_Color black, white, red, blue, green, lime;
};

class graphics {
public:
    class sprite {
    public:
        static GMSprite* add(std::string fname, int frames, int offx, int offy);
        static int get_offset_x(GMSprite* spr);
        static int get_offset_y(GMSprite* spr);
        static void set_offset_x(GMSprite* spr, int x);
        static void set_offset_y(GMSprite* spr, int y);
        static void destroy(GMSprite* spr);
    };
    class draw {
    public:
        static void rect(int x, int y, int w, int h, int outline);
        static int rect_color(float x, float y, float w, float h, SDL_Color col1, SDL_Color col2, SDL_Color col3, SDL_Color col4, int outline);
        static void triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color col1, SDL_Color col2, SDL_Color col3);
        static void circle(int x, int y, int r, int outline);
        static void line(int x1, int y1, int x2, int y2);
        static void point(int x, int y);
        static void color(Uint32 color);
        static void color_sdl(SDL_Color color);
        static void sprite(GMSprite* spr, int frame, int x, int y, int xscale, int yscale, int rot);
    };
    static void message(std::string title, std::string msg);
};
class screen {
public:
    static void draw(double fps);
};
class fs {
public:
    static int exists(std::string fname);
};

enum mb {
    left = SDL_BUTTON_LEFT,
    right = SDL_BUTTON_MIDDLE,
    middle = SDL_BUTTON_RIGHT
};
class mouse {
public:
    static int pressed(mb mouse_button);
    static int released(mb mouse_button);
    static int holding(mb mouse_button);
};
class math {
public:
    static double lendir_x(double len, int dir);
    static double lendir_y(double len, int dir);
    static double degtorad(double deg);
    static double clamp(double val, double minval, double maxval);
    static double point_in_rect(double px, double py, double rx1, double ry1, double rx2, double ry2);
};

}

typedef GameMaker::GMSprite GMSprite;
typedef GameMaker::GMSound GMSound;

typedef GameMaker::mb mb;
