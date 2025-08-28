#include "../include/gamebreaker.hpp"

namespace GameBreaker {

	const SDL_Color color::black = { 0, 0, 0, 255 },
	          color::white = { 255, 255, 255, 255 },
	          color::red = { 255, 0, 0, 255 },
	          color::blue = { 0, 0, 255, 255 },
	          color::green = { 0, 200, 0, 255 },
	          color::lime = { 0, 255, 50, 255 },
	          color::gray = { 128, 128, 128, 255 },
	          color::lt_gray = { 192, 192, 192, 255 },
	          color::dk_gray = { 80, 80, 80, 255 },
	          color::fuchsia = { 200, 50, 200, 255 },
	          color::purple = { 100, 16, 192, 255 },
	          color::aqua = { 50, 255, 255, 255 },
	          color::pink = { 255, 128, 128, 255 };

	SDL_Color color::mix(SDL_Color col1, SDL_Color col2) {
		return {Uint8((col1.r*col2.r)/255),Uint8((col1.g*col2.g)/255),Uint8((col1.b*col2.b)/255),Uint8((col1.a*col2.a)/255)};
	}

	SDL_Color color::merge(SDL_Color col1, SDL_Color col2, double amount) {
		return {Uint8(math::lerp(col1.r,col2.r,amount)),Uint8(math::lerp(col1.g,col2.g,amount)),Uint8(math::lerp(col1.b,col2.b,amount)),Uint8(math::lerp(col1.a,col2.a,amount))};
	}

}
