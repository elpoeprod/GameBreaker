#include "../include/gamebreaker.hpp"
#include <raylib.h>

namespace GameBreaker {
	int sprite::add(str fname, int frames, GBPoint offset) {
		this->offset=offset;
		this->image_index=0;
		this->image_speed=1;
		this->id=_gbsys_->__add(this);
		this->frames=frames;
		this->tex=LoadTexture(fname.c_str());
		return this->id;
	}
	
	void sprite::remove() {
		UnloadTexture(this->tex);
		delete this;
	}

	void sprite::draw(GBFPoint pos, int frame) {
		//GBFPoint ppos = GBXyfy(pos.x, pos.y);
		GBColor col = draw::color();
		Rectangle rect = {
			(this->tex.width * 1.f / this->frames) * frame, 0,
			1.f * this->tex.width / frames, 1.f * this->tex.height};
		DrawTexturePro(this->tex,rect,{pos.x,pos.y,this->tex.width*1.f,this->tex.height*1.f},this->offset,0,col);
	}

	void sprite::draw(GBFPoint pos, int frame, GBScale scale, real rot, GBColor col) {
		//auto ppos=GBXyfy(pos.x, pos.y);
		Rectangle rect={
			(this->tex.width * 1.f / this->frames) * frame, 0,
			1.f * this->tex.width / frames, 1.f * this->tex.height};
		DrawTexturePro(this->tex, rect, {pos.x,pos.y,this->tex.width*scale.xscale,this->tex.height*scale.yscale*1.f}, this->offset, rot, col);
	}

	void sprite::draw_stretched(GBFPoint pos, int frame, GBSize stretch) {
		//auto ppos=GBXyfy(pos.x, pos.y);
		Rectangle rect={
			(this->tex.width*1.f/this->frames) * frame,0, 1.f*this->tex.width/frames,this->tex.height*1.f
		};
		DrawTexturePro(this->tex,rect,{pos.x,pos.y,1.f*stretch.w,stretch.h*1.f},this->offset,0,draw::color());
	}

	void sprite::draw_stretched(GBFPoint pos, int frame, GBSize stretch, GBScale scale, real rot, GBColor col) {
		//auto ppos=GBXyfy(pos.x,pos.y);
		Rectangle rect={
			(this->tex.width*1.f/this->frames)*frame,0,1.f*this->tex.width/frames,1.f*this->tex.height
		};
		DrawTexturePro(this->tex, rect, {pos.x,pos.y,stretch.w*1.f*scale.xscale,stretch.h*1.f*scale.yscale},this->offset, rot, col);
	}

	void sprite::draw_part(GBFPoint pos, int frame, GBRect part) {
		//auto ppos=GBXyfy(pos.x,pos.y);
		Rectangle rect= {
			(this->tex.width*1.f/this->frames)*frame+part.x,part.y*1.f,
			1.f*part.w, 1.f*part.h
		};
		DrawTexturePro(this->tex,rect,{pos.x,pos.y,this->tex.width*1.f,this->tex.height*1.f},this->offset,0,draw::color());
	}

	void sprite::draw_part(GBFPoint pos, int frame, GBRect part, GBScale scale, real rot, GBColor col) {
		//auto ppos=GBXyfy(pos.x,pos.y);
		Rectangle rect= {
			(this->tex.width*1.f/this->frames)*frame+part.x,part.y*1.f,
			1.f*part.w, 1.f*part.h
		};
		DrawTexturePro(this->tex,rect,{pos.x,pos.y,this->tex.width*1.f*scale.xscale,this->tex.height*1.f*scale.yscale},this->offset,rot,col);
	}

	void sprite::draw_part_stretched(GBFPoint pos, int frame, GBRect part, GBSize size) {
		//auto ppos=GBXyfy(pos.x,pos.y);
		Rectangle rect= {
			(this->tex.width*1.f/this->frames)*frame+part.x,part.y*1.f,
			1.f*part.w, 1.f*part.h
		};
		DrawTexturePro(this->tex,rect,{pos.x,pos.y,size.w*1.f,size.h*1.f},this->offset,0,draw::color());
	}

	void sprite::draw_part_stretched(GBFPoint pos, int frame, GBRect part, GBSize size, GBScale scale, real rot, GBColor col) {
		//auto ppos=GBXyfy(pos.x,pos.y);
		Rectangle rect= {
			(this->tex.width*1.f/this->frames)*frame+part.x,part.y*1.f,
			1.f*part.w, 1.f*part.h
		};
		DrawTexturePro(this->tex,rect,{pos.x,pos.y,size.w*1.f*scale.xscale,size.h*1.f*scale.yscale},this->offset,rot,col);
	}
}
