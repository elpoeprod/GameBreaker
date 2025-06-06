#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "3rdparty/sdl2_sound/SDL_sound.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#ifndef GB_INIT_WIN_FLAGS
#define GB_INIT_WIN_FLAGS SDL_RENDERER_ACCELERATED
#endif

#define repeat(a) if(a>0) for(int __rep_i=0;__rep_i<a;__rep_i++)

#define GB_WINPOS_CENTER SDL_WINDOWPOS_CENTERED

typedef struct __current {
        int second,
        minute,
        hour,
        day,
        month,
        year,
        century,
        planet,
        millenium;
    } __current;

namespace GameBreaker {
typedef std::string gb_str;
extern int current_time;
extern SDL_Color _realcol_;
//extern void *__sel_obj_;

#ifndef GB_DONT_USE_SFX
typedef struct GBSound {
    Mix_Chunk* chunk;
    double vol;
    double pos;
    int type;
    double x, y;
    double pan;
    int channel;
} GBSound;
#endif

#ifndef GB_DONT_USE_MUSIC
typedef struct GBMusic {
    Mix_Music* chunk;
    double vol;
    double pos;
    int type;
    double x, y;
    double pan;
    double len;
    std::string tag[4];
} GBMusic;
#endif

typedef struct GB_Sound {
    struct {
        Sound_Sample *sample;
        SDL_AudioSpec devformat;
        Uint8 *decoded_ptr;
        Uint32 decoded_bytes;
    } data;
    Sound_Sample *smp;
    double vol;
    double pos;
    int type; // 0 or 1
    double x,y;
    double pan;
    double len;
} GB_Sound;

typedef struct GBSprite {
    int offx, offy;
    int w, h;
    int frames;
    SDL_Texture* tex;
} GBSprite;

typedef struct GBObject {
    public:
        double x, y;
        double xprevious, yprevious;
        double direction, gravity, gravity_direction,friction;
        double spd,hspd,vspd;
        GBSprite *spr, *mask;

    private:
        int _in_path;
} GBObject;

typedef struct GBFont {
    int size;
    int bold, italic;
    TTF_Font* font;
} GBFont;

typedef struct GBWin {
    gb_str label;
    int x, y, w, h;
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_Event ev;
    int running;
} GBWindow;

struct _GBPath {
    float x,y;
};

struct GBPath {
    std::vector<_GBPath> path;
    int closed;
    int speed;

};

struct _gm_file {
    FILE *file;
    int mode;
};

extern GBWindow* gb_win;

typedef struct _curfont{GBFont *f; int bold; int italic;} _curfont;
extern _curfont curfon;

extern std::vector<GBSound*> gb_sounds;
extern std::vector<GBSprite*> gb_sprites;
extern std::vector<_gm_file *>gb_files;
extern std::vector<GBObject*> gb_objects;
extern std::vector<GBFont*> gb_fonts;
extern GBMusic *curmusic;

extern int mybut[4];
extern int mylastbut[4];

extern Uint32 fps_current;

extern std::map<std::string,int> mykey;
extern std::map<std::string,int> mylastkey;

struct GBText {
public:
    GBText(const std::string& newText)
    {
        *this = newText;
        this->txt=newText;
    }

    ~GBText()
    {
        if (this->surf != nullptr)
            SDL_FreeSurface(this->surf);
        if (this->tex != nullptr)
            SDL_DestroyTexture(this->tex);
    }

    GBText& operator=(const std::string& newText)
    {
        this->txt = newText;

        if (this->surf != nullptr)
            SDL_FreeSurface(this->surf);
        if (this->tex != nullptr)
            SDL_DestroyTexture(this->tex);

        this->surf = TTF_RenderUTF8_Blended(m_font->font, this->txt.c_str(), m_col);
        this->tex = SDL_CreateTextureFromSurface(gb_win->ren, this->surf);
        //if(this->tex==nullptr or this->surf->w==0 or this->surf->h==0) exit(0x000010);

        return *this;
    }

    SDL_Color m_col {(SDL_Color){255,255,255,255}};
    std::string txt {};
    SDL_Surface* surf { nullptr };
    SDL_Texture* tex { nullptr };
    GBFont *m_font{GameBreaker::curfon.f};
};

extern double master_vol,
    _gm_halign, _gm_valign;

extern int init(int x, int y, int w, int h, gb_str label);
extern int running(void);
extern void update();
extern void shutdown();

class font {
public:
    static GBFont* add(gb_str fname, int size);
    static void style(GBFont *font, int bold, int italic);
    static void destroy(GBFont* font);
    static void option(Uint32 style_flags);
};

class object {
public:
    static GBObject* add(GBSprite* spr, GBSprite* mask, double x, double y);
    static void destroy(GBObject* obj);
};

class io {public:
    static void clear();
};
#ifndef GB_DONT_USE_KEYB
class keyboard {public:
    static int pressed(int key);
    static int released(int key);
    static int holding(int key);
};
#endif

#ifndef GB_DONT_USE_JOY
class joy {
public:
    static int count();
    static int working();
    static int pressed(int joy, int button);
    static int released(int joy, int button);
    static int holding(int joy, int button);
    enum button {
        invalid = -1,
        cross,
        circle,
        square,
        triangle,
        select,
        guide,
        start,
        lstick,
        rstick,
        lshoulder,
        rshoulder,
        dpad_up,
        dpad_down,
        dpad_left,
        dpad_right,
        misc1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
        paddle1,  /* Xbox Elite paddle P1 (upper left, facing the back) */
        paddle2,  /* Xbox Elite paddle P3 (upper right, facing the back) */
        paddle3,  /* Xbox Elite paddle P2 (lower left, facing the back) */
        paddle4,  /* Xbox Elite paddle P4 (lower right, facing the back) */
        touchpad, /* PS4/PS5 touchpad button */
        max
    };
};
#endif

class window {
public:
    static void size(int w, int h);
    static void pos(int x, int y);
    static int get_x();
    static int get_y();
    static int get_width();
    static int get_height();
    static void set_icon(gb_str ico);
    static SDL_Point get_size();
    static SDL_Renderer* get_renderer();
};

#ifndef GB_DONT_USE_MUSIC
class music {
public:
    static GBMusic*     add(gb_str fname, int type);
    static void         set_pos(GBMusic* snd, double pos);
    static void         play(GBMusic* snd);
    static void         loop(GBMusic* snd, int loops);
    static void         pause();
    static void         resume();
    static void         stop(GBMusic* snd);
    static void         set_vol(GBMusic* snd, double vol);
    static int          get_wave(GBMusic* snd,int pos);
    static void         destroy(GBMusic* snd);
    static void         get_tags(GBMusic *snd);
    static double       get_pos(GBMusic *snd);
    static double       get_len(GBMusic *snd);
    static void         set_loops(int loops);
};
#endif

#ifndef GB_DONT_USE_SFX
class sound {
public:
    static GBSound* add(gb_str fname, int type);
    static void set_pos(GBSound* snd, double pos);
    static void play(GBSound* snd);
    static void loop(GBSound* snd, int loops);
    static void pause(GBSound* snd);
    static void stop(GBSound* snd);
    static void set_vol(GBSound* snd, double vol);
    static int get_wave(GBSound* snd,int pos);
    static void destroy(GBSound* snd);
};
#endif

class color {
public:
    static SDL_Color black, white, red, blue, green, lime,
    gray,lt_gray,dk_gray,fuchsia,purple,aqua,pink;
};

class show {public:
    static void message(gb_str title, gb_str msg);
    static void error(gb_str msg, int abort);
};

enum mb {
    none    = -1,
    left    = SDL_BUTTON_LEFT,
    right   = SDL_BUTTON_MIDDLE,
    middle  = SDL_BUTTON_RIGHT,
    any     = 0x100
};
class mouse {
public:
    static int pressed(mb mouse_button);
    static int released(mb mouse_button);
    static int holding(mb mouse_button);
    static int nothing(mb mouse_button);
    static mb which();
    static int x, y;
};

struct gb_button_state {
    int released;
    mb button;
};

class graphics {
public:
    class sprite {
    public:
        static GBSprite* add(gb_str fname, int frames, int offx, int offy);
        static int get_offset_x(GBSprite* spr);
        static int get_offset_y(GBSprite* spr);
        static void set_offset(GBSprite* spr, int x, int y);
        static void destroy(GBSprite* spr);
    };
    class draw {
    public:
        static void rect(int x, int y, int w, int h, int outline);
        static int rect_color(float x, float y, float w, float h, SDL_Color col1, SDL_Color col2, SDL_Color col3, SDL_Color col4, int outline);
        static void triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color col1, SDL_Color col2, SDL_Color col3);
        static void circle(int x, int y, int r, int outline);
        static void line(int x1, int y1, int x2, int y2);
        static void point(int x, int y);
        static void alpha(float alpha);
        static void color(Uint32 color);
        static void color_rgb(Uint8 r,Uint8 g,Uint8 b);
        static void color_sdl(SDL_Color color);
        static void color_hsv(double h, double s, double v);
        static SDL_Color color_get();
        static void blendmode(SDL_BlendMode mode);
        static void sprite(GBSprite* spr, int frame, int x, int y, int xscale, int yscale, int rot);
        static void sprite_part(GBSprite* spr, int frame, int x, int y, int w, int h, int xscale, int yscale, int rot);
        static void sprite_stretched(GBSprite* spr, int frame, int x, int y, int w, int h, int xscale, int yscale, int rot);
        static void sprite_ext(GBSprite* spr, int frame, int x, int y, int xscale, int yscale, int rot, SDL_Color col);
        static gb_button_state button(int x, int y, int w, int h, GBSprite *spr, int types);
        static void text(float x, float y, GBText* text);
        static void text_rt(float x, float y, gb_str text);
        static void set_font(GBFont *fnt);
        static void set_text_align(double halign, double valign);
    };
    
};
class screen {
public:
    static void draw(double fps);
    static void end();
};
enum type {
    real = 0,
    str = 1
};
struct __gblist {
    int type;
    gb_str data;
};

class list {
public:
    static gb_str get_string(std::vector<__gblist> list, gb_str sep);
    class find {public:
        static int pos(std::vector<__gblist> list, gb_str value);
        static gb_str value(std::vector<__gblist>,int pos);
    };
};

struct fname_list {
    gb_str title;
    gb_str filter;
};

class fs {
public:
    enum fmode {
        read=0,
        write=1,
        append=2
    };
    enum fa {
        hidden = 0x0010, // show hidden files
        dir = 0x0020, // show directories
        sysfile = 0x0040, // show system files
        fullpath = 0x0080, // (for fs::find::list() - adds a path to a founded filename)
    };
    enum type {
        tfile=DT_REG,
        tdir=DT_DIR
    };
    static int exists(gb_str fname);
    class find {
    public:
        static std::vector<__gblist> list(gb_str directory, gb_str filter, Uint32 mask);
        static std::vector<__gblist> list_ext(gb_str directory, std::vector<std::string> filter, Uint32 mask);
    };
    class text {public:
        static int open(gb_str fname,int mode);
        static void write(int file,gb_str str);
        static void close(int file);
    };
    static gb_str path_parent(gb_str path);
    static gb_str path(gb_str fname);
    static gb_str get_fname(std::vector<fname_list> filter, gb_str title);
    static gb_str get_folder(gb_str title);
};

class ini {public:
    static int      open(gb_str fname);
    static int      read_int(int file, gb_str section, gb_str keyName, int defKey);
    static gb_str   read_str(int file, gb_str section, gb_str keyName, gb_str defKey);
    static void     write_int(int file, gb_str section, gb_str key, int num);
    static void     write_str(int file, gb_str section, gb_str key, gb_str num);
    static void     close(int file);
};

class d3d {
};

class date{public:
    static __current current;
};

class gstr {public:
    static gb_str   replace(gb_str text,gb_str in, gb_str out);
    static gb_str   replace_all(gb_str text,gb_str in, gb_str out);
    static gb_str   cat(std::vector<void *>args);
    static int      count(gb_str text, gb_str n);
    static gb_str   shorten(gb_str fname);
    static gb_str   lowercase(gb_str str);
    static gb_str   uppercase(gb_str str); 
};

enum ERROR {
    SPRITE_FILE_DOESNT_EXIST=0x000100,
    SPRITE_FILE_NOT_SUPPORTED=0x000101
};

class math {
public:
    static double lendir_x(double len, int dir);
    static double lendir_y(double len, int dir);
    static double degtorad(double deg);
    static double clamp(double val, double minval, double maxval);
    static double point_in_rect(double px, double py, double rx1, double ry1, double rx2, double ry2);
    static int round(double x);
    static int floor(double x);
    static int ceil(double x);
};

class room{public:
    static int width,height;
};

struct __gbmap {
    std::string key;
    void *value;
};
}

typedef GameBreaker::GBSprite GBSprite;
typedef GameBreaker::GBSound GBSound;
typedef GameBreaker::GBMusic GBMusic;
typedef GameBreaker::GBObject GBObject;
typedef GameBreaker::GBFont GBFont;
typedef GameBreaker::GBText GBText;

typedef std::vector<GameBreaker::__gblist> ds_list;
typedef std::vector<GameBreaker::__gbmap> ds_map;
typedef GameBreaker::fs::fa fa;

typedef GameBreaker::mb mb;

typedef GameBreaker::gb_str str;
#define stringify std::to_string

#define var auto

/* functions */
#ifdef GB_USE_SMALL_FUNCNAMES
typedef GameBreaker::graphics::draw draw;
typedef GameBreaker::graphics::sprite sprite;
typedef GameBreaker::sound sound;
typedef GameBreaker::window window;
typedef GameBreaker::mouse mouse;
typedef GameBreaker::color col;
typedef GameBreaker::fs file;
typedef GameBreaker::screen screen;
typedef GameBreaker::joy joystick;
typedef GameBreaker::keyboard keyboard;
typedef GameBreaker::math math;
typedef GameBreaker::object object;
typedef GameBreaker::font font;
typedef GameBreaker::music music;
typedef GameBreaker::io io;
typedef GameBreaker::gstr gstr;
typedef std::vector<GameBreaker::fname_list> fname_list;
typedef GameBreaker::gb_button_state gb_button_state;
typedef GameBreaker::show show;

#endif
