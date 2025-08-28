#define GB_USE_SMALL_FUNCNAMES
#include <gamebreaker/gamebreaker.hpp>
namespace gb=GameBreaker;

GBSound *mymus;

GBObject *myobj;

void mystep(GBObject *self) {
	if(keyboard::pressed(vk::f1)) audio::loop(mymus,-1);
	if(keyboard::pressed(vk::f2)) audio::set_pos(mymus,audio::get_len(mymus)/2);
	if(keyboard::pressed(vk::f3)) audio::stop(mymus);
	if(keyboard::pressed(vk::f4)) screen::end();
}

int main() {
	gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"Music test");

	mymus=audio::add("examples/music_sounds/crawling.mp3",gb::GB_MUSIC);
	myobj=object::add(nullptr,nullptr);
	myobj->event_step=mystep;

	var room0=room::add(640,480);
	room::add_instance(room0,myobj,0,0,nullptr);
	//room::camera_setup(room0,0,1,(GB_CamSetup){0,0,640,480,0},(GB_CamSetup){0,0,640,480,0},-1,(GB_CamTarget){0,0,0,0});
	room::current(room0);

	gb::run();
	gb::shutdown();
	
	return 0;
}
