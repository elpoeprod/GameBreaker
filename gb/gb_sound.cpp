#include "../include/gamebreaker.hpp"
#include <taglib/tag.h>
#include <taglib/fileref.h>

/*******************
 * GAMEBREAKER::SOUND
 *
*/


namespace GameBreaker {
    GBAudio* curmusic;
    std::vector<GBAudio*> gb_sounds;

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
        mus->fname=fname;

        mus->loops=0;
        if(type==GB_MUSIC) mus->chunk.stream.load(fname.c_str());
        else mus->chunk.nonstream.load(fname.c_str());
        mus->len=-1;
        curmusic = mus;
        return mus;
    }
    
    void audio::get_tags(GBAudio *mus) {
    	
    	TagLib::FileRef f(mus->fname.c_str());
        mus->tag["artist"]=	f.tag()->artist().to8Bit();
        mus->tag["album"]=	f.tag()->album().to8Bit();
        mus->tag["title"]=	f.tag()->title().to8Bit();
        mus->tag["year"]=	stringify(f.tag()->year());
        mus->tag["genre"]=	f.tag()->genre().to8Bit();
        mus->tag["track"]=	stringify(f.tag()->track());
        
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
    	snd->loops=loops;
        if(snd->type==GB_MUSIC) snd->chunk.stream.setLooping((loops>0||loops==-1));
        else snd->chunk.nonstream.setLooping((loops>0||loops==-1));
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
        return;
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
        return;
    }
    
    double audio::get_pos(GBAudio *mus) {
        return __mus_handle->getStreamPosition(mus->handle);
    }
    
    double audio::get_len(GBAudio *mus) {
        return mus->len;
    }

    void audio::set_loops(GBAudio *snd, int loops) {
		snd->loops=loops;
        return;
    }

    int audio::get_wave(GBAudio *snd, int pos) {
    	if(snd==nullptr) return 0;
    	if(snd->type==GB_MUSIC)
    		return __mus_handle->getWave()[pos];
    	else 
    		return __mus_handle->getWave()[pos];
    }

    int audio::get_fft(GBAudio *snd, int pos) {
    	if(snd==nullptr) return 0;
    	if(snd->type==GB_MUSIC)
    		return __mus_handle->calcFFT()[pos];
    	else
    		return __mus_handle->calcFFT()[pos];
    }
}
