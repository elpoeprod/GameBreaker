#include "gm.hpp"

namespace gm = GameMaker;

int main()
{
    gm::init(640, 480, 640, 480, "test");
    GMSprite* spr = gm::graphics::sprite::add("elpaudio.png", 1, 0, 0);
    GMSound *sndMusic=gm::sound::add("A.ogg",0);

    gm::sound::loop(sndMusic,-1);

    while (gm::running()) {
        gm::update();
        gm::graphics::draw::color(0xFFFFFF);
        gm::graphics::draw::rect(0, 0, 640, 480, 0);
        gm::graphics::draw::sprite(spr, 0, 80+gm::math::lendir_x(60,SDL_GetTicks()), 0, 1 + 4 * gm::mouse::holding(mb::left), 2, 0);
        gm::graphics::draw::color(0x000000);
        gm::graphics::draw::line(5, 5, 88, 99);
        gm::graphics::draw::triangle(30,400,30,470,140,445,gm::color::lime,gm::color::green,gm::color::white);
        gm::graphics::draw::rect_color(200,200,120,80,gm::color::black,gm::color::black,gm::color::green,gm::color::blue,0);
        if(gm::mouse::released(mb::left)) gm::graphics::message("Test","H...");

        gm::screen::draw(60);
    }
    gm::graphics::sprite::destroy(spr);
    gm::sound::destroy(sndMusic);
}
