#define GB_USE_SMALL_FUNCNAMES
#include "../../include/gamebreaker.hpp"
namespace gb=GameBreaker;

GBSprite *sprLinus;
GBObject *objLinus;
GBRoom *room1;

void mydraw() {
	draw::sprite_stretched(objLinus->spr,0,0,0,640,480,1,1,0);
}

int main() {
    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,640,480,"Graphics test");

    sprLinus=sprite::add("creator of school.jpg",0,0,0);
    objLinus=object::add(sprLinus,nullptr);
    objLinus->event_draw=mydraw;

    room1=room::add(640,480);
    room::camera_setup(room1,0,1,(GB_CamSetup){0,0,640,480,0},(GB_CamSetup){0,0,640,480,0},-1,(GB_CamTarget){0,0,0,0});
    room::add_instance(room1,objLinus,0,0,nullptr);
    room::current(room1);

	gb::run();
    gb::shutdown();
    return 0;
}
