#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_render.h>

/*
* GAMEBREAKER::GRAPHICS
*/

#define GAssert if(room_current->view_enabled[room_current->view_current]==0) return;

SDL_FPoint GBXyfy(double x, double y) {
    return {
        (float)(x-GameBreaker::room_current->view[GameBreaker::room_current->view_current].x),
        (float)(y-GameBreaker::room_current->view[GameBreaker::room_current->view_current].y),
    };
}

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;
    
    if(0 <= fHPrime && fHPrime < 1) {
      fR = fC;
      fG = fX;
      fB = 0;
    } else if(1 <= fHPrime && fHPrime < 2) {
      fR = fX;
      fG = fC;
      fB = 0;
    } else if(2 <= fHPrime && fHPrime < 3) {
      fR = 0;
      fG = fC;
      fB = fX;
    } else if(3 <= fHPrime && fHPrime < 4) {
      fR = 0;
      fG = fX;
      fB = fC;
    } else if(4 <= fHPrime && fHPrime < 5) {
      fR = fX;
      fG = 0;
      fB = fC;
    } else if(5 <= fHPrime && fHPrime < 6) {
      fR = fC;
      fG = 0;
      fB = fX;
    } else {
      fR = 0;
      fG = 0;
      fB = 0;
    }
    
    fR += fM;
    fG += fM;
    fB += fM;
}

namespace GameBreaker {

    std::vector<GBSprite*> gb_sprites;

    /**
    * draws a colored rectangle
    * \sa x,y - coordinates where the rectanggle should be drawn
    * \sa w,h - size of the rectangle
    * \sa col1, col2, col3, col4 - colors of rectangle (top-left, top-right, bottom-right, bottom-left)
    * \sa outline - if true, the rectangle will be drawn outlined only, otherwise rectangle will be filled
    **/
    int graphics::draw::rect_color(float x, float y, float w, float h, SDL_Color col1, SDL_Color col2, SDL_Color col3, SDL_Color col4, int outline)
    {
        const std::vector<SDL_Vertex> verts = {
            {
                SDL_FPoint { x, y },
                SDL_Color { col1.r, col1.g, col1.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { x + w, y },
                SDL_Color { col2.r, col2.g, col2.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { x + w, y + h },
                SDL_Color { col3.r, col3.g, col3.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { x + w, y + h },
                SDL_Color { col3.r, col3.g, col3.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { x, y + h },
                SDL_Color { col4.r, col4.g, col4.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { x, y },
                SDL_Color { col1.r, col1.g, col1.b, 255 },
                SDL_FPoint { 0 },
            },
        };
        return SDL_RenderGeometry(gb_win->ren, nullptr, verts.data(), verts.size(), nullptr, 0);
    }
    /**
    * draws a rectangle
    * \sa x*,y* - coordinates of three points used to create a triangle
    * \sa col* - color of triangle's corners
    **/
    void graphics::draw::triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color col1, SDL_Color col2, SDL_Color col3)
    {
        GAssert;
        auto _real_1=GBXyfy(x1,y1);
        auto _real_2=GBXyfy(x2,y2);
        auto _real_3=GBXyfy(x3,y3);

        const std::vector<SDL_Vertex> verts = {
            {
                SDL_FPoint { _real_1.x, _real_1.y },
                SDL_Color { col1.r, col1.g, col1.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { _real_2.x, _real_2.y },
                SDL_Color { col2.r, col2.g, col2.b, 255 },
                SDL_FPoint { 0 },
            },
            {
                SDL_FPoint { _real_2.x, _real_3.y },
                SDL_Color { col3.r, col3.g, col3.b, 255 },
                SDL_FPoint { 0 },
            },
        };
        SDL_RenderGeometry(gb_win->ren, nullptr, verts.data(), verts.size(), nullptr, 0);
    }
    /**
    * sets a color for drawing
    * \sa col - color in HEX form (0x123456)
    **/
    void graphics::draw::color(Uint32 color)
    {
        _realcol_=(SDL_Color){(Uint8)((color >> 8) & 0xFF), (Uint8)((color >> 4) & 0xFF), (Uint8)(color & 0xFF)};
        SDL_SetRenderDrawColor(gb_win->ren,_realcol_.r, _realcol_.g,_realcol_.b,255);
    }

    /**
    * sets a color for drawing
    * \sa col - color in HEX form (0x123456)
    **/
    void graphics::draw::color_rgb(Uint8 r,Uint8 g,Uint8 b)
    {
        _realcol_=(SDL_Color){r,g,b};
        SDL_SetRenderDrawColor(gb_win->ren,_realcol_.r, _realcol_.g,_realcol_.b,255);
    }

    void graphics::draw::set_font(GBFont *fnt) {
        curfon.f=fnt;
        curfon.bold=fnt->bold;
        curfon.italic=fnt->italic;
    }
    void graphics::draw::set_text_align(double ha, double va) {
        _gm_halign=ha;
        _gm_valign=va;
    }

    /**
    * draws a circle
    * \sa x,y - coordinates of circle's center
    * \sa r - radius of a circle
    * \sa outline - if true, circle will be drawn outlined
    **/
    void graphics::draw::circle(int x, int y, int r, int outline)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);
        if (outline)
            SDL_RenderDrawCircle(gb_win->ren, _real_.x, _real_.y, r);
        else
            SDL_RenderFillCircle(gb_win->ren, _real_.x, _real_.y, r);
    }
    /**
    * draws a line
    * \sa x1,y1 - first point
    * \sa x2,y2 - second point
    **/
    void graphics::draw::line(int x1, int y1, int x2, int y2)
    {
        GAssert;
        auto _real_1=GBXyfy(x1,y1);
        auto _real_2=GBXyfy(x2,y2);
        SDL_RenderDrawLine(gb_win->ren, _real_1.x, _real_1.y, _real_2.x, _real_2.y);
    }
    /**
    * draws a point
    * \sa x,y - point coordinates
    **/
    void graphics::draw::point(int x, int y)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);
        SDL_RenderDrawPoint(gb_win->ren, _real_.x, _real_.y);
    }
    /**
    * sets a color for drawing using SDL_Color struct
    * \sa color - SDL_Color color
    **/
    void graphics::draw::color_sdl(SDL_Color color)
    {
        _realcol_=color;
        SDL_SetRenderDrawColor(gb_win->ren, _realcol_.r, _realcol_.g, _realcol_.b, _realcol_.a);
    }

    void graphics::draw::color_hsv(double h, double s, double v) {
        float r,g,b;
        float _h=h,_s=s,_v=v;
        HSVtoRGB(r,g,b,_h,_s,_v);
        Uint8 _r=r,_g=g,_b=b;
        SDL_Color mycol={_r,_g,_b,_realcol_.a};
        graphics::draw::color_sdl(mycol);
    }


    void graphics::draw::text(float x, float y, GBText* text)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);
        SDL_Rect myrect = { 0, 0, text->surf->w, text->surf->h };
        SDL_FRect extrect = { _real_.x - (float)_gm_halign * text->surf->w, _real_.y - (float)_gm_valign * text->surf->h, (float)text->surf->w, (float)text->surf->h };
        SDL_SetTextureColorMod(text->tex,_realcol_.r,_realcol_.g,_realcol_.b);
        SDL_RenderCopyF(gb_win->ren, text->tex, &myrect, &extrect);
    }

    std::vector<GBText*> _gb_txt_;

    int __gb_find_text_in_db(gb_str text) {
        for(int i=0;i<(int)_gb_txt_.size();i++) {
            if(text==_gb_txt_[i]->txt) return i;
        }
        return -1;
    }

    void graphics::draw::text_rt(float x, float y, gb_str txt)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);
        GBText *text;
        int finder=__gb_find_text_in_db(txt);
        if(finder!=-1) {
            text=_gb_txt_[finder];
        }
        else {
            _gb_txt_.resize(_gb_txt_.size()+1);
            _gb_txt_[_gb_txt_.size()-1]=new GBText(txt);
            text=_gb_txt_[_gb_txt_.size()-1];
        }
        SDL_Rect myrect = { 0, 0, text->surf->w, text->surf->h };
        SDL_FRect extrect = { _real_.x - (float)_gm_halign * text->surf->w, _real_.y - (float)_gm_valign * text->surf->h, (float)text->surf->w, (float)text->surf->h };
        SDL_SetTextureColorMod(text->tex,_realcol_.r,_realcol_.g,_realcol_.b);
        SDL_RenderCopyF(gb_win->ren, text->tex, &myrect, &extrect);
    }

    void graphics::draw::alpha(float alpha) {
        _realcol_.a=alpha;
    }

    /**
    * adds a sprite
    * \sa fname - filename
    * \sa frames - frames, should be greater than 0
    * \sa offx, offy - offset coordinates
    **/
    GBSprite* graphics::sprite::add(std::string fname, int frames, int offx, int offy)
    {
        if (!fs::exists(fname)) {
            show::error("At graphics::sprite::add:\nFile doesn't exist: \"" + fname + "\".",1);
            return nullptr;
        }
        GBSprite* spr = new GBSprite;
        spr->frames = (frames < 1) ? 1 : frames;
        SDL_Surface* temp = IMG_Load(fname.c_str());
        spr->tex = SDL_CreateTextureFromSurface(gb_win->ren, temp);
        spr->w = temp->w;
        spr->h = temp->h;
        spr->offx=offx;
        spr->offy=offy;
        spr->_selx=0;
        spr->_sely=0;
        spr->_selw=temp->w;
        spr->_selh=temp->h;
        SDL_FreeSurface(temp);
        gb_sprites.resize(gb_sprites.size() + 1);
        gb_sprites[gb_sprites.size() - 1] = spr;
        return spr;
    }

    /**
    * adds a sprite with extended vars
    * \sa fname - filename
    * \sa frames - frames, should be greater than 0
    * \sa offx, offy - offset coordinates
    **/
    GBSprite* graphics::sprite::add_ext(std::string fname, int frames, int offx, int offy, int grabx, int graby, int grabw, int grabh)
    {
        if (!fs::exists(fname)) {
            show::error("At graphics::sprite::add:\nFile doesn't exist: \"" + fname + "\".",1);
            return nullptr;
        }
        GBSprite* spr = new GBSprite;
        spr->frames = (frames < 1) ? 1 : frames;
        SDL_Surface* temp = IMG_Load(fname.c_str());
        spr->tex = SDL_CreateTextureFromSurface(gb_win->ren, temp);
        spr->w = temp->w;
        spr->h = temp->h;
        spr->offx=offx;
        spr->offy=offy;
        spr->_selx=grabx;
        spr->_sely=graby;
        spr->_selw=grabw==0?temp->w:grabw;
        spr->_selh=grabh==0?temp->h:grabh;
        SDL_FreeSurface(temp);
        gb_sprites.resize(gb_sprites.size() + 1);
        gb_sprites[gb_sprites.size() - 1] = spr;
        return spr;
    }

    /**
    * destroy the sprite if it will not be used anymore
    * \sa spr - sprite
    **/
    void graphics::sprite::destroy(GBSprite* spr)
    {
        spr->frames = 0;
        spr->h = 0;
        spr->offx = 0;
        spr->offy = 0;
        spr->w = 0;
        SDL_DestroyTexture(spr->tex);
        delete spr;
        spr=nullptr;
    }

    void graphics::sprite::set_offset(GBSprite *spr, int x, int y) {
        spr->offx=x;
        spr->offy=y;
    }
    /**
    * draw a sprite on screen
    * \sa spr - sprite
    * \sa frame - sprite frame
    * \sa x,y - coordinates where the sprite should be drawn
    * \sa xscale, yscale - image scale (spr->w*xscale, spr->h*yscale)
    * \sa rot - rotate by 0-360 degrees
    **/
    void graphics::draw::sprite(GBSprite* spr, int frame, int x, int y, float xscale, float yscale, float rot)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);      
        var myw=((spr->_selw) / spr->frames);
        
        SDL_Rect rect = { 
        				(spr->_selx+myw * (frame % spr->frames)), spr->_sely, 
        				myw, spr->_selh
        				};
        SDL_FRect dstrect = { 
        				_real_.x-spr->offx*xscale, _real_.y-spr->offy*yscale, 
        				(float)myw * xscale, (float)(spr->_selh-spr->_sely) * yscale 
        				};
        				
        float cenx=spr->offx,ceny=spr->offy;
        SDL_FPoint cen = {cenx,ceny};
        SDL_SetTextureColorMod(spr->tex,_realcol_.r,_realcol_.g,_realcol_.b);
        SDL_SetTextureAlphaMod(spr->tex, _realcol_.a);
        int myflip=SDL_FLIP_NONE;
        if(xscale<0) myflip|=(int)SDL_FLIP_HORIZONTAL;
        if(yscale<0) myflip|=(int)SDL_FLIP_VERTICAL;
        SDL_RenderCopyExF(gb_win->ren, spr->tex, &rect, &dstrect, rot, &cen, (SDL_RendererFlip)myflip);
    }

    void graphics::draw::sprite_part(GBSprite* spr, int frame, int x, int y, int w, int h, float xscale, float yscale, float rot)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);

        var myw=((spr->_selw) / spr->frames);
        
        SDL_Rect rect = {
        				(spr->_selx+myw*(frame % spr->frames)),spr->_sely,
        				(int)math::clamp(w,0,myw),(int)math::clamp(h,0,spr->_selh-spr->_sely)
        				};
        SDL_FRect dstrect = { 
        				_real_.x-spr->offx*xscale, _real_.y-spr->offy*yscale, 
        				(float)myw * xscale, (float)spr->h * yscale 
        				};
        				
        float cenx=spr->offx,ceny=spr->offy;
        SDL_FPoint cen = { cenx,ceny };
        SDL_SetTextureColorMod(spr->tex,_realcol_.r,_realcol_.g,_realcol_.b);
        SDL_SetTextureAlphaMod(spr->tex, _realcol_.a);
        int myflip=SDL_FLIP_NONE;
        if(xscale<0) myflip|=(int)SDL_FLIP_HORIZONTAL;
        if(yscale<0) myflip|=(int)SDL_FLIP_VERTICAL;
        SDL_RenderCopyExF(gb_win->ren, spr->tex, &rect, &dstrect, rot, &cen, (SDL_RendererFlip)myflip);
    }

    void graphics::draw::sprite_stretched(GBSprite* spr, int frame, int x, int y, int w, int h, float xscale, float yscale, float rot)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);

        var myw=((spr->_selw/*-spr->_selx*/) / spr->frames);
        
        SDL_Rect rect = { 
        				(spr->_selx+myw * (frame % spr->frames)), spr->_sely, 
        				myw, spr->_selh-spr->_sely
        				};
        SDL_FRect dstrect = { 
        				_real_.x-spr->offx*xscale, _real_.y-spr->offy*yscale, 
        				(float)w * xscale, (float)h * yscale 
        				};
        				
        float cenx=spr->offx,ceny=spr->offy;
        SDL_FPoint cen = { cenx,ceny };
        SDL_SetTextureColorMod(spr->tex,_realcol_.r,_realcol_.g,_realcol_.b);
        SDL_SetTextureAlphaMod(spr->tex, _realcol_.a);
        int myflip=SDL_FLIP_NONE;
        if(xscale<0) myflip|=(int)SDL_FLIP_HORIZONTAL;
        if(yscale<0) myflip|=(int)SDL_FLIP_VERTICAL;
        SDL_RenderCopyExF(gb_win->ren, spr->tex, &rect, &dstrect, rot, &cen, (SDL_RendererFlip)myflip);
    }

    SDL_Color graphics::draw::color_get() {return _realcol_;}

    /**
    * draw a sprite on screen
    * \sa spr - sprite
    * \sa frame - sprite frame
    * \sa x,y - coordinates where the sprite should be drawn
    * \sa xscale, yscale - image scale (spr->w*xscale, spr->h*yscale)
    * \sa rot - rotate by 0-360 degrees
    **/
    void graphics::draw::sprite_ext(GBSprite* spr, int frame, int x, int y, float xscale, float yscale, float rot,SDL_Color col)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);
        var myw=((spr->_selw-spr->_selx)/spr->frames);
        graphics::draw::color_sdl(col);
        
        SDL_Rect rect = { 
				        spr->_selx+myw * (frame % spr->frames), spr->_sely, 
				        myw, spr->_selh-spr->_sely 
				        };
        SDL_FRect dstrect = { 
				        _real_.x, _real_.y, 
				        myw * xscale, (float)spr->h * yscale 
				        };
				        
        SDL_FPoint cen = { (float)spr->offx, (float)spr->offy };
        SDL_SetTextureColorMod(spr->tex,col.r,col.g,col.b);
        SDL_SetTextureAlphaMod(spr->tex, col.a);
        int myflip=SDL_FLIP_NONE;
        if(xscale<0) myflip|=(int)SDL_FLIP_HORIZONTAL;
        if(yscale<0) myflip|=(int)SDL_FLIP_VERTICAL;
        SDL_RenderCopyExF(gb_win->ren, spr->tex, &rect, &dstrect, rot, &cen, (SDL_RendererFlip)myflip);
    }

    /**
    * draws a rectangle
    * \sa x,y - coordinates where the rectanggle should be drawn
    * \sa w,h - size of the rectangle
    * \sa outline - if true, the rectangle will be drawn outlined only, otherwise rectangle will be filled
    **/
    void graphics::draw::rect(int x, int y, int w, int h, int outline)
    {
        GAssert;
        auto _real_=GBXyfy(x,y);
        SDL_Rect myrect = { (int)_real_.x,(int)_real_.y,w, h };
        if (outline == 0)
            SDL_RenderFillRect(gb_win->ren, &myrect);
        else
            SDL_RenderDrawRect(gb_win->ren, &myrect);
    }

    gb_button_state graphics::draw::button(int x, int y, int w, int h, GBSprite *spr, int types) {
        gb_button_state mystate={0,mb::none};
        if(room_current->view_enabled[room_current->view_current]==0) return mystate;
        int inrect=math::point_in_rect(mouse::x,mouse::y,x,y,x+w,y+h);
        int press=mouse::holding(mb::any);
        graphics::draw::sprite(spr,(inrect&&press)?spr->frames-1:types,x,y,(float)w/((float)spr->w/spr->frames),(float)h/(spr->h),0);
        mystate={inrect and mouse::released(mb::any),mouse::which()};
        return mystate;
    }

    void graphics::draw::blendmode(SDL_BlendMode mode) { 
        SDL_SetRenderDrawBlendMode(gb_win->ren, mode); 
    }

}
