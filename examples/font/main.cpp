#define GB_USE_SMALL_FUNCNAMES
#include <gamebreaker/gamebreaker.hpp>
namespace gb=GameBreaker;

GBObject *objFonts;
GBFont *font0;

void mydraw() {
	//draw::color_rgb(math::irandom(255),math::irandom(255),math::irandom(255));
    draw::color_sdl(col::white);
    draw::rect(0,0,320,240,0);

    draw::color_sdl(col::black);

    draw::set_font(font0);

    font::style(font0,0,0);
    draw::text_rt(0, 2, "I am normal font being.");

    font::style(font0,0,1);
    draw::text_rt(0, 20, "I am italic.");

    font::style(font0,1,0);
    draw::text_rt(0, 48, "I am bold.");

    font::style(font0,1,1);
    draw::text_rt(0, 64, "Text is drawing in real-time. No lags! Maybe...");

    draw::text_rt(0,220,"FPS: "+stringify(gb::fps_current));
}

int main() {

    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"Font testing");

    font0=font::add("sourcesans.ttf",16);
    objFonts=object::add(nullptr,nullptr);
    objFonts->event_draw=mydraw;
	var myroom=room::add(320,240);
	room::add_instance(myroom,objFonts,0,0,nullptr);
	room::camera_setup(myroom,0,1,(GB_CamSetup){0,0,320,240,0},(GB_CamSetup){0,0,640,480,0},-1,(GB_CamTarget){0,0,0,0});
	room::current(myroom);

	gb::run();
    gb::shutdown();
    return 0;
}
