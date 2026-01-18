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

#define SUPPORT_FILEFORMAT_WAV
#define SUPPORT_FILEFORMAT_OGG
#define SUPPORT_FILEFORMAT_MP3
#define SUPPORT_FILEFORMAT_QOA
#define SUPPORT_FILEFORMAT_FLAC
#define SUPPORT_FILEFORMAT_XM
#define SUPPORT_FILEFORMAT_MOD


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

#define var auto
#define repeat(a) for (luint __gb_repeat_i_i__ = 0; __gb_repeat_i_i__ < a; __gb_repeat_i_i__++);
#define undefined '\0'

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

	struct GB_HANDLE {
		Music mus;
		Sound snd;
	};

	enum SOUND_TYPE {
		nonstream=0,
		stream,
	};

	class sound {
		private:
		real _pan, _volume;
		int _type;
		int _loops;

		public:
		void add(str fname, int type);

		void volume(real vol);
		real volume();
		
		void pan(real pan);
		real pan();
		
		void play();
		void loop(int loops);
		void stop();
		void pause();
		void resume();
		void remove();
		GB_HANDLE handle;
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
		std::vector<object *> *__get_room_objects();
		void __set_room_objects(std::vector<object *>);
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
		int bold, italic;
		public:
		int id, size;

		public:
		void add(str fname, int size, int bold, int italic);
		void remove();
		Font _getor();
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
		void set_font(font *fnt);

		private:
		static GBColor current_color;
			
	};

	class system {
		private:
		std::vector<sprite *> 	sprites;
		std::vector<object *> 	objects;
		std::vector<room *> 	rooms;
		std::vector<font *> 	fonts;
		std::vector<sound *>	sounds;
		int __current_room;
		int __current_display;
		int __current_view;
		int __current_font;
		
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

		void current_font(int id);
		int current_font(void);
		
		void init		();
		void shutdown	();
		void end		();
		int run			();
	};

	class show {public:
		static void message(str title, str msg);
		static void error(str msg, int abort);
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
		static GBColor mix(GBColor col1, GBColor col2);
		static GBColor merge(GBColor col1, GBColor col2, real amount);
		static GBColor merge_corrected(GBColor col1, GBColor col2, real amount);
		static GBColor make_hsv(real hue, real saturation, real value);
		static GBColor make_rgb(long unsigned int col);
		static real get_luminance(GBColor col);

	};

	extern str gb_version;
	extern str keyboard_string;
	extern system *_gbsys_;
	extern int debug_mode;

	typedef std::vector<void *> GB_ChooseBag;
	typedef std::vector<real> GB_NumberBag;

	extern int __gb_rand_seed;
	
	class math {
	public:
		static real 	abs				(real num);
	    static real 	lendir_x		(real len, int dir);
	    static real 	lendir_y		(real len, int dir);
	    static real 	degtorad		(real deg);
	    static real 	clamp			(real val, real minval, real maxval);
	    static real 	point_in_rect	(real px, real py, real rx1, real ry1, real rx2, real ry2);
	    static real		sin				(real x);
	    static real		cos				(real x);
	    static real 	dsin			(real x);
	    static real 	dcos			(real x);
	    static int 		round			(real x);
	    static int 		floor			(real x);
	    static int 		ceil			(real x);
		static real		round_to		(real x, real to);
		static real		floor_to		(real x, real to);
		static real		ceil_to			(real x, real to);
	    static real 	pdistance		(real x1, real y1, real x2, real y2);
	    static real 	pdirection		(real x1, real y1, real x2, real y2);
	    static real 	power			(real x, int n);
	    static real 	sqr				(real x);
	    static real 	sqrt			(real x);
	    static real 	min 			(GB_NumberBag bag);
	    static real 	max 			(GB_NumberBag bag);
	    static int 		sign			(real num);
	    static real 	frac			(real x);
	
	    static real 	median			(GB_NumberBag bag);
	    static real 	mean			(GB_NumberBag bag);
	    static real 	lerp			(real a, real b, real num);
	
	    static real 	random 			(real n);
	    static int 		irandom 		(int n);
	    static real 	random_range	(real min, real max);
	    static int 		irandom_range	(int min, int max);
	    static void 	random_set_seed	(int seed);
	    static int 		irandom_fresh	(int oldval, int minval, int maxval);
	    static int 		random_get_seed	();
	    static void 	randomize		();
		static void *	choose			(GB_ChooseBag bag);
		static real 	gauss 			(real range);
		static real		gauss_range		(real min, real max);
		static real 	modwrap			(real val, real minval, real maxval);
		static real		exp				(real x);
		static real		log				(real x);
		static real		ln				(real x);
		static real		log10			(real x);
		static real		log2			(real x);
		static real		tan				(real x);
		static real		cotan			(real x);
		static real		tg				(real x);
		static real		ctg				(real x);
	};

	class gstr {public:
	    static str	replace 		(str text, str in, str out);
	    static str	replace_all		(str text, str in, str out);
	    static str	cat				(std::vector<void *> args);
	    static int	count			(str text, str n);
	    static str	shorten			(str fname);
	    static str	lowercase		(str text);
	    static str	uppercase		(str text); 
	    static str	char_at			(str text, int pos);
	    static int	ord_at			(str text, int pos);
	    static int	length			(str text); // why not use strlen(str.c_str()) or str.length()? because no.
	    static int	pos				(str substr, str text);
	    static str	copy			(str text, int pos, int len);
	    static str	del				(str text, int pos, int len);
	    static str	insert			(str text, str substr, int pos);
	    static str	duplicate		(str text, int count);
		static str	format			(int num, int tot, int dec);
	    static str	pad 			(int num, int padding);
	    static str	file_ext		(str fname);
	};

	class ini {public:
	    static int      open		(str fname);
	    static int      read_int	(int file, str section, str keyName, int defKey);
	    static str   	read_str	(int file, str section, str keyName, str defKey);
	    static void     write_int	(int file, str section, str key, int num);
	    static void     write_str	(int file, str section, str key, str num);
	    static void     close		(int file);
	};


	struct fname_list {
	    str title;
	    str filter;
	};
	struct __gblist {
	    int type;
	    str data;
	};
	
	typedef std::vector<__gblist> ds_list;

	struct _gm_ftype {
		std::ofstream out;
		std::ifstream in;
		std::fstream a;
	};
	
	struct _gm_file {
	    _gm_ftype file;
	    int mode;
	    int line;
	    str name;
	};
	
	class fs {
	public:
	    enum fmode {
	        read	= 0,
	        write	= 1,
	        append	= 2
	    };
	    enum fa {
	        hidden		= 0x0010, // show hidden files
	        dir			= 0x0020, // show directories
	        sysfile		= 0x0040, // show system files
	        fullpath	= 0x0080, // (for fs::find::list() - adds a path to found filename)
	    };
	    enum type {
	        tfile	= DT_REG,
	        tdir	= DT_DIR
	    };
	    static int exists(str fname);
	    class find {
	    public:
	        static ds_list list 		(str directory, str filter, luint mask);
	        static ds_list list_ext	(str directory, std::vector<str> filter, luint mask);
	    };
	    class text {public:
	        static int 		open	(str fname, int mode);
	        static void 	write 	(int file, str str);
	        static str 		read 	(int file);
	        static void 	ln		(int file);
	        static int 		eof		(int file);
	        static void 	close 	(int file);
	    };
	    static str 	path_parent		(str path);
	    static str 	path			(str fname);
	    static str	fname			(str fname);
	    static str 	get_fname		(std::vector<fname_list> filter, str title);
	    static str 	get_folder		(str title);
	    static void create_folder	(str path);
	};
}

#define stringify std::to_string

namespace gb = GameBreaker;
