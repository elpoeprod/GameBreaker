#include "../include/gamebreaker.hpp"
#include <taglib/tag.h>
#include <taglib/fileref.h>

/*******************
 * GAMEBREAKER::SOUND
 *
*/

#define SAssert if(snd==nullptr) return;
#define SAssertn if(snd==nullptr) return (int)NULL;

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
        
        if(type==GB_MUSIC) {
        	if(gstr::pos(gstr::file_ext(fname),"669, amf, ams, dbm, digi, dmf, dsm, far, gdm, ice, imf, it, itp, j2b, m15, mdl, med, mid, mo3, mod, mptm, mt2, mtm, okt, plm, psm, ptm, s3m, stm, ult, umx, wow, xm")) {
        		mus->chunk.mod.load(fname.c_str());
		       	mus->handle=__mus_handle->play(mus->chunk.mod,1*master_vol,0,1);
		       	mus->len=-1;//mus->chunk.mod.getLength();
        	} else {
				mus->chunk.stream.load(fname.c_str());
	        	mus->handle=__mus_handle->play(mus->chunk.stream,1*master_vol,0,1);
	        	mus->len=mus->chunk.stream.getLength();
        	}
        }
        else {
        	if(gstr::pos(gstr::file_ext(fname),"669, amf, ams, dbm, digi, dmf, dsm, far, gdm, ice, imf, it, itp, j2b, m15, mdl, med, mid, mo3, mod, mptm, mt2, mtm, okt, plm, psm, ptm, s3m, stm, ult, umx, wow, xm")) {
           		mus->chunk.mod.load(fname.c_str());
   		       	mus->handle=__mus_handle->play(mus->chunk.mod,1*master_vol,0,1);
   		       	mus->len=-1;//mus->chunk.mod.getLength();
           	} else {
		       	mus->chunk.nonstream.load(fname.c_str());
		       	mus->handle=__mus_handle->play(mus->chunk.nonstream,1*master_vol,0,1);
		       	mus->len=mus->chunk.nonstream.getLength();
        	}
        }       
		
        curmusic = mus;
        return mus;
    }
    
    void audio::get_tags(GBAudio *snd) {
    	SAssert;
    	TagLib::FileRef f(snd->fname.c_str());
        snd->tag["artist"]=	f.tag()->artist().to8Bit();
        snd->tag["album"]=	f.tag()->album().to8Bit();
        snd->tag["title"]=	f.tag()->title().to8Bit();
        snd->tag["year"]=	stringify(f.tag()->year());
        snd->tag["genre"]=	f.tag()->genre().to8Bit();
        snd->tag["track"]=	stringify(f.tag()->track());
        return;
    }
    
    /**
    * set sound pos
    **/
    
    void audio::set_pos(GBAudio* snd, float pos)
    {
    	SAssert;
        snd->pos = pos;
        __mus_handle->seek(snd->handle,pos);
        return;
    }
    
    /**
    * play sound
    * \sa snd - sound
    **/
    void audio::play(GBAudio* snd) {
    	SAssert;
    	/*
        if(snd->type==GB_MUSIC) snd->handle=__mus_handle->play(snd->chunk.stream,1*master_vol);
        else snd->handle=__mus_handle->play(snd->chunk.nonstream,1*master_vol);
        */
        __mus_handle->setPause(snd->handle,false);
        return;
    }
    
    /**
    * play sound looped
    * \sa snd - sound
    * \sa loops - how many times the sound should be repeated
    **/
    void audio::loop(GBAudio* snd, int loops) {
    	SAssert;
    	snd->loops=loops;
    	
        if(snd->type==GB_MUSIC) 
        	snd->chunk.stream.setLooping((loops>0||loops==-1));
        else 
        	snd->chunk.nonstream.setLooping((loops>0||loops==-1));

        __mus_handle->setPause(snd->handle,false);
        return;
    }
    /**
    * pauses the sound
    * \sa snd - sound
    **/
    void audio::pause(GBAudio *snd) {
    	SAssert;
    	__mus_handle->setPause(snd->handle,true);
    	return;
    }
    
    void audio::resume(GBAudio *snd) {
    	SAssert;
    	__mus_handle->setPause(snd->handle,false);
    	return;
    }
    /**
    * stops the sound entirely
    * \sa snd - sound
    **/
    void audio::stop(GBAudio* snd) { 
    	SAssert;
    	__mus_handle->stop(snd->handle); 
    	return;
    }
    /**
    * sets the volume of a sound
    * \sa snd - sound
    * \sa vol - volume
    **/
    void audio::set_vol(GBAudio* snd, double vol) {
    	SAssert;
        __mus_handle->setVolume(snd->handle,vol);
        snd->vol=vol;
        return;
    }

    double audio::get_vol(GBAudio *snd) {
    	SAssertn;
    	return __mus_handle->getVolume(snd->handle);
    }
    /**
    * destroy sound if it will not be used anymore
    * \sa snd - sound
    **/
    void audio::destroy(GBAudio* snd)
    {
    	SAssert;
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
    
    double audio::get_pos(GBAudio *snd) {
    	SAssertn;
        return __mus_handle->getStreamTime(snd->handle);
    }
    
    double audio::get_len(GBAudio *snd) {
    	SAssertn;
        return snd->len;
    }

    void audio::set_loops(GBAudio *snd, int loops) {
    	SAssert;
		snd->loops=loops;
        return;
    }

    float audio::get_wave(GBAudio *snd, int pos) {
    	SAssertn;
    	if(snd->type==GB_MUSIC)
    		return __mus_handle->getWave()[pos];//*4;//*(256*((pos+2)/128));
    	else 
    		return __mus_handle->getWave()[pos];//*4;//*(256*((pos+2)/128));
    }

    float audio::get_fft(GBAudio *snd, int pos) {
    	SAssertn;
    	if(pos==0) return __mus_handle->calcFFT()[pos]/4;
    	if(snd->type==GB_MUSIC)
    		return __mus_handle->calcFFT()[pos]*4;//*(256*((pos+2)/128));
    	else
    		return __mus_handle->calcFFT()[pos]*4;//*(256*((pos+2)/128));
    }
}
