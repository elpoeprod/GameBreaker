#define GB_USE_SMALL_FUNCNAMES
#include "gamebreaker.hpp"

namespace gb = GameBreaker;

int main()
{
    gb::init(640, 480, 640, 480, "test");
    GBSprite* spr = sprite::add("elpaudio.png", 1, 0, 0);
    GBSound *sndMusic=sound::add("A.ogg",0);
    GBObject *obj=object::add(spr,nullptr,50,50);
    GBFont *fnt0=font::add("clacon2.ttf",14);

    gb::sound::loop(sndMusic,-1);

    ds_list temp=file::find::list(".","*.ogg;*.png;",fa::fullpath);
    gb::graphics::message("test",gb::list::get_string(temp,"\n"));
	draw::set_font(fnt0);
	draw::color_sdl(col::lime);
    GBText *text=new GBText("Hello world");
    while (gb::running()) {
        draw::color(0xFFFFFF);
        draw::rect(0, 0, 640, 480, 0);
        draw::sprite(obj->spr, 0, obj->x+math::lendir_x(60,SDL_GetTicks()), obj->y, 1 + 4 * mouse::holding(mb::left), 2, 0);
        draw::color(0x000000);
        draw::line(5, 5, 88, 99);
        draw::triangle(30,400,30,470,140,445,col::lime,col::green,col::white);
        draw::rect_color(200,200,120,80,col::black,col::black,col::green,col::blue,0);
        draw::text(50,60,text);
        for(int i=0;i<256;i++) {
            draw::line(120+i*(360/256),400+sound::get_wave(sndMusic,i),12+(i+1)*(360/256),400+sound::get_wave(sndMusic,i));
        }
        if(mouse::released(mb::left)&&mouse::x>500&&mouse::y>400) gb::graphics::message("Test","H...");

        screen::draw(60);
    }
    gb::shutdown();
}
