#include "../include/gamebreaker.hpp"

gb::object myobj;
gb::object myobj2;
gb::system sys;
gb::window *win;
gb::room *room0;
gb::sprite *spr0;

void myobj_event_draw(gb::object *self) {
	gb::draw::color({255,0,255,255});
	gb::draw::rect({30,30,60,60},gb::draw::color(),gb::draw::color(),gb::draw::color(),gb::draw::color());
	if(gb::mouse::pressed(gb::mb::any)) {
		self->depth=-self->depth;
		myobj2->depth=-myobj2->depth;
	}
	gb::show::message("DEBUG","I'm on depth "+std::to_string(self->depth)+"!");
	return;
}

void myobj2_event_draw(gb::object *self) {
	//spr0->draw({(float)self->x, (float)self->y+10}, 0);
	gb::draw::color({255,255,255,255});
	gb::draw::rect({0,0,60,60},0);
	gb::show::message("DEBUG","I'm on depth "+std::to_string(self->depth)+"!");
	return;
}

int main(void) {
	// myobj=	new gb::object;
	// myobj2=	new gb::object;
	room0=	new gb::room;
	win=	new gb::window;
	spr0=	new gb::sprite;
	
	gb::debug_mode=1;
	
	sys.init();
	win->add("mytestgame.exe.666");
	win->current();
	
	spr0->add("c.png",1,{0,0});
	myobj.add(spr0);
	myobj2.add(spr0);
	room0->add({640,480});
	
	room0->current();
	room0->add_instance(myobj);
	room0->add_instance(myobj2);
	
	myobj->depth=-10;
	myobj2->depth=10;
	
	myobj->event_draw=myobj_event_draw;
	myobj2->event_draw=myobj2_event_draw;
	return sys.run();
}
