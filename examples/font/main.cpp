#define GB_USE_SMALL_FUNCNAMES
#define GB_EXIT_ON_CLOSEBUTTON
#define GB_GAME_END_ON_ESC
#include "../../gb/gamebreaker.hpp"
namespace gb=GameBreaker;


int main() {

    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,320,240,"Font testing");

    GBFont *font0=font::add("sourcesans.ttf",16);

    while(gb::running()) {
        //draw::color_hsv(180+math::lendir_x(180, GameBreaker::current_time*0.5),99,99);
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

        screen::draw(60);
    }

    gb::shutdown();
    return 0;
}