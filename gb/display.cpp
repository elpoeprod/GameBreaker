#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	GBSize display::size() {
		SDL_Rect r={0,0,0,0};
		SDL_GetDisplayBounds(0, &r);
		return {r.w, r.h};
	}

	str display::name() {
		return SDL_GetDisplayName(0);
	}
}
