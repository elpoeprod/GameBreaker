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
    GBMusic* music::add(gb_str fname, int type)
    {
        GBMusic* mus = new GBMusic;
        mus->pos = 0;
        mus->vol = 1 * master_vol;
        mus->type = type;
        mus->x = 0;
        mus->y = 0;
        mus->pan = 0;
        mus->chunk.stream.load(fname.c_str());
        mus->len=-1;
        //mus->tag[0]=mus->chunk.
        //mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
        //mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
        //mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
        curmusic = mus;
        return mus;
    }
    
    void music::get_tags(GBMusic *mus) {
        //mus->tag[0]=Mix_GetMusicArtistTag(mus->chunk);
        //mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
        //mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
        //mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
    }
    
    /**
    * set sound pos
    **/
    
    void music::set_pos(GBMusic* snd, double pos)
    {
        snd->pos = pos;
        __mus_handle->seek(snd->handle,pos);
    }
    
    /**
    * play sound
    * \sa snd - sound
    **/
    void music::play(GBMusic* snd) {
        snd->handle=__mus_handle->play(snd->chunk.stream,1*master_vol);
    }
    /**
    * play sound looped
    * \sa snd - sound
    * \sa loops - how many times the sound should be repeated
    **/
    void music::loop(GBMusic* snd, int loops) {
        snd->chunk.stream.setLooping((loops>0));
        snd->handle=__mus_handle->play(snd->chunk.stream);
    }
    /**
    * pauses the sound
    * \sa snd - sound
    **/
    void music::pause(GBMusic *snd) {__mus_handle->setPause(snd->handle,true);}
    void music::resume(GBMusic *snd) {__mus_handle->setPause(snd->handle,false);}
    /**
    * stops the sound entirely
    * \sa snd - sound
    **/
    void music::stop(GBMusic* snd) { __mus_handle->stop(snd->handle); }
    /**
    * sets the volume of a sound
    * \sa snd - sound
    * \sa vol - volume
    **/
    void music::set_vol(GBMusic* snd, double vol) {
        snd->chunk.stream.setVolume(vol);
        snd->vol=vol;
    }
    /**
    * destroy sound if it will not be used anymore
    * \sa snd - sound
    **/
    void music::destroy(GBMusic* snd)
    {
        snd->x = 0;
        snd->y = 0;
        snd->pan = 0;
        snd->pos = 0;
        snd->type = 0;
        snd->vol = 0;
        delete snd;
        snd=nullptr;
    }
    
    double music::get_pos(GBMusic *mus) {
        return __mus_handle->getStreamPosition(mus->handle);
    }
    
    double music::get_len(GBMusic *mus) {
        return mus->len;
    }

    void music::set_loops(int loops) {
        return; // no function in soloud to set loop count after song was played
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
        snd->chunk.nonstream.load(fname.c_str());
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
        return 0;
    }
    
    int music::get_wave(GBMusic* snd,int pos) {
        return 0;
    }
    
    /**
    * play sound
    * \sa snd - sound
    **/
    void sound::play(GBSound* snd) { 
        if(snd->type==GB_2D) snd->handle=__mus_handle->play(snd->chunk.nonstream,snd->vol*master_vol);
        else __mus_handle->play3d(snd->chunk.nonstream,snd->x,snd->y,snd->z,1*master_vol);
    }
    /**
    * play sound looped
    * \sa snd - sound
    * \sa loops - how many times the sound should be repeated
    **/
    void sound::loop(GBSound* snd, int loops) { 
        snd->chunk.nonstream.setLooping(loops>0);
        if(snd->type==GB_2D) snd->handle=__mus_handle->play(snd->chunk.nonstream,snd->vol*master_vol);
        else __mus_handle->play3d(snd->chunk.nonstream,snd->x,snd->y,snd->z,1*master_vol);
    }
    /**
    * pauses the sound
    * \sa snd - sound
    **/
    void sound::pause(GBSound* snd) { __mus_handle->setPause(snd->handle, true); }
    /**
    * stops the sound entirely
    * \sa snd - sound
    **/
    void sound::stop(GBSound* snd) { snd->chunk.nonstream.stop();}
    /**
    * sets the volume of a sound
    * \sa snd - sound
    * \sa vol - volume
    **/
    void sound::set_vol(GBSound* snd, double vol) {
        snd->chunk.nonstream.setVolume(vol*master_vol);
    }
    /**
    * destroy sound if it will not be used anymore
    * \sa snd - sound
    **/
    void sound::destroy(GBSound* snd)
    {
        snd->x = 0;
        snd->y = 0;
        snd->pan = 0;
        snd->pos = 0;
        snd->type = 0;
        snd->vol = 0;
        delete snd;
        snd = nullptr;
    }
}