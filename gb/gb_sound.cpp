#include "../include/gamebreaker.hpp"

/*******************
 * GAMEBREAKER::SOUND
 *
*/


namespace GameBreaker {
    GBAudio* curmusic;
    std::vector<GBSound*> gb_sounds;

    /**
    * returns new sound that was added from fname and type
    */
    GBAudio* audio::add(gb_str fname, int type)
    {
        GBAudio* mus = new GBAudio;
        mus->pos = 0;
        mus->vol = 1 * master_vol;
        mus->type = type;
        mus->x = 0;
        mus->y = 0;
        mus->pan = 0;
        if(type==GB_MUSIC) mus->chunk.stream.load(fname.c_str());
        else mus->chunk.nonstream.load(fname.c_str());
        mus->len=-1;
        //mus->tag[0]=mus->chunk.
        //mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
        //mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
        //mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
        curmusic = mus;
        return mus;
    }
    
    void audio::get_tags(GBAudio *mus) {
        //mus->tag[0]=Mix_GetMusicArtistTag(mus->chunk);
        //mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
        //mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
        //mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
    }
    
    /**
    * set sound pos
    **/
    
    void audio::set_pos(GBAudio* snd, double pos)
    {
        snd->pos = pos;
        __mus_handle->seek(snd->handle,pos);
    }
    
    /**
    * play sound
    * \sa snd - sound
    **/
    void audio::play(GBAudio* snd) {
        snd->handle=__mus_handle->play(snd->chunk.stream,1*master_vol);
    }
    /**
    * play sound looped
    * \sa snd - sound
    * \sa loops - how many times the sound should be repeated
    **/
    void audio::loop(GBAudio* snd, int loops) {
        snd->chunk.stream.setLooping((loops>0));
        snd->handle=__mus_handle->play(snd->chunk.stream);
    }
    /**
    * pauses the sound
    * \sa snd - sound
    **/
    void audio::pause(GBAudio *snd) {__mus_handle->setPause(snd->handle,true);}
    void audio::resume(GBAudio *snd) {__mus_handle->setPause(snd->handle,false);}
    /**
    * stops the sound entirely
    * \sa snd - sound
    **/
    void audio::stop(GBAudio* snd) { __mus_handle->stop(snd->handle); }
    /**
    * sets the volume of a sound
    * \sa snd - sound
    * \sa vol - volume
    **/
    void audio::set_vol(GBAudio* snd, double vol) {
        snd->chunk.stream.setVolume(vol);
        snd->vol=vol;
    }
    /**
    * destroy sound if it will not be used anymore
    * \sa snd - sound
    **/
    void audio::destroy(GBAudio* snd)
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
    
    double audio::get_pos(GBAudio *mus) {
        return __mus_handle->getStreamPosition(mus->handle);
    }
    
    double audio::get_len(GBAudio *mus) {
        return mus->len;
    }

    void audio::set_loops(int loops) {
        return; // no function in soloud to set loop count after song was played
    }
}