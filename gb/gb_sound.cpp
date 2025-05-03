#include "gamebreaker.hpp"

/*******************
 * GAMEBREAKER::SOUND
 *
*/


namespace GameBreaker {
    GBMusic* curmusic;
    std::vector<GBSound*> gb_sounds;
    /**
    * returns new sound that was added from fname and type (unused)
    */
    GBMusic* music::add(std::string fname, int type)
    {
        GBMusic* mus = new GBMusic;
        mus->pos = 0;
        mus->vol = 1 * master_vol;
        mus->type = type;
        mus->x = 0;
        mus->y = 0;
        mus->pan = 0;
        mus->chunk = Mix_LoadMUS(fname.c_str());
        mus->len=-1;
        if(mus->chunk==nullptr) {
        show::error(R"(At function music::add:
    Can't load file with name )" + fname,1);
        }
        mus->tag[0]=Mix_GetMusicArtistTag(mus->chunk);
        mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
        mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
        mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
        curmusic = mus;
        return mus;
    }
    
    void music::get_tags(GBMusic *mus) {
        mus->tag[0]=Mix_GetMusicArtistTag(mus->chunk);
        mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
        mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
        mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
    }
    
    /**
    * set sound pos
    **/
    
    void music::set_pos(GBMusic* snd, double pos)
    {
        snd->pos = pos;
        Mix_SetMusicPosition(snd->pos);
    }
    
    /**
    * play sound
    * \sa snd - sound
    **/
    void music::play(GBMusic* snd) { Mix_PlayMusic(snd->chunk, 0); snd->len=Mix_MusicDuration(snd->chunk);}
    /**
    * play sound looped
    * \sa snd - sound
    * \sa loops - how many times the sound should be repeated
    **/
    void music::loop(GBMusic* snd, int loops) { Mix_PlayMusic(snd->chunk, loops); snd->len=Mix_MusicDuration(snd->chunk);}
    /**
    * pauses the sound
    * \sa snd - sound
    **/
    void music::pause() { Mix_PauseMusic(); }
    void music::resume() {Mix_ResumeMusic();}
    /**
    * stops the sound entirely
    * \sa snd - sound
    **/
    void music::stop(GBMusic* snd) { Mix_HaltMusic(); }
    /**
    * sets the volume of a sound
    * \sa snd - sound
    * \sa vol - volume
    **/
    void music::set_vol(GBMusic* snd, double vol) {
    #ifdef GB_USE_GM_VOLUME
        Mix_VolumeMusic(vol * 128); }
    #else
        Mix_VolumeMusic(vol);
    #endif
    }
    /**
    * destroy sound if it will not be used anymore
    * \sa snd - sound
    **/
    void music::destroy(GBMusic* snd)
    {
        snd->x = 0;
        snd->y = 0;
        Mix_FreeMusic(snd->chunk);
        snd->pan = 0;
        snd->pos = 0;
        snd->type = 0;
        snd->vol = 0;
        delete snd;
        snd=nullptr;
    }
    
    double music::get_pos(GBMusic *mus) {
        if(mus->chunk==nullptr) return 0;
        return Mix_GetMusicPosition(mus->chunk);
    }
    
    double music::get_len(GBMusic *mus) {
        return mus->len;
    }

    void music::set_loops(int loops) {
        return; // no function in sdl2 to set loop count after song was played
    }
    
    /**
    * returns new sound that was added from fname and type (unused)
    */
    GBSound* sound::add(std::string fname, int type)
    {
        if (!fs::exists(fname)) {
            show::error("At sound::add:\nFile doesn't exist: \"" + fname + "\".",1);
            return nullptr;
        }
        GBSound* snd = new GBSound;
        snd->pos = 0;
        snd->vol = 1 * master_vol;
        snd->type = type;
        snd->x = 0;
        snd->y = 0;
        snd->pan = 0;
        snd->chunk = Mix_LoadWAV(fname.c_str());
        gb_sounds.resize(gb_sounds.size() + 1);
        gb_sounds[gb_sounds.size() - 1] = snd;
        return snd;
    }
    /**
    * set sound pos (unused for a while)
    **/
    
    void sound::set_pos(GBSound* snd, double pos)
    {
        snd->pos = pos;
        // Mix_SetMusicPosition(snd->pos);
    }
    int sound::get_wave(GBSound* snd, int pos)
    {
        int h = snd->chunk->abuf[pos];
    
        return h;
    }
    
    static int get_wave(GBMusic* snd,int pos) {
        return 0;
    }
    
    /**
    * play sound
    * \sa snd - sound
    **/
    void sound::play(GBSound* snd) { snd->channel = Mix_PlayChannel(-1, snd->chunk, 0); }
    /**
    * play sound looped
    * \sa snd - sound
    * \sa loops - how many times the sound should be repeated
    **/
    void sound::loop(GBSound* snd, int loops) { snd->channel = Mix_PlayChannel(-1, snd->chunk, loops); }
    /**
    * pauses the sound
    * \sa snd - sound
    **/
    void sound::pause(GBSound* snd) { Mix_Pause(snd->channel); }
    /**
    * stops the sound entirely
    * \sa snd - sound
    **/
    void sound::stop(GBSound* snd) { Mix_HaltChannel(snd->channel); }
    /**
    * sets the volume of a sound
    * \sa snd - sound
    * \sa vol - volume
    **/
    void sound::set_vol(GBSound* snd, double vol) {
    #ifdef GB_USE_GM_VOLUME
    Mix_Volume(snd->channel, vol * 128);
    #else
    Mix_Volume(snd->channel,vol);
    #endif
    }
    /**
    * destroy sound if it will not be used anymore
    * \sa snd - sound
    **/
    void sound::destroy(GBSound* snd)
    {
        snd->x = 0;
        snd->y = 0;
        Mix_FreeChunk(snd->chunk);
        snd->pan = 0;
        snd->pos = 0;
        snd->type = 0;
        snd->vol = 0;
        delete snd;
        snd = nullptr;
    }
}