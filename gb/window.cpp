#include "../include/gamebreaker.hpp"

namespace GameBreaker {

	void window::default_init() {
		this->title = "GameBreaker "+gb_version+" game";
		this->size={640,480};
		this->pos={0,0};
		this->window_id=_gbsys_->__add(this);
		return;
	}
	
	void window::add(str title, GBPoint pos) {
		debug_message("Initializing window with title \""+title+"\"");
		this->default_init();
		this->title = title;
		this->win = SDL_CreateWindow(this->title.c_str(), pos.x, pos.y, 640, 480, SDL_WINDOW_SHOWN);
		this->render = SDL_CreateRenderer(this->win, 0, SDL_RENDERER_ACCELERATED);
		this->pos=pos;
		debug_message("Created window and renderer");
		return;
	}
	
	void window::add(str title) {
		debug_message("Initializing window with title \""+title+"\"");
		this->default_init();
		this->title = title;
		this->win = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
		this->render = SDL_CreateRenderer(this->win, 0, SDL_RENDERER_ACCELERATED);
		int w=640,h=480;
		SDL_GetWindowPosition(this->win,&w,&h);
		this->pos={w,h};
		debug_message("Created window and renderer");
		return;
	}
	
	void window::add() {
		debug_message("Initializing window with title \""+title+"\"");
		this->default_init();
		this->win = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
		this->render = SDL_CreateRenderer(this->win, 0, SDL_RENDERER_ACCELERATED);
		int w=640,h=480;
		SDL_GetWindowPosition(this->win,&w,&h);
		this->pos={w,h};
		debug_message("Created window and renderer");
		return;
	}
	
	void window::remove() {
		SDL_DestroyRenderer(this->render);
		SDL_DestroyWindow(this->win);
		debug_message("Destroyed window with title \""+this->title+"\"");
		delete this;
	}

	SDL_Renderer *window::get_render() {
		return this->render;
	}
	
	SDL_Window *window::get_winid() {
		return this->win;
	}

	void window::current() {
		_gbsys_->current_win(this);
		return;
	}
}
