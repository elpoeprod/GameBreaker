#include "gamebreaker.hpp"

namespace GameBreaker {

    std::vector<GBFont*> gb_fonts;

    GBFont* font::add(gb_str fname, int size, int bold, int italic) {
        GBFont* fn = new GBFont;
        fn->font = TTF_OpenFont(fname.c_str(), size);
        fn->size = size;
        gb_fonts.resize(gb_fonts.size() + 1);
        gb_fonts[gb_fonts.size() - 1] = fn;
        TTF_SetFontHinting(fn->font,TTF_HINTING_LIGHT_SUBPIXEL);
        TTF_SetFontStyle(fn->font,bold?TTF_STYLE_BOLD:italic?TTF_STYLE_ITALIC:TTF_STYLE_NORMAL);
        return fn;
    }

    void font::destroy(GBFont* font) {
        TTF_CloseFont(font->font);
        font->size = 0;
        delete font;
    }

}