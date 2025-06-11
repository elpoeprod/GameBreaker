#define GB_USE_SMALL_FUNCNAMES
#include "../../gb/gamebreaker.hpp"

namespace gb = GameBreaker;

int main()
{
    gb::init(640, 480, 640, 480, "test");
    var  spr = sprite::add("elpaudio.png", 1, 0, 0);
    var sndMusic=music::add("A.ogg",0);
    var obj=object::add(spr,nullptr,50,50);

    gb::music::loop(sndMusic,-1);

    std::vector<str> tempfilter={".ogg",".png"};
    ds_list temp=file::find::list_ext(".",tempfilter,fa::fullpath);
    show::message("test",gb::list::get_string(temp,"\n"));
	draw::color_sdl(col::lime);
    var text=new GBText("Hello world");
    while (gb::running()) {
        draw::color(0xFFFFFF);
        draw::rect(0, 0, 640, 480, 0);
        draw::sprite(obj->spr, 0, obj->x+math::lendir_x(60,gb::current_time), obj->y, 1 + 4 * mouse::holding(mb::left), 2, 0);
        draw::color(0x000000);
        draw::line(5, 5, 88, 99);
        draw::triangle(30,400,30,470,140,445,col::lime,col::green,col::white);
        draw::rect_color(200,200,120,80,col::black,col::black,col::green,col::blue,0);
        //draw::text(50,60,text);
        if(mouse::released(mb::left)&&mouse::x>500&&mouse::y>400) show::message("Test","H...");

        screen::draw(60);
    }
    gb::shutdown();
}
