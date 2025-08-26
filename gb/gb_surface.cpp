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
		SDL_SetRenderDrawBlendMode(gb_win->ren, SDL_BLENDMODE_BLEND);
		SDL_RenderClear(gb_win->ren);
		return;
	}

	void surface::target_reset() {
		__gb_uses_surfaces=0;
		SDL_SetRenderTarget(gb_win->ren,nullptr);
		SDL_SetRenderDrawBlendMode(gb_win->ren, SDL_BLENDMODE_BLEND);
		return;
	}

	void graphics::draw::surface(GBSurface *surf, int x, int y, float xscale, float yscale, float rot, SDL_Color col) {

		SDL_Rect mysrcrect={0,0,surf->w,surf->h};
		SDL_Rect mydstrect={x,y,int(surf->w*xscale),int(surf->h*yscale)};
		SDL_Point mypoint{0,0};
		SDL_SetRenderDrawColor(gb_win->ren,col.r,col.g,col.b,col.a);
		SDL_SetTextureBlendMode(surf->surf, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(surf->surf, col.a);
		SDL_SetTextureColorMod(surf->surf, col.r,col.g,col.b);
		SDL_RenderCopyEx(gb_win->ren,surf->surf,&mysrcrect,&mydstrect,rot,&mypoint,SDL_RendererFlip(0));
		return;
	}

	void surface::clone(GBSurface *src, GBSurface *dst, int x, int y) {
		SDL_Rect dstrect={x,y,dst->w,dst->h};
		SDL_SetRenderTarget(gb_win->ren,dst->surf);
		SDL_RenderCopy(gb_win->ren,src->surf,nullptr,&dstrect);
		SDL_SetRenderTarget(gb_win->ren,nullptr);
		return;
	}
}
