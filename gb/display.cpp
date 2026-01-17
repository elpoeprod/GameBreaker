#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	GBSize display::size() {
		return {GetScreenWidth(),GetScreenHeight()};
	}

	str display::name() {
		return GetMonitorName(_gbsys_->current_display());
	}
}
