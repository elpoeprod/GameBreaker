#include "../include/gamebreaker.hpp"

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

	void sprite::draw(GBFPoint pos, real frame) {
		GBFPoint ppos = GBXyfy(pos.x, pos.y);
		GBColor col = draw::color();
		Rectangle rect={(this->tex.width/this->frames)*frame, 0, 1.f*this->tex.width/frames, 1.f*this->tex.height};
		DrawTextureRec(this->tex, rect, {ppos.x,ppos.y},col);
	}
}
