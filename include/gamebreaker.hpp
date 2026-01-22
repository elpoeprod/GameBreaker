/*

	GAMEBREAKER
	class functions instead of *::*::*::*::*::*::*::*........ (somewhere)

*/
//#pragma once //do not remove or die

#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

#ifndef GB_MAX_CAMERAS
#define GB_MAX_CAMERAS 7
#endif

#include <raylib.h>
#include <rlgl.h>


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
typedef struct {float xscale, yscale;} GBScale;
typedef long unsigned int luint;
//typedef struct {double x, y; int w, h; double angle;} GBCamera;
typedef Camera GBCamera;
typedef GBRect GBVPort;

#ifndef GB_TYPE_NONE
#define GB_TYPE_NONE -1
#define GB_INSTANCE_ANY 0xfffffe
#endif

#define var auto
#define repeat(a) for (luint __gb_repeat_i_i__ = 0; __gb_repeat_i_i__ < a; __gb_repeat_i_i__++);
#define undefined '\0'
#define stringify std::to_string
#define realify std::real

namespace GameBreaker {

	// Debug message printer
	void debug_message(str msg);

	// Sprite class for image handling
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
		
		// Creates new sprite and returns id
		int add(str fname, int frames, GBPoint offset);

		// Removes sprite from the game
		void remove();

		// Returns size of the sprite
		GBSize get_size();

		// Returns offset position of the sprite
		GBPoint get_offset();

		// Draws sprite at `pos` with `frame` frame
		void draw(GBFPoint pos, int frame);

		// Draws sprite at `pos` with `frame` frame, upscaled to `scale`, rotated to `rot` degrees and colored `col`
		void draw(GBFPoint pos, int frame, GBScale scale, real rot, GBColor col); //draw_ext

		// Draws stretched sprite at `pos` with `frame` frame, stretched to `size`
		void draw_stretched(GBFPoint pos, int frame, GBSize size);	//draw_stretched

		// Draws stretched sprite at `pos` with `frame`, stretched to `size`, upscaled to `scale`, rotated to `rot` and colored `col`
		void draw_stretched(GBFPoint pos, int frame, GBSize size, GBScale scale, real rot, GBColor col);	//draw_stretched_ext

		// Draws `part` of the sprite at `pos` with `frame` frame
		void draw_part(GBFPoint pos, int frame, GBRect part);	//draw_part

		// Draws `part` of the sprite at `pos` with `frame` frame, upscaled to `scale`, rotated to `rot` and colored `col`
		void draw_part(GBFPoint pos, int frame, GBRect part, GBScale scale, real rot, GBColor col);	//draw_part_ext

		// Draws stretched `part` of the sprite at `pos` with `frame` frame, stretched to `size`
		void draw_part_stretched(GBFPoint pos, int frame, GBRect part, GBSize size);	//draw_part_stretched

		// Draws stretched `part` of the sprite at `pos` with `frame` frame, stretched to `size`, upscaled to `scale`, rotated to `rot` and colored `col`
		void draw_part_stretched(GBFPoint pos, int frame, GBRect part, GBSize size, GBScale scale, real rot, GBColor col);	//draw_part_stretched_ext
	};

	// Object class for handling positions etc
	class object {
		public:

		// position of object
		real x, y;

		// previous position of object
		real xprevious, yprevious;
		real speed, hspeed, vspeed;
		real gravity, gravity_direction, friction;
		int id;
		int sprite_index, mask_index;
		int depth;
		int solid;

		private:
		void default_init();
		void default_adder();

		public:
		
		// Creates new object with `spr` as sprite and `mask` as mask
		void add(sprite *spr, sprite *mask);

		// Creates new object with nothing as sprite and mask
		void add();

		// Creates new object with `spr` as sprite and mask
		void add(sprite *spr);

		// Removes object from the game
		void remove();


		// Create event
		void (*event_create)(object *self);

		// Destroy event
		void (*event_destroy)(object *self);

		// Begin Step event
		void (*event_step_begin)(object *self);

		// Step event
		void (*event_step)(object *self);

		// End Step event
		void (*event_step_end)(object *self);

		// Draw event
		void (*event_draw)(object *self);
	};

	struct GB_HANDLE {
		Music mus;
		Sound snd;
	};

	// Sound type for loading
	enum SOUND_TYPE {
		nonstream=0, 	// sound
		stream, 		// music
	};

	// Sound class for handling sound/music playing
	class sound {
		private:
		real _pan, _volume;
		int _type;
		int _loops;

		public:

		// ID of sound
		int id;

		// Creates new sound
		void add(str fname, int type);

		// Sets volume of a sound
		void volume(real vol);

		// Returns sound's volume
		real volume();
		

		// Sets panning of sound
		void pan(real pan);

		// Returns sound's panning
		real pan();
		
		// Plays sound once, music will automatically play looped
		void play();

		// Sets sound looping to `looped`
		void loop(int looped);

		// Stops sound
		void stop();

		// Pauses sound playing
		void pause();

		// Resumes sound playing
		void resume();

		// Removes soud from the game
		void remove();

		// Sound handle
		GB_HANDLE handle;
	};

	// Tile (WIP)
	class tile {
		private:
		sprite spr;
		GBSize grid_size;
	};

	// Room class for making GUIs, main game stages etc.
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
		int room_speed;									// Room speed (FPS)
		int id;											// ID of the room
		GBColor 	background_color;					// Background color
		int 		background_image[GB_MAX_CAMERAS];	// Background image for each camera
		GBCamera 	view			[GB_MAX_CAMERAS];	// Camera
		GBVPort		port			[GB_MAX_CAMERAS];	// Viewport for each camera
		

		// Creates new room
		void add			(GBSize size);

		// For debug purposes		
		std::vector<object *> *__get_room_objects();
		void __set_room_objects(std::vector<object *>);
		void __add(object *obj);
		
		// WIP
		void add_tile		(tile t, GBPoint tile_pos);

		// Removes room from the game
		void remove			();

		// Sets current room to this room
		void current		();
	};

	// Instance handling functions
	class instance {public:

		// Creates an instance at current room and returns InstanceID
		static luint 	create(object *obj, GBPoint pos);

		// Returns object with `inst_id`
		static object*	get(int inst_id);

		// Returns count of objects with `id` id
		static luint 	count(int id);

		// Removes instance, object or everything from the room
		static void		destroy(int id);

		// Removes every instance that are on `pos` coordinates
		static void		pos_destroy(GBPoint pos);

		// Checks if instance or object exist in the room
		static int		exists(int id);
		
		// Returns nearest inst_id of object
		static int		nearest(GBPoint pos, int obj_id);

		// Returns furthest inst_id of object
		static int		furthest(GBPoint pos, int obj_id);
	};

	// Place collision functions
	class place {public:
		
		// Checks if place is COMPLETELY empty at `pos` coordinates
		static int empty(GBPoint pos);

		// Checks if object with `obj_id` id is on coordinates
		static int meeting(GBPoint pos, int obj_id);

		// Checks if place is empty from solid objects
		static int free(GBPoint pos);
	};
	
	// Window manipulation functions
	class window {
		static str __title;
		public:

		// Sets position of a window
		static void 	pos(GBPoint pos);

		// Returns position of window
		static GBPoint 	pos();

		// Sets size of a window
		static void 	size(GBSize size);

		// Returns size of a window
		static GBSize 	size();

		// Sets window title
		static void 	title(str title);

		// Returns window title
		static str 		title(void);

	};

	// Font class for handling text drawing
	class font {
		private:
		Font fnt;
		int bold, italic;
		public:
		int id, size;

		public:
		
		// Creates new font from `fname` with `size` and `bold` and `italic` checkmarks
		void add(str fname, int size, int bold, int italic);

		// Removes font from the game
		void remove();

		// For debug purposes
		Font _getor();
	};

	// For debug purposes
	GBFPoint GBXyfy(float x, float y);
	
	// Drawing sprites, shapes, text etc
	class draw {public:

		// Draws a rectangle, if `outline`==1, the rectangle will be drawn outlined
		static void rect(GBRect rect, int outline);

		// Draws a rectangle colored from `col1` to `col4`
		static void rect(GBFRect rect, GBColor col1, GBColor col2, GBColor col3, GBColor col4);


		// Draws a line from `pos1` to `pos2`
		static void line(GBPoint pos1, GBPoint pos2);

		// Draws a point at `pos`
		static void point(GBPoint pos);

		// Draws a point at `pos` with `width` size
		static void point(GBPoint pos, real width);


		// Sets drawing color with `col`
		static void		color(GBColor col);

		// Returns drawing color
		static GBColor	color();


		// Draws `text` at `pos`
		static void text(GBPoint pos, str text);	//draw

		// Draws `text` at `pos`, upscaled to `scale`, rotated to `rot` and colored `col`
		static void text(GBPoint pos, str text, GBScale scale, real rot, GBColor col);	//draw_ext

		// Sets current drawing font
		void set_font(font *fnt);

		private:
		static GBColor current_color;
			
	};

	// System class for handling everything in game
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
		Shader *__current_shader;
		
		public:

		// For debug purposes
		int __add	(room *rm);
		int __add	(object *obj);
		int __add	(font *fnt);
		int __add	(sprite *spr);
		int __add	(sound *snd);
		void 	*__get		(int id, str type); //sprite, room, object, window, text, font

		// Returns current room
		room *current_room	();

		// Sets current room to `rm`
		void current_room	(room *rm);

		// Returns current display
		int current_display	();

		// Sets current display to `disp`
		void current_display(int disp);
		
		// Returns current view
		int current_view	();

		// Sets current view to `view`
		void current_view	(int view);

		// Sets current font (for debug purposes)
		void current_font(int id);

		// Returns current font ID
		int current_font(void);	

		// Sets current shader
		void current_shader(Shader *shader);

		// Returns current shader
		Shader *current_shader();		

		int fps_current; // Current FPS
		int fps_delta; // Delta FPS

		// Sleep for `sec` seconds
		void sleep(real sec);
		
		// Init the system
		void init		();

		// Shutdown everything (do not use)
		void shutdown	();

		// End the game (do not use)
		void end		();

		// Run game
		int run			();
	};

	// Date manipulation functions and structs
	class date {public:
		struct _cur {
			int planet,
				millenium,
				century,
				year,
				month,
				week,
				day,
				hour,
				minute,
				second;
			str weekday;
		} _cur;

		public:
		// Current day parameters
		static struct _cur current;
			
	};

	// WIP
	class show {public:

		// Shows message box with title `title` and message `msg`
		static void message(str title, str msg);

		// Shows message box with title `ERROR` and message `msg`. If abort==1, game will end after messagebox will be closed.
		static void error(str msg, int abort);
	};

	// Mouse buttons for mouse functions
	enum mb {
	    none	= -1,
	    left	= MOUSE_BUTTON_LEFT,
	    middle	= MOUSE_BUTTON_MIDDLE,
	    right	= MOUSE_BUTTON_RIGHT,
	    any		= 0x100
	};

	// Mouse handling functions
	class mouse {public:

		// Mouse position
		static int x, y;


		// Checks if `mouse_button` was pressed
		static int pressed(mb mouse_button);

		// Checks if `mouse_button` is down
		static int holding(mb mouse_button);

		// Checks if `mouse_button` was released
		static int released(mb mouse_button);

		// Checks if `mouse_button` does nothing
		static int nothing(mb mouse_button);

		// Returns which mouse button is pressed right now
		static mb which();

		// Checks if wheel was scrolled up
		static int wheel_up();

		// Checks if wheel was scrolled down
		static int wheel_down();
	};

	//sorry for that mess c++ thinks that vk::left can conflict with mb::left
	extern int vk_nokey,
		vk_anykey,
		vk_enter,
		vk_ret,
		vk_shift,
		vk_control,
		vk_alt,
		vk_escape,
		vk_space,
		vk_backspace,
		vk_tab,
		vk_pause,
		vk_printscreen,
		vk_left,
		vk_right,
		vk_up,
		vk_down,
		vk_home,
		vk_end,
		vk_pageup,
		vk_pagedown,
		vk_del,
		vk_ins,
		vk_f1,
		vk_f2,
		vk_f3,
		vk_f4,
		vk_f5,
		vk_f6,
		vk_f7,
		vk_f8,
		vk_f9,
		vk_f10,
		vk_f11,
		vk_f12,
		vk_numpad0,
		vk_numpad1,
		vk_numpad2,
		vk_numpad3,
		vk_numpad4,
		vk_numpad5,
		vk_numpad6,
		vk_numpad7,
		vk_numpad8,
		vk_numpad9,
		vk_divide,
		vk_multiply,
		vk_subtract,
		vk_add,
		vk_decimal,
		vk_lshift,
		vk_rshift,
		vk_lalt,
		vk_ralt,
		vk_lcontrol,
		vk_rcontrol;

	// Keyboard functions
	class keyboard {public:

		// Checks if `key` was pressed 
		static int pressed(int key);

		// Checks if `key` is down
		static int holding(int key);

		// Checks if `key` was released
		static int released(int key);
	};

	// Joystick buttons (sorry for the mess again)
	extern int joy_cross, 	// X
		joy_triangle,		// D
		joy_circle,			// O
		joy_square,			// P
		joy_select,			// Select
		joy_dpad_up,		// Dpad UP
		joy_dpad_down,		// Dpad DOWN
		joy_dpad_left,		// Dpad LEFT
		joy_dpad_right,		// Dpad RIGHT
		joy_rbumper,		// Right bumper
		joy_lbumper,		// Left bumper
		joy_ltrigger,		// Left trigger
		joy_rtrigger,		// Right trigger
		joy_middle,			// PS
		joy_start,			// Start
		joy_lthumb,			// Left thumb
		joy_rthumb,			// Right thumb
		joy_unknown,		// Unknown button
		joy_axis_lx,		// Left X axis
		joy_axis_ly,		// Left Y axis
		joy_axis_rx,		// Right X axis
		joy_axis_ry,		// Right Y axis
		joy_axis_ltrigger,	// Left trigger
		joy_axis_rtrigger;	// Right trigger

	// Joystick functions
	class joystick {public:

		// Returns 1 if joystick with id `id` exists
		static int 	exists(int id);

		// Checks if joystick `id` has button `button` pressed
		static int 	pressed(int id, int button);

		// Checks if joystick `id` has button `button` down
		static int 	holding(int id, int button);

		// Checks if joystick `id` button `button` was released
		static int 	released(int id, int button);

		// Returns joystick's `id` name
		static str 	name(int id);

		// Returns axes count of joystick `id`
		static int 	axes(int id);

		// Returns a value of `axis` of joystick `id`
		static real axis_pos(int id, int axis);
	};

	// Display functions (WIP)
	class display {public:

		// Returns the size of display
		static GBSize size();

		// Returns name of display
		static str name();
	};

	// Colors
	extern GBColor c_aqua, c_black, c_blue, c_dkgray, c_fuchsia, c_gray,
					c_green, c_lime, c_ltgray, c_maroon, c_navy, c_olive, c_purple,
					c_red, c_silver, c_teal, c_white, c_yellow, c_orange;

	// Color manipulation functions
	class color {public:

		// Returns HUE value from `col`
		static real get_hue(GBColor col);

		// Returns SAT value from `col`
		static real get_saturation(GBColor col);

		// Returns VAL value from `col`
		static real get_value(GBColor col);

		// Returns mixed color from `col1` and `col2`
		static GBColor mix(GBColor col1, GBColor col2);

		// Returns merged color of `col1` and `col2` of `amount`
		static GBColor merge(GBColor col1, GBColor col2, real amount);

		// Returns color, merged by another type of merging
		static GBColor merge_corrected(GBColor col1, GBColor col2, real amount);

		// Returns color, created from HSV
		static GBColor make_hsv(real hue, real saturation, real value);

		// Returns color, created from HEX value
		static GBColor make_rgb(long unsigned int col);

		// Returns luminance of `col`
		static real get_luminance(GBColor col);

	};

	extern str gb_version; 			// GameBreaker version
	extern str keyboard_string; 	// Keyboard string
	extern system *_gbsys_;			// System variable (your_sys->add())
	extern int debug_mode;			// Turn debug mode ON (1) or OFF (0)

	// For math::choose() function
	typedef std::vector<void *> GB_ChooseBag;

	// Number bag for needed functions
	typedef std::vector<real> 	GB_NumberBag;

	//Random seed
	extern int __gb_rand_seed;
	
	// Math functions
	class math {
	public:

		// Returns absolute of a `num`
		static real 	abs				(real num);

		// Returns cos(`dir`)*`len`
	    static real 	lendir_x		(real len, int dir);

		// Returns -sin(`dir`)*`len`
	    static real 	lendir_y		(real len, int dir);

		// Returns radian from `deg`
	    static real 	degtorad		(real deg);

		// Returns clamped `val` from `minval` to `maxval`
	    static real 	clamp			(real val, real minval, real maxval);

		// Returns 1 if `pos` placed at `rect` coordinates
	    static real 	point_in_rect	(GBPoint pos, GBRect rect);

		// Returns sinus of radian `x`
	    static real		sin				(real x);

		// Returns cosinus of radian `x`
	    static real		cos				(real x);

		// Returns sinus of degree `x`
	    static real 	dsin			(real x);

		// Returns cosinus of degree `x`
	    static real 	dcos			(real x);

		// Returns tangent of radian `x`
	    static real		tan				(real x);

		// Returns cotangent of radian `x`
   		static real		cotan			(real x);

		// Same as math::tan(x)
   		static real		tg				(real x);

		// Same as math::cotan(x)
   		static real		ctg				(real x);

		// Returns inversed sinus of radian `x`
   		static real		arcsin			(real x);

		// Returns inversed cosinus of radian `x`
   		static real		arccos			(real x);

		// Returns inversed tangent of radian `x`
   		static real		arctan			(real x);

		// Returns inversed tangent of radian `y/x`
   		static real		arctan2			(real y, real x);
	    

		// Returns rounded value of `x` (5.5==6, 5.4==0)
	    static int 		round			(real x);

		// Returns floored value of `x` (5.87182==5)
	    static int 		floor			(real x);

		// Returns ceiled value of `x` (5.000001==6)
	    static int 		ceil			(real x);

		// Returns rounded `x` to `to`
		static real		round_to		(real x, real to);

		// Returns floored `x` to `to`
		static real		floor_to		(real x, real to);

		// Returns ceiled `x` to `to`
		static real		ceil_to			(real x, real to);

		// Returns distance from `v1` to `v2`
	    static real 	pdistance		(GBPoint v1, GBPoint v2);

		// Returns 3D distance from `v1` to `v2`
	    static real 	pdistance_3d	(GBPoint3D v1, GBPoint3D v2);

		// Returns direction from `v1` to `v2`
	    static real 	pdirection		(GBPoint v1, GBPoint v2);

		// Returns power of `x` by `n` (x^n)
	    static real 	power			(real x, int n);

		// Returns square of `x` (x^2)
	    static real 	sqr				(real x);

		// Returns square root of `x`
	    static real 	sqrt			(real x);

		// Returns the minimal number from `bag`
	    static real 	min 			(GB_NumberBag bag);

		// Returns the maximum number from `bag`
	    static real 	max 			(GB_NumberBag bag);

		// Returns `-1` if `num`<0, `1` if `num`>0 and `0` if `num`==0
	    static int 		sign			(real num);

		// Returns decimal of `x`
	    static real 	frac			(real x);
	

		// Returns middle value from `bag`
	    static real 	median			(GB_NumberBag bag);

		// Returns mean value from `bag` ((bag[0]+...+bag[n])/bag.size()))
	    static real 	mean			(GB_NumberBag bag);

		// Returns lerp of `a` and `b`
	    static real 	lerp			(real a, real b, real num);
	

		// Returns random number from 0 to `n`
	    static real 	random 			(real n);

		// Returns integer'ed random number from 0 to `n`
	    static int 		irandom 		(int n);

		// Returns random number from `min` to `max`
	    static real 	random_range	(real min, real max);

		// Returns integer'ed random number from `min` to `max`
	    static int 		irandom_range	(int min, int max);

		// Sets seed of random functions
	    static void 	random_set_seed	(int seed);

		// Returns any random value from `minval` to `maxval` that aren't `oldval`
	    static int 		irandom_fresh	(int oldval, int minval, int maxval);

		// Returns seed of random functions
	    static int 		random_get_seed	();

		// Randomizes random numbers to not get exact same
	    static void 	randomize		();

		// Chooses anything from `bag`
		static void *	choose			(GB_ChooseBag bag);

		// Returns gauss value at `range`
		static real 	gauss 			(real range);

		// Returns gauss value from `min` to `max`
		static real		gauss_range		(real min, real max);

		// Wraps `val` from `minval` to `maxval`
		static real 	modwrap			(real val, real minval, real maxval);

		// Returns expotential^`x`
		static real		exp				(real x);

		// Returns log of `x`
		static real		log				(real x);

		// Returns log of `n` by `x`
		static real		logn			(real n, real x);

		// Returns log of expotential by `x`
		static real		ln				(real x);

		// Returns log of 10 by `x`
		static real		log10			(real x);

		// Returns log of 2 by `x`
		static real		log2			(real x);


		// Returns dot product at 2D space of `v1` and `v2`
		static real		dot_product		(GBPoint v1, GBPoint v2);

		// Returns dot product at 3D space of `v1` and `v2`
		static real		dot_product_3d	(GBPoint3D v1, GBPoint3D v2);
	};

	// String manipulation functions
	class gstr {public:
		// Replaces `in` to `out` once in `text`
	    static str	replace 		(str text, str in, str out);

		// Replaces all `in` to `out` in `text`
	    static str	replace_all		(str text, str in, str out);

		// Concatenate anything to text
	    static str	cat				(std::vector<void *> args);

		// How many `n` in a `text`
	    static int	count			(str text, str n);

		// Shorten filename from `asdasdasd.png` to `asdasd~1.png`
	    static str	shorten			(str fname);

		// lowercase a `text`
	    static str	lowercase		(str text);

		// UPPERCASE A `TEXT`
	    static str	uppercase		(str text); 

		// Get chr at `pos` of `text`
	    static str	char_at			(str text, int pos);

		// Get ord at `pos` of `text`
	    static int	ord_at			(str text, int pos);

		// Get length of a `text`
	    static int	length			(str text); // why not use strlen(str.c_str()) or str.length()? because no.

		// Get position of `substr` at `text` 
	    static int	pos				(str substr, str text);

		// Returns copied string of `text` from `pos` to `len` char
	    static str	copy			(str text, int pos, int len);

		// Returns copied string of `text` without text from `pos` to `len` char
	    static str	del				(str text, int pos, int len);

		// Inserts `substr` to `str` at `pos`
	    static str	insert			(str text, str substr, int pos);

		// Returns `text` duplicated `count` times
	    static str	duplicate		(str text, int count);

		// Formats a number to have total `tot` length and total `dec` decimal length
		static str	format			(int num, int tot, int dec);

		// Adds "0" to left side of `num` `padding` times
	    static str	pad 			(int num, int padding);

		// Returns file extension of `fname`
	    static str	file_ext		(str fname);

		// Returns chr of val (32 - SPACE)
		static str	chr				(int val);

		// Returns ord of some char (SPACE - 32)
		static int	ord				(str chr);
	    
	};

	// Clipboard handling functions
	class clipboard {public:
		// 0 if clipboard doesn't have any text
		static int	has_text		();

		// Set clipboard text
		static void	set_text		(str text);

		// Get text from clipboard
		static str	get_text		();
	};

	// Ini manipulation functions
	class ini {public:
		// Open INI file for both reading and writing
	    static int      open		(str fname);

		// Read integer from INI
	    static int      read_int	(int file, str section, str keyName, int defKey);

		// Read string from INI
	    static str   	read_str	(int file, str section, str keyName, str defKey);

		// Write integer to INI
	    static void     write_int	(int file, str section, str key, int num);

		// Write a string for INI
	    static void     write_str	(int file, str section, str key, str num);

		// Close INI file
	    static void     close		(int file);
	};

	// Struct for file variables
	struct fname_list {
	    str title;
	    str filter;
	};

	// ds_list
	struct __gblist {
	    int type;
	    str data;
	};
	
	// ds_list
	typedef std::vector<__gblist> ds_list;

	// file type
	struct _gm_ftype {
		std::ofstream out;
		std::ifstream in;
		std::fstream a;
	};
	
	// file for file functions
	struct _gm_file {
	    _gm_ftype file;
	    int mode;
	    int line;
	    str name;
	};
	
	// Filesystem functions
	class fs {
	public:
		// File open mode
	    enum fmode {
	        read	= 0,
	        write	= 1,
	        append	= 2
	    };

		// Filter
	    enum fa {
	        hidden		= 0x0010, // show hidden files
	        dir			= 0x0020, // show directories
	        sysfile		= 0x0040, // show system files
	        fullpath	= 0x0080, // (for fs::find::list() - adds a path to found filename)
	    };

		// File type (file or directory)
	    enum type {
	        tfile	= DT_REG,
	        tdir	= DT_DIR
	    };

		// Check if file exists
	    static int exists(str fname);

		// find files in directory with filters and masks
	    class find {
	    public:
	        static ds_list list 		(str directory, str filter, luint mask);
	        static ds_list list_ext	(str directory, std::vector<str> filter, luint mask);
	    };

		// text files manipulation
	    class text {public:
	        static int 		open	(str fname, int mode);
	        static void 	write 	(int file, str str);
	        static str 		read 	(int file);
	        static void 	ln		(int file);
	        static int 		eof		(int file);
	        static void 	close 	(int file);
	    };

		// Get parent path from string
	    static str 	path_parent		(str path);

		// Get path without filename
	    static str 	path			(str fname);

		// Get filename without path
	    static str	fname			(str fname);

		// Get filename from a dialog
	    static str 	get_fname		(std::vector<fname_list> filter, str title);

		// Get folder name from a dialog
	    static str 	get_folder		(str title);

		// Create folder if it doesn't exist
	    static void create_folder	(str path);
	};

	typedef struct GBRect3D {
		real x,y,z,w,h,l;
	} GBRect3D;

	enum pr {
		pointlist=0,
		linelist,
		linestrip,
		trianglelist,
		trianglestrip,
		trianglefan
	};

	// 3D functions
	class d3d {public:
		// Starts 3D render
		static void start();

		// Ends 3D render
		static void end();

		// Sets camera's ortho projection
		static void projection_ortho(GBRect rect, real angle);

	
		// Draws 3D block
		static void draw_block(GBRect3D rect, sprite *spr, int hrepeat, int vrepeat);

		// Draws 3D floor
		static void draw_floor(GBRect3D rect, sprite *spr, int hrepeat, int vrepeat);

		// Draws 3D wall
		static void draw_wall(GBRect3D rect, sprite *spr, int hrepeat, int vrepeat);

		// starts to draw polygons
		static void primitive_begin(int type);

		// Draws vertex
		static void vertex(GBPoint3D pos);

		// Draws colored vertex
		static void vertex_color(GBPoint3D pos, GBColor col);

		// Ends drawing polygons
		static void primitive_end();

		// // Draws a fog
		// static void set_fog(int enable, real start, real end, GBColor col);

		// // Creates light
		// static int light_create(int light_type, GBColor col, GBPoint3D pos, GBPoint3D target_pos);

		// // Sets light's position
		// static void light_set_pos(int light, GBPoint3D pos, GBPoint3D target_pos);

		// // Enable or disable the light
		// static void light_enable(int light, int enable);
	};

	class buffer {public:
		static str base64_encode(str input);
		static str base64_decode(str input);
	};
}

// namespace rlights {

// 	extern int lightsCount;

// 	#define         MAX_LIGHTS            4         // Max lights supported by shader
// 	#define         LIGHT_DISTANCE        3.5f      // Light distance from world center
// 	#define         LIGHT_HEIGHT          1.0f      // Light height position

// 	//----------------------------------------------------------------------------------
// 	// Types and Structures Definition
// 	//----------------------------------------------------------------------------------
// 	typedef enum {
// 		LIGHT_DIRECTIONAL,
// 		LIGHT_POINT
// 	} LightType;

// 	typedef struct {
// 		bool enabled;
// 		LightType type;
// 		Vector3 position;
// 		Vector3 target;
// 		Color color;
// 		int enabledLoc;
// 		int typeLoc;
// 		int posLoc;
// 		int targetLoc;
// 		int colorLoc;
// 	} Light;

// 	Light CreateLight(int type, Vector3 pos, Vector3 targ, Color color, Shader shader);
// 	void UpdateLightValues(Shader shader, Light light);    
// }

namespace gb = GameBreaker;