#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	void sprite::add(str fname, int frames, GBPoint offset) {
		this->offset=offset;
		this->image_index=0;
		this->image_speed=1;
		this->id=_gbsys_->__add(this);
		this->frames=frames;
		SDL_Surface *mysurf=IMG_Load(fname.c_str());
		this->size={mysurf->w/frames, mysurf->h};
		this->tex=SDL_CreateTextureFromSurface(_gbsys_->current_win()->get_render(),mysurf);
		SDL_FreeSurface(mysurf);
		return;
	}
	
	void sprite::remove() {
		SDL_DestroyTexture(this->tex);
		delete this;
	}

	void sprite::draw(GBFPoint pos, real frame) {
		GBFPoint ppos = GBXyfy(pos.x, pos.y);
		GBColor col = draw::color();
		SDL_SetTextureColorMod(this->tex, col.r, col.g, col.b);
		SDL_SetTextureAlphaMod(this->tex, col.a);
		SDL_Rect srcrect = {this->size.w*(int)frame, 0, this->size.w, this->size.h};
		SDL_FRect dstrect = {ppos.x, ppos.y, srcrect.w*1.f, srcrect.h*1.f};
		SDL_RenderCopyF(_gbsys_->current_win()->get_render(), this->tex, &srcrect, &dstrect);
	}
}
