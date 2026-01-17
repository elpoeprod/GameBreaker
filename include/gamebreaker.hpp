/*

	GAMEBREAKER
	rewritten edition
	class functions instead of *::*::*::*::*::*::*::*........

*/
//#pragma once //do not remove or die
#include <raylib.h>
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
typedef Vector2 GBPoint;
typedef Vector3 GBPoint3D;
typedef struct {float x, y;} GBFPoint;
typedef struct {int x, y, w, h;} GBRect;
typedef struct {float x, y, w, h;} GBFRect;
typedef Color GBColor;//struct {unsigned char r, g, b, a;} GBColor;
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
		Texture2D tex;
		GBSize size;
		GBPoint offset;

		public:
		int id;
		real image_index;
		real image_speed;
		int frames;
		
		int add(str fname, int frames, GBPoint offset);
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
		//object(object& other);

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
		std::vector<object *>		robjects;
		std::vector<tile *>			rtiles;
		std::vector<tile_data *>	rtiles_data;
		GBSize size;
	
		public:
		int room_speed;
		int id;
		GBColor 	background_color;
		int 		background_image[GB_MAX_CAMERAS];
		GBCamera 	view			[GB_MAX_CAMERAS];
		GBVPort		port			[GB_MAX_CAMERAS];
		
		void add			(GBSize size);
		void add_instance	(object *obj, GBPoint pos);
		object *get_instance(int id);
		luint instance_count(int id);
		void add_tile		(tile t, GBPoint tile_pos);
		void remove			();
		void current		();
	};
	
	class window {
		static str title;
		public:
		static GBSize get_size();
		static GBPoint get_pos();
		static void set_size(GBSize size);
		static void set_pos(GBPoint pos);
		static void set_title(str title);
		static str get_title(void);

	};

	class font {
		private:
		Font fnt;
		int size, bold, italic;
		int id;

		public:
		void add(str fname, int size, int bold, int italic);
		void remove();
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

		static void text(GBPoint pos, str text);	//draw
		static void text(GBPoint pos, str text, GBScale scale, real rot, GBColor col);	//draw_ext
		void set_font(Font font);

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
		int __current_room;
		int __current_display;
		int __current_view;
		
		public:
		int __add	(room *rm);
		int __add	(object *obj);
		int __add	(font *fnt);
		int __add	(sprite *spr);
		
		void __sys_sort_objects();
		
		void 	*__get		(int id, str type); //sprite, room, object, window, text, font
		int chmouse			(int id, int ch1, int ch2);

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
	    left	= MOUSE_BUTTON_LEFT,
	    middle	= MOUSE_BUTTON_MIDDLE,
	    right	= MOUSE_BUTTON_RIGHT,
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

	extern GBColor c_aqua, c_black, c_blue, c_dkgray, c_fuchsia, c_gray,
					c_green, c_lime, c_ltgray, c_maroon, c_navy, c_olive, c_purple,
					c_red, c_silver, c_teal, c_white, c_yellow, c_orange;

	class color {public:
		static real get_hue(GBColor col);
		static real get_saturation(GBColor col);
		static real get_value(GBColor col);
		static GBColor merge(GBColor col1, GBColor col2, real amount);
		static GBColor merge_corrected(GBColor col1, GBColor col2, real amount);
		static GBColor make_hsv(real hue, real saturation, real value);

	};

	extern str gb_version;
	extern str keyboard_string;
	extern system *_gbsys_;
	extern int debug_mode;
}

namespace gb = GameBreaker;
