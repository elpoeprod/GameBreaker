#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	void font::add(str fname, int size, int bold, int italic) {
		this->fnt = LoadFont(fname.c_str());
		this->size = size;
		this->bold = bold;
		this->italic = italic;
		this->id = _gbsys_->__add(this);
		return;
	}

	void font::remove() {
		delete this;
	}

	Font font::_getor() {
		return this->fnt;
	}
}
