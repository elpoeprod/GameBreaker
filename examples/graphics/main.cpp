#define GB_USE_SMALL_FUNCNAMES
#include "../../gb/gamebreaker.hpp"
namespace gb=GameBreaker;

int main() {
    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,640,480,"Graphics test");

    var linus=sprite::add("creator of school.jpg",0,0,0);

    while(gb::running()) {
        draw::sprite_stretched(linus,0,0,0,640,480,1,1,0);
        screen::draw(60);
    }
    gb::shutdown();
    return 0;
}