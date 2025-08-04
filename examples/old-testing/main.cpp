#define GB_USE_SMALL_FUNCNAMES
#include "../../include/gamebreaker.hpp"

namespace gb = GameBreaker;

GBObject *obj,*obj2,*obj3;
GBText *text;
GBRoom *myroom,*room2;

void obj_Draw() {
	draw::color(0xFFFFFF);
    draw::sprite(obj->spr, 0, obj->x+math::lendir_x(60,gb::current_time), obj->y, 1 + 4 * mouse::holding(mb::left), 2, 0);
    draw::color(0x000000);
    draw::line(5, 5, 88, 99);
    draw::triangle(30,400,30,470,140,445,col::lime,col::green,col::white);
    draw::rect_color(200,200,120,80,col::black,col::black,col::green,col::blue,0);
    draw::text(50,60,text);
    if(mouse::released(mb::left)&&mouse::x>500&&mouse::y>400) show::message("Test","H...");
   	if(keyboard::released('T')) {
   		show::message("Test","Lorem ipsum dolor sit amet");
		room::current(room2);
   	}
}

void obj2_draw() {
	draw::color_rgb(192,216,192);
	draw::rect(70,70,70+150+math::lendir_x(150,gb::current_time*0.95),70+150+math::lendir_y(150,gb::current_time),0);
}

void obj3_draw() {
	draw::color_rgb(14,88,186);
	draw::rect(70,70,70+150+math::lendir_x(75,gb::current_time*0.9),70+150+math::lendir_y(75,gb::current_time*0.95),0);
	if(keyboard::released('G')) {
		if(obj3->depth!=-15)
			obj3->depth=-15;
		else obj3->depth=100;
	}
    gb::room_current->view[0].x+=0.1;
}

int main()
{
    gb::init(640, 480, 640, 480, "test");
    var spr = sprite::add("elpaudio.png", 1, 0, 0);
    var sndMusic=audio::add("A.ogg",gb::GB_MUSIC);
    obj=object::add(spr,nullptr);
	obj->event_draw=obj_Draw;
	
    var myfont=font::add("default.ttf",12);

    obj2=object::add(nullptr,nullptr);
    obj2->event_draw=obj2_draw;
    obj2->depth=90;

    obj3=object::add(nullptr,nullptr);
    obj3->event_draw=obj3_draw;
    obj3->depth=-15;

    myroom=room::add(640,480);
    room2=room::add(1024,768);
	room::add_instance(myroom,obj,0,0,nullptr);
	room::add_instance(room2,obj2,0,0,nullptr);
	room::add_instance(room2,obj3,0,0,nullptr);
	
	room::current(myroom);
    myroom->view_current=0;
    room::camera_setup(myroom,0,1,(GB_CamSetup){0,0,640,480,0},(GB_CamSetup){0,0,640,480,0},-1,(GB_CamTarget){0,0,0,0});
    room::camera_setup(room2,0,1,(GB_CamSetup){0,0,640,480,0},(GB_CamSetup){0,0,640,480,0},-1,(GB_CamTarget){0,0,0,0});

    draw::set_font(myfont);

    audio::loop(sndMusic,-1);

    std::vector<str> tempfilter={".ogg",".png"};
    ds_list temp=file::find::list_ext(".",tempfilter,fa::fullpath);
    show::message("test",gb::list::get_string(temp,"\n"));
	draw::color_sdl(col::lime);
    text=new GBText("Hello world");
    gb::run();
    gb::shutdown();
}
