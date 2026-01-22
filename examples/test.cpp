#include "../include/gamebreaker.hpp"

using namespace gb;

object myobj;
object myobj2;
gb::system sys;
room *room0;
sprite *spr0;
sound *snd0;

void myobj_event_draw(object *self) {
	draw::color({255,0,255,255});
	draw::rect({30,30,60,60},0);
	if(mouse::pressed(mb::any)) {
		self->depth=-self->depth;
		myobj2.depth=-myobj2.depth;
	}
	self->x+=(keyboard::holding(vk_right)-keyboard::holding(vk_left))*3;
	//debug_message("I'm on depth "+std::to_string(self->depth)+"! 1");
	return;
}

void myobj2_event_draw(object *self) {
	//spr0->draw({(float)self->x, (float)self->y+10}, 0);
	draw::color({255,255,255,255});
	draw::rect({0,0,60,60},0);
	spr0->draw({50,50},1);
	//debug_message("I'm on depth "+std::to_string(self->depth)+"! 2");
	return;
}

int main(void) {
	// myobj=	new object;
	// myobj2=	new object;
	room0=	new room;
	spr0=	new sprite;
	snd0=	new sound;
	
	//debug_mode=1;
	
	sys.init();

	snd0->add("d.mp3",SOUND_TYPE::stream);
	snd0->play();
	
	spr0->add("c.png",1,{0,0});
	myobj.add(spr0);
	myobj2.add(spr0);
	room0->add({640,480});
	
	room0->current();
	instance::create(&myobj,{0,0});
	instance::create(&myobj2,{10,10});
	
	myobj.depth=10;
	myobj2.depth=-10;
	
	myobj.event_draw=myobj_event_draw;
	myobj2.event_draw=myobj2_event_draw;
	return sys.run();
}
