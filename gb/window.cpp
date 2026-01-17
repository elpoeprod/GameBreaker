#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	GBSize window::get_size() {
		return {GetRenderWidth(),GetRenderHeight()};
	}

	void window::set_size(GBSize size) {
		SetWindowSize(size.w,size.h);
		return;
	}

	GBPoint window::get_pos() {
		return GetWindowPosition();
	}

	void window::set_pos(GBPoint pos) {
		SetWindowPosition(pos.x,pos.y);
		return;
	}

	void window::set_title(str title) {
		SetWindowTitle(title.c_str());
		window::title=title;
		return;
	}

	str window::get_title() {
		return window::title;
	}
}
