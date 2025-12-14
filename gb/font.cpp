#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	void font::add(str fname, int size, int bold, int italic) {
		this->fnt = TTF_OpenFont(fname.c_str(), size);
		this->size = size;
		this->bold = bold;
		this->italic = italic;
		this->id = _gbsys_->__add(this);
		return;
	}

	void font::remove() {
		delete this;
	}
}
