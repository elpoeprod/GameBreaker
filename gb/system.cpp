#include "../include/gamebreaker.hpp"
#include <algorithm>

namespace GameBreaker {
	str gb_version = "0.1a INDEV";
	system *_gbsys_;
	int debug_mode=0;
	str keyboard_string="";

	int mouse::x=0, mouse::y=0;

	GBColor draw::current_color={0xa0, 0xa0, 0xa0, 0xff};
	
	void system::init() {
		debug_message("GameBreaker starts\nversion "+gb_version+"\ninitializing system");
		_gbsys_ = this;
		debug_message("set _gbsys_->as this SUCCESS");
		SDL_Init(SDL_INIT_EVERYTHING);
		debug_message("initialized SDL2");
		TTF_Init();
		debug_message("initialized SDL2_ttf");
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
		debug_message("initialized SDL2_image");
		this->running = 1;
		this->__current_room = GB_TYPE_NONE;
		this->__current_window = GB_TYPE_NONE;
		debug_message("intialized first variables");
		// this->music_handle = new SoLoud::Soloud;
		// this->music_handle->init(
		// 	SoLoud::Soloud::ENABLE_VISUALIZATION|SoLoud::Soloud::CLIP_ROUNDOFF,
		// 	SoLoud::Soloud::AUTO,
		// 	SoLoud::Soloud::AUTO,
		// 	SoLoud::Soloud::AUTO,
		// );
	}
	
	int system::run() {
		debug_message("running system in system::run()");
		if(this->__current_window == GB_TYPE_NONE) {
			show::message("ERROR", "Did you forget to set window.current()?");
			exit(1);
		}
		if(this->__current_room == GB_TYPE_NONE) {
			show::message("ERROR" , "Did you forget to set room.current()?");
			exit(1);
		}
		debug_message("checks were passed. continuing");

		mylastkey=mykey;
		
		while(this->running) {
			while(SDL_PollEvent(&this->event)!=0) {
				switch(this->event.type) {
					case SDL_QUIT: {
						this->shutdown();
					} break;
					case SDL_KEYDOWN: {
						mykey[SDL_GetKeyName(this->event.key.keysym.sym)]=1;
						if(this->event.key.keysym.sym==SDLK_RETURN)
		            		keyboard_string+="\n";
		            	else 
		            		keyboard_string+=SDL_GetKeyName(this->event.key.keysym.sym);
					} break;
					case SDL_KEYUP: {
						mykey[SDL_GetKeyName(this->event.key.keysym.sym)]=0;
					}
					//Mouse
		            case SDL_MOUSEMOTION: 
		                mouse::x=this->event.motion.x; 
		                mouse::y=this->event.motion.y; 
		            break;
		
		            case SDL_MOUSEBUTTONDOWN: {
		                    mybut[this->event.button.button] = 1;
		            } break;
		
		            case SDL_MOUSEBUTTONUP: {
		                    mybut[this->event.button.button] = 0;
		            } break;
				}
			}
			SDL_SetRenderDrawBlendMode(this->current_win()->get_render(),SDL_BLENDMODE_BLEND);
			SDL_RenderClear(this->current_win()->get_render());
			
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
					puts(("IOBJ: "+std::to_string(iobj)+"\nIOBJINROOM: "+std::to_string(iobjinroom)).c_str());
					if(this->objects[iobj]==this->current_room()->get_instance(iobjinroom)) { //if object is in room then do the code, else continue
						if(this->objects[iobj]->event_step) 
							this->objects[iobj]->event_step(this->objects[iobj]);
							
						if(this->objects[iobj]->event_draw)
							this->objects[iobj]->event_draw(this->objects[iobj]);
					}
				}	
			}
			
			SDL_RenderPresent(this->current_win()->get_render());
			SDL_Delay(1000/16.f);
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
			if(type=="text") return this->texts[id];
			if(type=="window") return this->windows[id];
		// }
		return nullptr;
	}

	void system::shutdown() {
		debug_message("game stops running...");
		this->running=0;
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
		for(luint i = 0; i < this->windows.size(); i++) {
			windows[i]->remove();
			windows.erase(windows.begin()+i);
		}
		for(luint i = 0; i < this->fonts.size(); i++) {
			fonts[i]->remove();
			fonts.erase(fonts.begin()+i);
		}
		debug_message("Erased everything. (not your system just things that are used in game)");
	}

	window *system::current_win() {
		return this->windows[this->__current_window];
		debug_message("Got current window of the program");
	}

	void system::current_win(window *win) {
		for(luint i = 0; i < windows.size(); i++) {
			if(windows[i]==win) this->__current_window=i;
		}
		debug_message("Set current window of the program");
		return;
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

	SDL_Event system::get_event() {
		return this->event;
	}

	void system::current_room(room *rm) {
		for(luint i = 0; i < this->rooms.size(); i++) {
			if(rooms[i]==rm) this->__current_room=i;
		}
	}

	void debug_message(str msg) {
		if(debug_mode) puts(msg.c_str());
	}
	
	int system::__add(room *rm) {
		this->rooms.push_back(rm);
		return this->rooms.size()-1;
	}
	
	int system::__add(window *win) {
		this->windows.push_back(win);
		return this->windows.size()-1;
	}
	
	int system::__add(object *obj) {
		this->objects.push_back(obj);
		return this->objects.size()-1;
	}
	
	int system::__add(font *fnt) {
		this->fonts.push_back(fnt);
		return this->fonts.size()-1;
	}
	
	int system::__add(text *txt) {
		this->texts.push_back(txt);
		return this->texts.size()-1;
	}
	
	int system::__add(sprite *spr) {
		this->sprites.push_back(spr);
		return this->sprites.size()-1;
	}
	
};
