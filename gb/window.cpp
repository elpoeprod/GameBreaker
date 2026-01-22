#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	GBSize window::size() {
		return {GetRenderWidth(),GetRenderHeight()};
	}

	void window::size(GBSize size) {
		SetWindowSize(size.w,size.h);
		return;
	}

	GBPoint window::pos() {
		return GetWindowPosition();
	}

	void window::pos(GBPoint pos) {
		SetWindowPosition(pos.x,pos.y);
		return;
	}

	void window::title(str title) {
		SetWindowTitle(title.c_str());
		window::__title=title;
		return;
	}

	str window::title() {
		return window::__title;
	}
}
