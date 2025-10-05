#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SoLoud/soloud.h"
#include "SoLoud/soloud_wav.h"
#include "SoLoud/soloud_wavstream.h"
#include "SoLoud/soloud_openmpt.h"
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

//#ifndef _GB_HPP_
//#define _GB_HPP_

#ifndef GB_INIT_REN_FLAGS
#define GB_INIT_REN_FLAGS SDL_RENDERER_ACCELERATED
#endif

#ifndef GB_INIT_WIN_FLAGS
#define GB_INIT_WIN_FLAGS SDL_WINDOW_SHOWN
#endif

#ifndef GB_MAX_OBJ_ALARMS
#define GB_MAX_OBJ_ALARMS 12
#endif

#ifndef GB_MAX_ROOM_CAMERAS 
#define GB_MAX_ROOM_CAMERAS 8

#ifndef GB_DEFAULT_SAMPLESIZE
#define GB_DEFAULT_SAMPLESIZE 1024
#endif

#endif

#define repeat(a) if(a>0) for(int __rep_i=0;__rep_i<(int)a;__rep_i++)

#define GB_WINPOS_CENTER SDL_WINDOWPOS_CENTERED
#define DMSG(a) if(GameBreaker::debug_mode==1) puts(a);

extern void _gb_find_controllers();

extern SDL_Texture *__gb_empty_1x1__;

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
        std::string weekday;
    } __current;

typedef std::string gb_str;
typedef double real;

namespace GameBreaker {

extern int debug_mode;

extern int current_time;
extern SDL_Color _realcol_;

extern int myjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
extern int mylastjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
extern int gb_working_joystick;

extern std::vector<SDL_GameController*> controllers;
extern int joy_count;

extern SoLoud::Soloud *__mus_handle;

#ifndef GB_DONT_USE_SFX
enum GBAudioType {
    GB_2D=0,
    GB_3D,
    GB_MUSIC
};

typedef struct _GB_AudioType_{
    SoLoud::Wav nonstream;
    SoLoud::WavStream stream;
    SoLoud::Openmpt mod;
} _GB_AudioType_;

typedef struct GBAudio {
    _GB_AudioType_ chunk;
    double vol;
    double pos;
    int type;
    double x,y,z;
    double pan;
    int handle;
    double len;
    int loops;
    std::string fname;
    std::map<gb_str,gb_str> tag;
} GBAudio;
#endif

typedef struct GBSprite {
    int offx, offy;
    int w, h;
    int frames;
    SDL_Texture* tex;
    int _selx,_sely,_selw,_selh;
} GBSprite;

typedef struct GBObject {
    public:
        double x, y;
        double xprevious, yprevious;
        double direction, gravity, gravity_direction,friction;
        double spd,hspd,vspd;
        GBSprite *spr, *mask;
        int depth;
        int id;
        double image_index;
        double image_speed;
        int inst_id;
        int alarm[GB_MAX_OBJ_ALARMS];
    
    void (*event_create)					(GBObject *self);
    void (*event_step_begin)				(GBObject *self);
    void (*event_step)						(GBObject *self);
    void (*event_step_end)					(GBObject *self);
    void (*event_destroy)					(GBObject *self);
    void (*event_draw)						(GBObject *self);
    int (*event_alarm[GB_MAX_OBJ_ALARMS])	(GBObject *self);

	int initialized;
} GBObject;

typedef struct GBFont {
    int size;
    int bold, italic;
    TTF_Font* font;
} GBFont;

typedef struct GBWin {
    gb_str label;
    int x, y, w, h;
    //std::vector<SDL_Window*> win;
    //std::vector<SDL_Renderer*> ren;
    SDL_Window *win;
    SDL_Renderer *ren;
    int cur_win;
    SDL_Event ev;
    int running;
} GBWindow;

typedef struct GBSurface {
	int w,h;
	SDL_Texture *surf; //very strange, but it's the only way...
} GBSurface;

extern std::vector<GBSurface *>gb_surfs;

typedef struct GBTile {
	GBSprite *spr;
	int w,h;
	int x,y;
	int depth;
} GBTile;


struct rmtile {
	int tile_id;
	int instance_id;
	GBTile *tile;
};

struct rmobj {
    int obj_id;
    int instance_id;
    GBObject *object;
    double x,y;
    void (*event_create)();
} ;

typedef struct GB_CamSetup {
    double x,y;
    int w,h;
    double angle;
} GB_CamSetup;

typedef struct GB_CamTarget {
    int hspeed,vspeed;
    int borderw,borderh;
} GB_CamTarget;

typedef struct GBRoom {
    std::vector<rmobj>objects;
    std::vector<rmtile>tiles;
    int id;
    int width,height;
    int background_visible;
    int speed;
    SDL_Color background_color;
    GBSprite *background_image;
    int view_enabled[GB_MAX_ROOM_CAMERAS];
    int view_current;
    int target_id;
    GB_CamTarget target_setup;
    GB_CamSetup view[GB_MAX_ROOM_CAMERAS];
    GB_CamSetup port[GB_MAX_ROOM_CAMERAS];	// GameBreaker ignores `angle` variable in portview when rendering, so angle works
                            				// only in camview.
} GBRoom; 

extern std::vector<GBRoom *> gb_rooms;

struct _GBPath {
    float x,y;
};

struct GBPath {
    std::vector<_GBPath> path;
    int closed;
    int speed;

};

struct _gm_ftype {
	std::ofstream out;
	std::ifstream in;
	std::fstream a;
};

struct _gm_file {
    _gm_ftype file;
    int mode;
    int line;
    gb_str name;
};

extern GBWindow* gb_win;

typedef struct _curfont{GBFont *f; int bold; int italic;} _curfont;
extern _curfont curfon;
extern GBFont *_fntDefault__;

extern std::vector<GBAudio*> gb_sounds;
extern std::vector<GBSprite*> gb_sprites;
extern std::vector<_gm_file *>gb_files;
extern std::vector<GBObject*> gb_objects;
extern std::vector<GBFont*> gb_fonts;
extern GBAudio *curmusic;

extern gb_str const gb_version;

extern std::string keyboard_string;

extern int mybut[4];
extern int mylastbut[4];
extern int mywheel;

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

extern GBRoom *room_current;

extern int 	init 	(int x, int y, gb_str label);
extern void run 	();
extern void update 	();
extern void shutdown();

class font {
public:
    static GBFont* 	add 		(gb_str fname, int size);
    static void 	style 		(GBFont *font, int bold, int italic);
    static void 	style_ext 	(GBFont *font, int style); // use TTF_STYLE_* 
    static void 	destroy		(GBFont* font);
    static void 	option		(Uint32 style_flags);
};

class object {
public:
    static GBObject* 	add 		(GBSprite* spr, GBSprite* mask);
    static void 		add_event	(GBObject *obj, int ev_type, void(*event)(GBObject *self));
    static void 		destroy		(GBObject* obj);
};

class io {public:
    static void clear();
};
#ifndef GB_DONT_USE_KEYB
class keyboard {public:
    static int 		pressed		(int key);
    static int 		released	(int key);
    static int 		holding		(int key);
    static int 		ord			(char *key);
    static char*	chr			(int ch);
    //static int get_numlock();
};
#endif

#ifndef GB_DONT_USE_JOY
class joy {
public:
    static int count	();
    static int working	();
    static int pressed	(int joy, int button);
    static int released	(int joy, int button);
    static int holding	(int joy, int button);
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
    static void 			set_size 		(int w, int h);
    static void 			set_pos 		(int x, int y);
    static int 				get_x 			();
    static int 				get_y 			();
    static int 				get_width 		();
    static int				get_height 		();
    static void 			set_icon 		(gb_str ico);
    static SDL_Point	 	get_size 		();
    static SDL_Point	 	get_pos 		();
    static SDL_Renderer* 	get_renderer	();
    static void 			set_title 		(gb_str title);
    static void 			set_priority	(int num);
    static int 				get_ontop		();
    static void 			set_ontop		(int enable);
    static void				show_borders	(int enable);
    static void				grab 			(int enable);
    static void				minimize		(int mini);
};

extern int display_current;
class display {public:
    static int 			get_width	();
    static int 			get_height	();
    static SDL_Point 	get_size	();
    static int 			mouse_x;
    static int 			mouse_y;
};

#ifndef GB_DONT_USE_SFX
class audio {
public:
    static GBAudio*     add 		(gb_str fname, int type);
    static void         set_pos 	(GBAudio* snd, float pos);
    static void         play 		(GBAudio* snd);
    static void         loop 		(GBAudio* snd, int loops);
    static void         pause 		(GBAudio *snd);
    static void         resume 		(GBAudio *snd);
    static void         stop 		(GBAudio* snd);
    static void         set_vol 	(GBAudio* snd, double vol);
    static double		get_vol 	(GBAudio* snd);
    static float        get_wave 	(GBAudio* snd, int pos);
    static float        get_fft 	(GBAudio* snd, int pos);
    static void         destroy 	(GBAudio* snd);
    static void         get_tags 	(GBAudio *snd);
    static double       get_pos 	(GBAudio *snd);
    static double       get_len 	(GBAudio *snd);
    static void         set_loops 	(GBAudio *snd, int loops);
};
#endif

class color {
public:
    static const SDL_Color black, white, red, blue, green, lime,
    gray,lt_gray,dk_gray,fuchsia,purple,aqua,pink;
    static SDL_Color 	merge 			(SDL_Color col1, SDL_Color col2, double amount);
    static SDL_Color 	mix 			(SDL_Color col1, SDL_Color col2);
    static double 		get_luminance	(SDL_Color col);
    static SDL_Color 	merge_corrected	(SDL_Color col1, SDL_Color col2, double amount);
};
/*
typedef struct GBPOMItem {
	gb_str title;
	int id;
	void (*func)();
} GBPOMItem;

typedef std::vector<GBPOMItem> GBPOMItems;
*/

class show {public:
    static void message(gb_str title, gb_str msg);
    static void error(gb_str msg, int abort);
    static int popover_menu(gb_str file);
};

enum mb {//public:
    //static const int 
    none	= -1,
    left	= SDL_BUTTON_LEFT,
    middle	= SDL_BUTTON_MIDDLE,
    right	= SDL_BUTTON_RIGHT,
    any		= 0x100 //;
};

class vk {public:
    static const int 
        shift=		SDLK_LSHIFT,
        space=		SDLK_SPACE,
        left=		SDLK_LEFT,
        right=		SDLK_RIGHT,
        up=			SDLK_UP,
        down=		SDLK_DOWN,
        enter=		SDLK_RETURN,
        backspace=	SDLK_BACKSPACE,
        escape=		SDLK_ESCAPE,
        tab=		SDLK_TAB,
        pause=		SDLK_PAUSE,
        printscreen=SDLK_PRINTSCREEN,
        home=		SDLK_HOME,
        end=		SDLK_END,
        del=		SDLK_DELETE,
        insert=		SDLK_INSERT,
        pageup=		SDLK_PAGEUP,
        pagedown=	SDLK_PAGEDOWN,
        f1=			SDLK_F1,
        f2=			SDLK_F2,
        f3=			SDLK_F3,
        f4=			SDLK_F4,
        f5=			SDLK_F5,
        f6=			SDLK_F6,
        f7=			SDLK_F7,
        f8=			SDLK_F8,
        f9=			SDLK_F9,
        f10=		SDLK_F10,
        f11=		SDLK_F11,
        f12=		SDLK_F12,
        divide=		SDLK_KP_DIVIDE,
        multiply=	SDLK_KP_MULTIPLY,
        subtract=	SDLK_KP_MINUS,
        add=		SDLK_KP_PLUS,
        decimal=	SDLK_KP_DECIMAL,
        lshift=		SDLK_LSHIFT,
        rshift=		SDLK_RSHIFT
        ;
};

class mouse {
public:
    static int 	pressed		(mb mouse_button);
    static int 	released	(mb mouse_button);
    static int 	holding		(mb mouse_button);
    static int 	nothing		(mb mouse_button);
    static mb 	which		();
    static int 	wheel_up	();
    static int 	wheel_down	();
    static int 	x, y;
};

struct gb_button_state {
    int released;
    mb button;
};

class graphics {
public:
    class sprite {
    public:
        static GBSprite* 	add 		(gb_str fname, int frames, int offx, int offy);
        static GBSprite* 	add_ext 	(gb_str fname, int frames, int offx, int offy, int grabx, int graby, int grabw, int grabh);
        static void 		replace 	(GBSprite *spr, gb_str fname, int frames, int offx, int offy);
        static void 		replace_ext	(GBSprite *spr, gb_str fname, int frames, int offx, int offy, int grabx, int graby, int grabw, int grabh);
        static int 			get_offset_x(GBSprite* spr);
        static int 			get_offset_y(GBSprite* spr);
        static void 		set_offset	(GBSprite* spr, int x, int y);
        static void 		destroy		(GBSprite* spr);
    };
    class draw {
    public:
        static void 			rect 				(int x, int y, int w, int h, int outline); 																					// draws rectangle
        static int 				rect_color			(float x, float y, float w, float h, SDL_Color col1, SDL_Color col2, SDL_Color col3, SDL_Color col4, int outline);	// draws colored rectangle
        static void 			triangle			(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color col1, SDL_Color col2, SDL_Color col3);			// draws colored triangle
        static void 			circle				(int x, int y, int r, int outline);																						// draws circle
        static void 			line				(float x1, float y1, float x2, float y2);																					// draws line
        static void 			point				(int x, int y);																											// draws point
        static void 			alpha				(float alpha);
        static void 			color 				(Uint32 color);
        static void 			color_rgb 			(Uint8 r,Uint8 g,Uint8 b);
        static void 			color_sdl 			(SDL_Color color);
        static void 			color_hsv 			(double h, double s, double v);
        static SDL_Color	 	color_get 			();
        static void 			blendmode 			(SDL_BlendMode mode);
        static void 			sprite 				(GBSprite* spr, int frame, int x, int y, float xscale, float yscale, float rot);
        static void 			sprite_part 		(GBSprite* spr, int frame, int x, int y, int w, int h, float xscale, float yscale, float rot);
        static void 			sprite_stretched 	(GBSprite* spr, int frame, int x, int y, int w, int h, float xscale, float yscale, float rot);
        static void 			sprite_ext 			(GBSprite* spr, int frame, int x, int y, float xscale, float yscale, float rot, SDL_Color col);
        static gb_button_state 	button 				(int x, int y, int w, int h, GBSprite *spr, int types);
        static void 			text 				(float x, float y, GBText* text);
        static void 			text_transformed	(float x, float y, GBText* text, float xscale, float yscale, float rot);
        static int	 			text_rt 			(float x, float y, gb_str text);
        static GBText 		   *text_get_from_db 	(int num);
        static void 			set_font 			(GBFont *fnt);
        static void 			set_text_align 		(double halign, double valign);
        static void 			surface 			(GBSurface *surf, int x, int y, float scale, float yscale, float rot, SDL_Color col);
    };
    
};
class screen {
public:
    static void draw(double fps);
    static void end();
};
struct __gblist {
    int type;
    gb_str data;
};

class list {
public:
    static gb_str get_string(std::vector<__gblist> list, gb_str sep);
    class find {public:
        static int 		pos		(std::vector<__gblist> list, gb_str value);
        static gb_str 	value	(std::vector<__gblist>,int pos);
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
        fullpath = 0x0080, // (for fs::find::list() - adds a path to found filename)
    };
    enum type {
        tfile=DT_REG,
        tdir=DT_DIR
    };
    static int exists(gb_str fname);
    class find {
    public:
        static std::vector<__gblist> list 		(gb_str directory, gb_str filter, Uint32 mask);
        static std::vector<__gblist> list_ext	(gb_str directory, std::vector<std::string> filter, Uint32 mask);
    };
    class text {public:
        static int 		open	(gb_str fname,int mode);
        static void 	write 	(int file,gb_str str);
        static gb_str 	read 	(int file);
        static void 	ln		(int file);
        static int 		eof		(int file);
        static void 	close 	(int file);
    };
    static gb_str 	path_parent		(gb_str path);
    static gb_str 	path			(gb_str fname);
    static gb_str	fname			(gb_str fname);
    static gb_str 	get_fname		(std::vector<fname_list> filter, gb_str title);
    static gb_str 	get_folder		(gb_str title);
    static void 	create_folder	(gb_str path);
};

class ini {public:
    static int      open		(gb_str fname);
    static int      read_int	(int file, gb_str section, gb_str keyName, int defKey);
    static gb_str   read_str	(int file, gb_str section, gb_str keyName, gb_str defKey);
    static void     write_int	(int file, gb_str section, gb_str key, int num);
    static void     write_str	(int file, gb_str section, gb_str key, gb_str num);
    static void     close		(int file);
};

class d3d {
};

class date{public:
    static __current current;
};

class gstr {public:
    static gb_str   replace 		(gb_str text,gb_str in, gb_str out);
    static gb_str   replace_all		(gb_str text,gb_str in, gb_str out);
    static gb_str   cat				(std::vector<void *>args);
    static int      count			(gb_str text, gb_str n);
    static gb_str   shorten			(gb_str fname);
    static gb_str   lowercase		(gb_str str);
    static gb_str   uppercase		(gb_str str); 
    static gb_str	char_at			(gb_str str, int pos);
    static int		ord_at			(gb_str str, int pos);
    static int      length			(gb_str str); // why not use strlen(str.c_str()) or str.length()? because no.
    static int      pos				(gb_str substr, gb_str str);
    static gb_str   copy			(gb_str str, int pos, int len);
    static gb_str   del				(gb_str str, int pos, int len);
    static gb_str   insert			(gb_str str, gb_str substr, int pos);
    static gb_str   duplicate		(gb_str str, int count);
	static gb_str	format			(int num, int tot, int dec);
    static gb_str	pad 			(int num, int padding);
    static gb_str	file_ext		(gb_str fname);
};

enum ERROR {
    SPRITE_FILE_DOESNT_EXIST=0x000100,
    SPRITE_FILE_NOT_SUPPORTED=0x000101
};

extern int __gb_rand_seed;
typedef std::vector<void *> GB_ChooseBag;
typedef std::vector<real> GB_NumberBag;

class math {
public:
	static double 	abs				(double num);
    static double 	lendir_x		(double len, int dir);
    static double 	lendir_y		(double len, int dir);
    static double 	degtorad		(double deg);
    static double 	clamp			(double val, double minval, double maxval);
    static double 	point_in_rect	(double px, double py, double rx1, double ry1, double rx2, double ry2);
    static double 	dsin			(double x);
    static double 	dcos			(double x);
    static int 		round			(double x);
    static int 		floor			(double x);
    static int 		ceil			(double x);
    static double 	pdistance		(double x1, double y1, double x2, double y2);
    static double 	pdirection		(double x1, double y1, double x2, double y2);
    static double 	power			(double x, int n);
    static double 	sqr				(double x);
    static double 	sqrt			(double x);
    static double 	min 			(GB_NumberBag bag);
    static double 	max 			(GB_NumberBag bag);
    static int 		sign			(double num);
    static double 	frac			(double x);

    static double 	median			(GB_NumberBag bag);
    static double 	mean			(GB_NumberBag bag);
    static double 	lerp			(double a, double b, double num);

    static double 	random 			(double n);
    static int 		irandom 		(int n);
    static double 	random_range	(double min, double max);
    static int 		irandom_range	(int min, int max);
    static void 	random_set_seed	(int seed);
    static int 		irandom_fresh	(int oldval, int minval, int maxval);
    static int 		random_get_seed	();
    static void 	randomize		();
	static void *	choose			(GB_ChooseBag bag);
	static double 	gauss 			(double range);
	static double	gauss_range		(double min, double max);
	static double 	modwrap			(double val, double minval, double maxval);

    class motion {public:
        static void add(GBObject *obj, real dir, real speed);
        static void set(GBObject *obj, real dir, real speed);
    };
};

class room{public:
    static int width,height;
    static GBRoom *add(int w, int h);
    static int add_instance(GBRoom *room, GBObject *obj, double x, double y, void (*event_create)());
    static void remove_instances(GBRoom *room, GBObject *obj);
    static void remove_instance(GBRoom *room, int instance_id);
    static void current(GBRoom *room);
    static GBObject *find_object(int inst_id);
    static void camera_setup(GBRoom *room, int camera_id, int enabled, GB_CamSetup view, GB_CamSetup port, int target_inst_id, GB_CamTarget target);
};

struct __gbmap {
    std::string key;
    void *value;
};

enum class ev {
	create=0,
	step,
	step_begin,
	step_end,
	draw,
	destroy,
};

extern int __gb_uses_surface;

class surface{public:
	static GBSurface *add(int w, int h);
	static void target_set(GBSurface *surf);
	static void target_reset();
	static void clone(GBSurface *src, GBSurface *dst, int x, int y);
};

}

#define undefined "\0"

extern double view_xview[GB_MAX_ROOM_CAMERAS],view_yview[GB_MAX_ROOM_CAMERAS],view_angle[GB_MAX_ROOM_CAMERAS];
extern int view_wview[GB_MAX_ROOM_CAMERAS],view_hview[GB_MAX_ROOM_CAMERAS];

typedef GameBreaker::GBSprite GBSprite;
typedef GameBreaker::GBAudio GBSound;
typedef GameBreaker::GBSurface GBSurface;
typedef GameBreaker::GBObject GBObject;
typedef GameBreaker::GBFont GBFont;
typedef GameBreaker::GBText GBText;
typedef GameBreaker::GBRoom GBRoom;
typedef GameBreaker::GB_CamSetup GB_CamSetup;
typedef GameBreaker::GB_CamTarget GB_CamTarget;
//#define ord(a) GameBreaker::keyboard::ord(a) 
//#define chr(a) GameBreaker::keyboard::chr(a) 

typedef gb_str str; //for compatibility

typedef std::vector<GameBreaker::__gblist> 		ds_list;
typedef std::vector<GameBreaker::__gbmap> 		ds_map;
typedef GameBreaker::fs::fa 					fa;
typedef GameBreaker::vk 						vk;
typedef GameBreaker::gb_button_state 			gb_button_state;

typedef GameBreaker::mb mb;

#define stringify std::to_string

#define var auto

/* functions */
#ifdef GB_USE_SMALL_FUNCNAMES
typedef GameBreaker::graphics::draw 			draw;
typedef GameBreaker::graphics::sprite 			sprite;
typedef GameBreaker::audio 						audio;
typedef GameBreaker::window 					window;
typedef GameBreaker::display 					display;
typedef GameBreaker::mouse 						mouse;
typedef GameBreaker::color 						col;
typedef GameBreaker::fs 						file;
typedef GameBreaker::fs::text 					text;
typedef GameBreaker::screen 					screen;
typedef GameBreaker::joy 						joystick;
typedef GameBreaker::keyboard 					keyboard;
typedef GameBreaker::math 						math;
typedef GameBreaker::object 					object;
typedef GameBreaker::font 						font;
typedef GameBreaker::io 						io;
typedef GameBreaker::gstr 						gstr;
typedef std::vector<GameBreaker::fname_list> 	fname_list;
typedef GameBreaker::show 						show;
typedef GameBreaker::room 						room;
typedef GameBreaker::ini 						ini;
typedef GameBreaker::surface					surface;
typedef GameBreaker::math::motion				motion;
#endif	// GB_USE_SMALL_FUNCNAMES

//#endif // _GB_HPP_
