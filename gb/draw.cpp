#include "../include/gamebreaker.hpp"
#include <rlgl.h>

namespace GameBreaker {

	GBFPoint GBXyfy(float x, float y) {
		return {x-(float)_gbsys_->current_room()->view[_gbsys_->current_view()].x,
				y-(float)_gbsys_->current_room()->view[_gbsys_->current_view()].y};	
	}

	void draw::rect(GBRect rect, int outline) {
		GBFPoint pos=GBXyfy(rect.x, rect.y);
		if(outline) 
			DrawRectangleLines(pos.x, pos.y, rect.w, rect.h, current_color);
		else 
			DrawRectangle(pos.x, pos.y, rect.w, rect.h, current_color);
		return;
	}
	
	void draw::rect(GBFRect rect, GBColor col1, GBColor col2, GBColor col3, GBColor col4) {
		GBFPoint pos=GBXyfy(rect.x, rect.y);
		rlBegin(RL_TRIANGLES);
            // One triangle, three points
            // Define color for next vertex
            rlColor4ub(col1.r,col1.g,col1.b,col1.a);
            // Define vertex
            rlVertex2f(pos.x, pos.y);
            rlColor4ub(col2.r,col2.g,col2.b,col2.a);
            rlVertex2f(pos.x+rect.w, pos.y);
            rlColor4ub(col3.r,col3.g,col3.b,col3.a);
            rlVertex2f(pos.x+rect.w, pos.y+rect.h);

            rlColor4ub(col1.r,col1.g,col1.b,col1.a);
			rlVertex2f(pos.x, pos.y);
			rlColor4ub(col3.r,col3.g,col3.b,col3.a);
            rlVertex2f(pos.x+rect.w, pos.y+rect.h);
            rlColor4ub(col4.r,col4.g,col4.b,col4.a);
            rlVertex2f(pos.x, pos.y+rect.h);
        rlEnd();
        return;
	}

	void draw::line(GBPoint pos1, GBPoint pos2) {
		DrawLineV(pos1,pos2,current_color);
		return;
	}

	void draw::point(GBPoint pos) {
		DrawPoint3D({pos.x,pos.y,0},current_color);
		return;
	}


	void draw::color(GBColor col) {
		current_color=col;
		return;
	}

	GBColor draw::color() {
		return current_color;
	}


	void show::message(str title, str msg) {
		//SDL_ShowSimpleMessageBox(0,title.c_str(), msg.c_str(),_gbsys_->current_win()->get_winid());
		return;
	}
}
