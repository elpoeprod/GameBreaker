#define GB_USE_SMALL_FUNCNAMES
#include <gamebreaker/gamebreaker.hpp>
namespace gb=GameBreaker;

GBSprite *spr;
GBObject *obj;

void obj_ev_draw() {
	int i=0; repeat(4) {
		draw::sprite(spr,i,77*i,0,1,1,0);
		i++;
	}
}

int main() {
	gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"TEST");
	spr=sprite::add_ext("elpaudio.png",4,0,0,2,2,77,70);//add("elpaudio.png",4,0,0);
	obj=object::add(nullptr,nullptr);
	var room1=room::add(640,480);
	obj->event_draw=obj_ev_draw;
	
	room::camera_setup(room1,0,1,(GB_CamSetup){0,0,640,480,0},(GB_CamSetup){0,0,640,480,0},-1,(GB_CamTarget){0,0,0,0});
	room::add_instance(room1,obj,0,0,nullptr);
	room::current(room1);

	gb::run();
	gb::shutdown();
	return 0;
}
