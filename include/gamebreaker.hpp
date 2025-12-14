/*

	GAMEBREAKER
	rewritten edition
	class functions instead of *::*::*::*::*::*::*::*........

*/
//#pragma once //do not remove or die
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

#ifndef GB_MAX_WINDOWS
#define GB_MAX_WINDOWS 8
#endif

#ifndef GB_MAX_CAMERAS
#define GB_MAX_CAMERAS 7
#endif


// typedef double real;
typedef float real;
typedef std::string str;

typedef struct {int w, h;} GBSize;
typedef struct {int x, y;} GBPoint;
typedef struct {float x, y;} GBFPoint;
typedef struct {int x, y, w, h;} GBRect;
typedef struct {float x, y, w, h;} GBFRect;
typedef struct {Uint8 r, g, b, a;} GBColor;
typedef struct {double xscale, yscale;} GBScale;
typedef long unsigned int luint;
typedef struct {double x, y; int w, h; double angle;} GBCamera;
typedef GBRect GBVPort;

#ifndef GB_TYPE_NONE
#define GB_TYPE_NONE -1
#define GB_INSTANCE_ANY 0xfffffe
#endif
#define repeat(a) for (luint __gb_repeat_i_i__ = 0; __gb_repeat_i_i__ < a; __gb_repeat_i_i__++;);

namespace GameBreaker {

	void debug_message(str msg);

	class sprite {
		private:
		SDL_Texture *tex;
		GBSize size;
		GBPoint offset;

		public:
		int id;
		real image_index;
		real image_speed;
		int frames;
		
		void add(str fname, int frames, GBPoint offset);
		void remove();
		GBSize get_size();
		GBPoint get_offset();
		void draw(GBFPoint pos, real frame);
		void draw(GBFPoint pos, real frame, GBScale scale, real rot, GBColor col); //draw_ext
		void draw_stretched(GBFPoint pos, real frame, GBSize size);	//draw_stretched
		void draw_stretched(GBFPoint pos, real frame, GBSize size, GBScale scale, real rot, GBColor col);	//draw_stretched_ext
		void draw_part(GBFPoint pos, real frame, GBSize part);	//draw_part
		void draw_part(GBFPoint pos, real frame, GBSize part, GBScale scale, real rot, GBColor col);	//draw_part_ext
		void draw_part_stretched(GBFPoint pos, real frame, GBSize part, GBSize size);	//draw_part_stretched
		void draw_part_stretched(GBFPoint pos, real frame, GBSize part, GBSize size, GBScale scale, real rot, GBColor col);	//draw_part_stretched_ext
	};

	class object {
		public:
		real x, y, xprevious, yprevious;
		real speed, hspeed, vspeed;
		real gravity, gravity_direction, friction;
		int id;
		int sprite_index, mask_index;
		int depth;

		private:
		void default_init();
		void default_adder();

		public:
		void add(sprite *spr, sprite *mask);
		void add();
		void add(sprite *spr);
		void remove();
		object(object& other);

		void (*event_create)(object *self);
		void (*event_destroy)(object *self);
		void (*event_step_begin)(object *self);
		void (*event_step)(object *self);
		void (*event_step_end)(object *self);
		void (*event_draw)(object *self);
	};

	class tile {
		private:
		sprite spr;
		GBSize grid_size;
	};

	class room {
		private:
		struct tile_data {
			int tile_id; 
			GBPoint	pos, 
					tile_pos;
		};
		std::vector<object>		robjects;
		std::vector<tile>			rtiles;
		std::vector<tile_data>	rtiles_data;
		GBSize size;
	
		public:
		int id;
		GBColor 	background_color;
		int 		background_image[GB_MAX_CAMERAS];
		GBCamera 	view			[GB_MAX_CAMERAS];
		GBVPort		port			[GB_MAX_CAMERAS];
		
		void add			(GBSize size);
		void add_instance	(object obj, GBPoint pos);
		object get_instance(int id);
		luint instance_count(int id);
		void add_tile		(tile t, GBPoint tile_pos);
		void remove			();
		void current		();
	};
	
	class window {
		private:
		SDL_Window *win;
		SDL_Renderer *render;
		str title;
		int window_id;
		GBSize size;
		GBPoint pos;
		void default_init();

		public:
		void add(str title);
		void add(str title, GBPoint pos);
		void add();
		void remove();
		void current();
		SDL_Window *get_winid();
		SDL_Renderer *get_render();
		GBSize get_size();
		GBPoint get_pos();
		void set_size(GBSize size);
		void set_pos(GBPoint pos);

	};

	class font {
		private:
		TTF_Font *fnt;
		int size, bold, italic;
		int id;

		public:
		void add(str fname, int size, int bold, int italic);
		void remove();
	};

	class text {
		private:
			str text;
			GBColor col;
			font fnt;

		public:
			void add(str text);
			void draw(GBPoint pos);	//draw
			void draw(GBPoint pos, GBScale scale, real rot, GBColor col);	//draw_ext
	};

	GBFPoint GBXyfy(float x, float y);
	
	class draw {public:
		static void rect(GBRect rect, int outline);
		static void rect(GBFRect rect, GBColor col1, GBColor col2, GBColor col3, GBColor col4);

		static void line(GBPoint pos1, GBPoint pos2);
		static void point(GBPoint pos);
		static void point(GBPoint pos, real width);

		static void		color(GBColor col);
		static GBColor	color();

		private:
		static GBColor current_color;
			
	};

	class system {
		private:
		std::vector<sprite *> 	sprites;
		std::vector<object *> 	objects;
		std::vector<room *> 	rooms;
		std::vector<font *> 	fonts;
		std::vector<window *> 	windows;
		std::vector<text *> 	texts;
		int __current_room;
		int __current_window;
		int __current_display;
		int __current_view;
		int running;
		SoLoud::Soloud *music_handle;
		SDL_Event event;
		std::map<str, int> mykey;
		std::map<str, int> mylastkey;
		int mybut		[4];
		int mylastbut	[4];
		
		public:
		int __add	(room *rm);
		int __add	(window *win);
		int __add	(object *obj);
		int __add	(font *fnt);
		int __add	(text *txt);
		int __add	(sprite *spr);
		
		void __sys_sort_objects();
		
		void 	*__get		(int id, str type); //sprite, room, object, window, text, font
		SDL_Event get_event	();
		int chmouse			(int id, int ch1, int ch2);
		
		window *current_win	();
		void current_win	(window *win);

		room *current_room	();
		void current_room	(room *rm);

		int current_display	();
		void current_display(int disp);
		
		int current_view	();
		void current_view	(int view);
		
		void init		();
		void shutdown	();
		void end		();
		int run			();
	};

	class show {public:
		static void message(str title, str msg);
	};

	enum mb {
	    none	= -1,
	    left	= SDL_BUTTON_LEFT,
	    middle	= SDL_BUTTON_MIDDLE,
	    right	= SDL_BUTTON_RIGHT,
	    any		= 0x100
	};

	class mouse {public:
		static int x, y;

		static int pressed(mb mouse_button);
		static int holding(mb mouse_button);
		static int released(mb mouse_button);
		static int nothing(mb mouse_button);
		static mb which();
		static int wheel_up();
		static int wheel_down();
	};

	class display {public:
		static GBSize size();
		static str name();
	};

	extern str gb_version;
	extern str keyboard_string;
	extern system *_gbsys_;
	extern int debug_mode;
}

namespace gb = GameBreaker;
