#include "../include/gamebreaker.hpp"
#include <algorithm>
#include <random>

namespace GameBreaker {
	str gb_version = "0.1a INDEV";
	system *_gbsys_;
	int debug_mode=0;
	str keyboard_string="";

	str window::title="";

	int mouse::x=0, mouse::y=0;
	int __gb_rand_seed;

	GBColor draw::current_color={0xa0, 0xa0, 0xa0, 0xff};
	
	void system::init() {
		debug_message("GameBreaker starts\nversion "+gb_version+"\ninitializing system");
		_gbsys_ = this;
		debug_message("set _gbsys_->as this SUCCESS");	
		InitWindow(640,480,"");
		InitAudioDevice();
		window::set_title("GameBreaker Game");
		debug_message("Created new window");
		this->__current_room = GB_TYPE_NONE;
		debug_message("intialized first variables");
		__gb_rand_seed=time(NULL);
		std::srand(__gb_rand_seed);
		this->__current_font=-1;
	}
	
	int system::run() {
		debug_message("running system in system::run()");
		if(this->__current_room == GB_TYPE_NONE) {
			show::message("ERROR" , "Did you forget to set room.current()?");
			exit(1);
		}
		debug_message("checks were passed. continuing");

		SetTargetFPS(this->current_room()->room_speed);
		while(!WindowShouldClose()) {

			for(luint i=0;i<this->sounds.size();i++) {
				UpdateMusicStream(this->sounds[i]->handle.mus);
			}
		
			BeginDrawing();
			BeginBlendMode(BLEND_ALPHA);
			
			GBColor mycol = draw::color();
			draw::color(this->current_room()->background_color);
			draw::rect({0,0,display::size().w,display::size().h},0);
			draw::color(mycol);

			static auto myobjs=*this->current_room()->__get_room_objects();

			std::sort(myobjs.begin(),myobjs.end(),[](object *a,object *b){return a->depth<b->depth;});

			this->current_room()->__set_room_objects(myobjs);
			
			//checks every instance in room
			for(luint iobjinroom = 0; iobjinroom < this->current_room()->instance_count(GB_INSTANCE_ANY); iobjinroom++) {
				if(this->current_room()->get_instance(iobjinroom)->event_step) 
					this->current_room()->get_instance(iobjinroom)->event_step(this->current_room()->get_instance(iobjinroom));
			
				if(this->current_room()->get_instance(iobjinroom)->event_draw) 
					this->current_room()->get_instance(iobjinroom)->event_draw(this->current_room()->get_instance(iobjinroom));
			}
			EndBlendMode();
			EndDrawing();
		}

		this->shutdown();
		
		debug_message("ending the game. goodbye!");
		return 0;
	}

	void system::__sys_sort_objects() {	 
		std::sort(objects.begin(), objects.end(), [this](object *a, object *b){return a->depth>b->depth;});
	}

	void *system::__get(int id, str type) {
		if(type=="sprite") return this->sprites[id];
		if(type=="object") return this->objects[id];
		if(type=="room") return this->fonts[id];
		return nullptr;
	}

	void system::shutdown() {
		debug_message("game stops running...");
		this->end();
		debug_message("Here i am!");
	}
	
	void system::end() {
		for(luint i = 0; i < this->sprites.size(); i++) {
			sprites[i]->remove();
			sprites.erase(sprites.begin()+i);
		}
		for(luint i = 0; i < this->objects.size(); i++) {
			objects[i]->remove();
			objects.erase(objects.begin()+i);
		}
		for(luint i = 0; i < this->rooms.size(); i++) {
			rooms[i]->remove();
			rooms.erase(rooms.begin()+i);
		}
		for(luint i = 0; i < this->fonts.size(); i++) {
			fonts[i]->remove();
			fonts.erase(fonts.begin()+i);
		}
		for(luint i = 0; i < this->sounds.size(); i++) {
			sounds[i]->remove();
			sounds.erase(sounds.begin()+i);
		}
		CloseAudioDevice();
		CloseWindow();
		debug_message("Freed resources");
	}

	room *system::current_room() {
		return this->rooms[this->__current_room];
	}

	void system::current_view(int view) {
		this->__current_view=view;
		return;
	}

	int system::current_view() {
		return this->__current_view;
	}

	void system::current_room(room *rm) {
		for(luint i = 0; i < this->rooms.size(); i++) {
			if(rooms[i]==rm) this->__current_room=i;
		}
	}

	int system::current_display() {
		return this->__current_display;
	}

	void system::current_display(int display_id) {
		this->__current_display=display_id;
		return;
	}

	void system::current_font(int id) {
		this->__current_font=id;
		return;
	}

	int system::current_font(void) {
		return this->__current_font;
	}

	void debug_message(str msg) {
		if(debug_mode) puts(("INFO: "+msg).c_str());
		return;
	}
	
	int system::__add(room *rm) {
		this->rooms.push_back(rm);
		return this->rooms.size()-1;
	}
	
	int system::__add(object *obj) {
		this->objects.push_back(obj);
		return this->objects.size()-1;
	}
	
	int system::__add(font *fnt) {
		this->fonts.push_back(fnt);
		return this->fonts.size()-1;
	}
	
	int system::__add(sprite *spr) {
		this->sprites.push_back(spr);
		return this->sprites.size()-1;
	}
	
};
