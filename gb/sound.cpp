#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	void sound::add(str fname, int type) {
		switch(type) {
			case SOUND_TYPE::stream: 
				this->handle.mus=LoadMusicStream(fname.c_str()); 
				break;
			case SOUND_TYPE::nonstream: 
				this->handle.snd=LoadSound(fname.c_str()); 
				break;
			default: break;
		}
		this->_pan=0;
		this->_volume=1;
		this->_type=type;
	}

	void sound::volume(real vol) {
		this->_volume=vol;
		if(this->_type==SOUND_TYPE::stream) 
			SetMusicVolume(this->handle.mus,vol);
		else
			SetSoundVolume(this->handle.snd,vol); 
	}

	real sound::volume() {
		return this->_volume;
	}

	void sound::pan(real pan) {
		this->_pan=pan;
		if(this->_type==SOUND_TYPE::stream)
			SetMusicPan(this->handle.mus,pan);
		else
			SetSoundPan(this->handle.snd,pan);
	}

	real sound::pan() {
		return this->_pan;
	}

	void sound::play() {
		if(this->_type==SOUND_TYPE::stream)
			PlayMusicStream(this->handle.mus);
		else
			PlaySound(this->handle.snd);
	}

	void sound::loop(int loops) {
		this->_loops=loops;
		if(this->_type==SOUND_TYPE::stream) 
			this->handle.mus.looping=loops>0;
		else
			debug_message("No support for looping Sound. TODO");
	}

	void sound::stop() {
		if(this->_type==SOUND_TYPE::stream) 
			StopMusicStream(this->handle.mus);
		else
			StopSound(this->handle.snd);
	}

	void sound::pause() {
		if(this->_type==SOUND_TYPE::stream) 
			PauseMusicStream(this->handle.mus);
		else
			PauseSound(this->handle.snd);
	}

	void sound::resume() {
		if(this->_type==SOUND_TYPE::stream) 
			ResumeMusicStream(this->handle.mus);
		else
			ResumeSound(this->handle.snd);
	}

	void sound::remove() {
		if(this->_type==SOUND_TYPE::stream) { 
			StopMusicStream(this->handle.mus);
			UnloadMusicStream(this->handle.mus);
		} else {
			StopSound(this->handle.snd);
			UnloadSound(this->handle.snd);
		}
		delete this;
	}
}
