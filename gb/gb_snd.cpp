#include "3rdparty/sdl2_sound/SDL_sound.h"
#include "gamebreaker.hpp"

namespace GameBreaker {
    class snd {
        static GB_Sound* add(gb_str fname, int type) {
            var snd=new GB_Sound;
            snd->type=type;
            Sound_AudioInfo sndaudinf;
            snd->smp=Sound_NewSampleFromFile(fname.c_str(),&sndaudinf,4096);
            snd->len=Sound_GetDuration(snd->smp);
            return snd;
            //snd->pos=Sound_
        }
    };
};