#include "../include/gamebreaker.hpp"

namespace GameBreaker {

	GBFPoint GBXyfy(float x, float y) {
		return {x-(float)_gbsys_->current_room()->view[_gbsys_->current_view()].x,
				y-(float)_gbsys_->current_room()->view[_gbsys_->current_view()].y};	
	}

	void draw::rect(GBRect rect, int outline) {
		GBFPoint pos=GBXyfy(rect.x, rect.y);
		SDL_Rect myrect = {(int)pos.x, (int)pos.y, rect.w, rect.h};
		if(outline) 
			SDL_RenderDrawRect(_gbsys_->current_win()->get_render(),&myrect);
		else 
			SDL_RenderFillRect(_gbsys_->current_win()->get_render(),&myrect);
		return;
	}
	
	void draw::rect(GBFRect rect, GBColor col1, GBColor col2, GBColor col3, GBColor col4) {
		GBFPoint pos=GBXyfy(rect.x, rect.y);
		
		const std::vector<SDL_Vertex> verts = {
            {
                SDL_FPoint { pos.x, pos.y },
                SDL_Color { col1.r, col1.g, col1.b, 255 },
                SDL_FPoint { 0,0 },
            },
            {
                SDL_FPoint { pos.x + rect.w, pos.y },
                SDL_Color { col2.r, col2.g, col2.b, 255 },
                SDL_FPoint { 0,0 },
            },
            {
                SDL_FPoint { pos.x + rect.w, pos.y + rect.h },
                SDL_Color { col3.r, col3.g, col3.b, 255 },
                SDL_FPoint { 0,0 },
            },
            {
                SDL_FPoint { pos.x + rect.w, pos.y + rect.h },
                SDL_Color { col3.r, col3.g, col3.b, 255 },
                SDL_FPoint { 0,0 },
            },
            {
                SDL_FPoint { pos.x, pos.y + rect.h },
                SDL_Color { col4.r, col4.g, col4.b, 255 },
                SDL_FPoint { 0,0 },
            },
            {
                SDL_FPoint { pos.x, pos.y },
                SDL_Color { col1.r, col1.g, col1.b, 255 },
                SDL_FPoint { 0,0 },
            },
        };
        SDL_RenderGeometry(_gbsys_->current_win()->get_render(), nullptr, verts.data(), verts.size(), nullptr, 0);
        return;
	}

	void draw::line(GBPoint pos1, GBPoint pos2) {
		SDL_RenderDrawLine(_gbsys_->current_win()->get_render(), pos1.x, pos1.y, pos2.x, pos2.y);
		return;
	}

	void draw::point(GBPoint pos) {
		SDL_RenderDrawPoint(_gbsys_->current_win()->get_render(), pos.x, pos.y);
		return;
	}


	void draw::color(GBColor col) {
		current_color=col;
		SDL_SetRenderDrawColor(_gbsys_->current_win()->get_render(), col.r, col.g ,col.b, col.a);
		return;
	}

	GBColor draw::color() {
		return current_color;
	}


	void show::message(str title, str msg) {
		SDL_ShowSimpleMessageBox(0,title.c_str(), msg.c_str(),_gbsys_->current_win()->get_winid());
		return;
	}
}
