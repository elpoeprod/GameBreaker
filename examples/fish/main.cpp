#define GB_USE_SMALL_FUNCNAMES
#include "../../include/gamebreaker.hpp"

namespace gb=GameBreaker;

GBRoom *room1;
GBObject *obj;

void fish_draw() {
	draw::color_rgb(255,255,255);
	int xx,yy,size,dx,dy,i;
	xx=320;
	yy=240;
	size=40;
	i=0;
	repeat(360) {
	    dx=xx+math::lendir_x(size,math::dsin(i)*90*2);
	    dy=yy+math::lendir_y(size,math::dcos(i)*90*3);
	    draw::circle(dx,dy,2,0);
	    dx=(xx+size*2)-math::lendir_x(size,math::dsin(i)*90);
	    dy=yy-math::lendir_y(size,math::dcos(i)*90);
	    draw::circle(dx,dy,2,0);
	    dx=xx+size*1.5;
	    dy=yy-size/2;
	    draw::circle(dx,dy,size/16,0);
	    i+=1;
	}
	int dxx,dyy;
	dx=xx+size*1.9;
	dy=yy+size/2;
	dxx=xx+size;
	dyy=yy+size/2;
	draw::line(dx,dy,dxx,dyy);
}

int main() {
	gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,640,480,"FISH.");
	room1=room::add(640,480);
	obj=object::add(nullptr,nullptr);
	obj->event_draw=fish_draw;

	room::add_instance(room1,obj,0,0,nullptr);
	room::current(room1);

	gb::run();
	gb::shutdown();
}
