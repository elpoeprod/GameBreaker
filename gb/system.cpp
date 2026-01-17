#include "../include/gamebreaker.hpp"
#include <algorithm>

namespace GameBreaker {
	str gb_version = "0.1a INDEV";
	system *_gbsys_;
	int debug_mode=0;
	str keyboard_string="";

	str window::title="";

	int mouse::x=0, mouse::y=0;

	GBColor draw::current_color={0xa0, 0xa0, 0xa0, 0xff};
	
	void system::init() {
		debug_message("GameBreaker starts\nversion "+gb_version+"\ninitializing system");
		_gbsys_ = this;
		debug_message("set _gbsys_->as this SUCCESS");	
		InitWindow(640,480,"");
		window::set_title("GameBreaker Game");
		debug_message("Created new window");
		this->__current_room = GB_TYPE_NONE;
		debug_message("intialized first variables");
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
			BeginDrawing();
			BeginBlendMode(BLEND_ALPHA);
			
			GBColor mycol = draw::color();
			draw::color(this->current_room()->background_color);
			draw::rect({0,0,display::size().w,display::size().h},0);
			draw::color(mycol);
			
			for(luint irooms = 0; irooms < this->rooms.size(); irooms++) {
				for (luint i = 0; i < GB_MAX_CAMERAS; i++ ) {
					if(this->rooms[irooms]->background_image[i]!=GB_TYPE_NONE) {
						sprite *spr=(sprite *)this->__get(this->rooms[irooms]->background_image[i],"sprite");
						spr->draw({(float)this->rooms[irooms]->view[i].x,(float)this->rooms[irooms]->view[i].y}, spr->image_index);
					}
				}
			}

			for (luint iobj = 0; iobj < objects.size(); iobj++) { //checks every instance
				for(luint iobjinroom = 0; iobjinroom < this->current_room()->instance_count(GB_INSTANCE_ANY); iobjinroom++) { //checks every instance in room
					if(this->objects[iobj]==this->current_room()->get_instance(iobjinroom)) { //if object is in room then do the code, else continue
						if(this->objects[iobj]->event_step) 
							this->objects[iobj]->event_step(this->objects[iobj]);
							
						if(this->objects[iobj]->event_draw)
							this->objects[iobj]->event_draw(this->objects[iobj]);
					}
				}	
			}

			EndDrawing();
		}
		
		debug_message("ending the game. goodbye!");
		return 0;
	}

	void system::__sys_sort_objects() {	 
		std::sort(objects.begin(), objects.end(), [this](object *a, object *b){return a->depth>b->depth;});
	}

	void *system::__get(int id, str type) {
		// switch(type) {
			if(type=="sprite") return this->sprites[id];
			if(type=="object") return this->objects[id];
			if(type=="room") return this->fonts[id];
			if(type=="window") return this->windows[id];
		// }
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
		CloseWindow();
		debug_message("Erased everything. (not your system just things that are used in game)");
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
