#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_ttf.h>

namespace GameBreaker {

    std::vector<GBFont*> gb_fonts;

    GBFont* font::add(gb_str fname, int size) {
        GBFont* fn = new GBFont;
        fn->font = TTF_OpenFont(fname.c_str(), size);
        if(fn->font==nullptr or fn->font==NULL) {show::error("At function font::add:\nFile doesn't exists: "+fname,1); return nullptr;} 
        fn->size = size;
        gb_fonts.resize(gb_fonts.size() + 1);
        gb_fonts[gb_fonts.size() - 1] = fn;
        TTF_SetFontHinting(fn->font,TTF_HINTING_LIGHT_SUBPIXEL);
        return fn;
    }
    
    void font::style(GBFont *font, int bold, int italic) {
        int myform=(bold&&italic)? TTF_STYLE_BOLD|TTF_STYLE_ITALIC:bold?TTF_STYLE_BOLD:italic?TTF_STYLE_ITALIC:0;
        TTF_SetFontStyle(font->font,myform);
    }

    void font::style_ext(GBFont *font, int style) {
        TTF_SetFontStyle(font->font,style);
    }

    void font::destroy(GBFont* font) {
        TTF_CloseFont(font->font);
        font->size = 0;
        delete font;
    }

}