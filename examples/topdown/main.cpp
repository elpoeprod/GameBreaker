#include "main.hpp"
#include "player.hpp"

GBObject *objPlayer;
GBObject *objEffector;
GBSprite *sprCursor;
GBRoom *rmTest;

int main() {
    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"Hotline Miami 4: GameBreaker Wanker");

	init_objects();
    var font1=font::add("sourcesans.ttf",14);
    draw::set_font(font1);
    //objPlayer=object::add(nullptr,nullptr);
    objPlayer->event_create=scrPlayer_eventCreate;
    objPlayer->event_step=scrPlayer_eventStep;
    objPlayer->event_draw=scrPlayer_eventDraw;

    sprCursor=sprite::add("sprites/sprCursor.png",13,6,6);

    //var sndHotline=audio::add("Hotline.ogg",gb::GB_MUSIC);
    //audio::loop(sndHotline,-1);

    rmTest=room::add(640,480);
    //ArmTest->speed=2;
    room::camera_setup(rmTest,0,1,(GB_CamSetup){0,0,480,256,0},(GB_CamSetup){0,0,1440,768,0},-1,(GB_CamTarget){0,0,0,0});
    room::add_instance(rmTest,objPlayer,320,240,nullptr);

    room::current(rmTest);

    gb::run();
    gb::shutdown();
    return 0;

}
