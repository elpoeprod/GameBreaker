#include "../include/gamebreaker.hpp"

namespace GameBreaker {
	std::vector<GBSurface *> gb_surfs;

	int __gb_uses_surfaces=0;

	GBSurface *surface::add(int w, int h) {
		auto mysurf=new GBSurface;
		mysurf->w=w;
		mysurf->h=h;
		mysurf->surf=SDL_CreateTexture(gb_win->ren, SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_TARGET, w, h);
		return mysurf;
	}

	void surface::target_set(GBSurface *surf) {
		__gb_uses_surfaces=1;
		SDL_SetRenderTarget(gb_win->ren,surf->surf);
	}

	void surface::target_reset() {
		__gb_uses_surfaces=0;
		SDL_SetRenderTarget(gb_win->ren,nullptr);
	}

	void graphics::draw::surface(GBSurface *surf, int x, int y, float xscale, float yscale, float rot, SDL_Color col) {

		SDL_Rect mysrcrect={0,0,surf->w,surf->h};
		SDL_Rect mydstrect={x,y,int(surf->w*xscale),int(surf->h*yscale)};
		SDL_Point mypoint{0,0};
		SDL_SetRenderDrawColor(gb_win->ren,col.r,col.g,col.b,col.a);
		SDL_RenderCopyEx(gb_win->ren,surf->surf,&mysrcrect,&mydstrect,rot,&mypoint,SDL_RendererFlip(0));
		return;
	}
}
