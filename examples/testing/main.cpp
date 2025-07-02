#define GB_USE_SMALL_FUNCNAMES
#include "../../include/gamebreaker.hpp"
namespace gb=GameBreaker;

GBObject *obj1;
GBObject *obj2;
GBSprite *sprite0;

void my_draw1() {
    draw::color(0xFFFFFF);
    draw::sprite(sprite0,0,obj1->x,obj1->y,1,2,0);
    obj1->x+=1;
    return;
}

void my_draw2() {
    draw::sprite(sprite0,0,obj2->x,obj2->y,1,2,0);
    obj2->y+=1;
    return;
}

int main() {
    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,640,480,"Test");

    sprite0=sprite::add("elpaudio.png",1,0,0);
    obj1=object::add(sprite0,nullptr,0,0);
    obj2=object::add(sprite0,nullptr,0,0);
    obj1->event_draw=my_draw1;
    obj2->event_draw=my_draw2;
    obj1->depth=-15;
    obj2->depth=15;
    var room0=room::add(640,480);
    room::add_instance(room0,obj1, 0,0);
    room::add_instance(room0,obj2, 10,10);

    room::current(room0);

    gb::run(60);

    gb::shutdown();
    return 0;
}