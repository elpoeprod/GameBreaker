#include "gamebreaker.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <filesystem>

std::string __error_string;

void __error_write(std::string errstr)
{
    std::string tempf=SDL_GetBasePath();
    var f=GameBreaker::fs::text::open((tempf+"/error.txt").c_str(),GameBreaker::fs::fmode::write);
    GameBreaker::fs::text::write(f,errstr);
    GameBreaker::fs::text::close(f);
    __error_string=errstr;
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

int mybut[3];
int mylastbut[3];

int myjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
int mylastjoybut[32][SDL_CONTROLLER_BUTTON_MAX];
int gb_working_joystick = -1;
GBMusic* curmusic;

std::vector<SDL_GameController*> controllers;
int joy_count = 0;

void findControllers()
{
    int ii = 0;
    controllers.resize(SDL_NumJoysticks());
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            controllers[ii] = SDL_GameControllerOpen(i);
            gb_working_joystick = ii;
            ii++;
            joy_count++;
        }
    }
}

namespace GameBreaker {
SDL_Color _realcol_={255,255,255,255};
GBFont *curfon;
int current_time=0;
double master_vol = 1,
    _gm_halign=0, _gm_valign = 0;
std::vector<GBSound*> gb_sounds;
std::vector<GBSprite*> gb_sprites;
std::vector<GBObject*> gb_objects;
std::vector<GBFont*> gb_fonts;
std::vector<_gm_file *>gb_files;
GBWindow* gb_win;

int joy::count()
{
    return joy_count;
}
int joy::working() { return gb_working_joystick; }
int joy::pressed(int joy, int button) { return myjoybut[joy][button] && !mylastjoybut[joy][button]; }
int joy::released(int joy, int button) { return !myjoybut[joy][button] && mylastjoybut[joy][button]; }
int joy::holding(int joy, int button) { return myjoybut[joy][button] && mylastjoybut[joy][button]; }

int mouse::x = 0;
int mouse::y = 0;

int init(int x, int y, int w, int h, std::string label)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Uint32 mix_flags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OPUS | MIX_INIT_MP3;
#ifndef __PSP__
    mix_flags |= MIX_INIT_WAVPACK;
#endif
    Mix_Init(mix_flags);
    IMG_Init(IMG_INIT_WEBP | IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_AVIF | IMG_INIT_JXL | IMG_INIT_TIF);
    int hz=44100;
    int channels=2;
    Uint16 format=MIX_DEFAULT_FORMAT;
    //Mix_QuerySpec(&hz,&format,&channels);
    Mix_OpenAudio(hz, format, channels, 1024);
    gb_win = new GBWindow;
    gb_win->win = SDL_CreateWindow(label.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
    gb_win->ren = SDL_CreateRenderer(gb_win->win, -1, SDL_RENDERER_ACCELERATED);
    gb_win->x = x;
    gb_win->y = y;
    gb_win->w = w;
    gb_win->h = h;
    gb_win->running = 1;
    mouse::x = 0;
    mouse::y = 0;
    for (int i = 0; i < 3; i++) {
        mybut[i] = 0;
        mylastbut[i] = 0;
    }
    for (int i = 0; i < joy::count(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            myjoybut[i][ii] = 0;
            mylastjoybut[i][ii] = 0;
        }
    }
    findControllers();

    return 1;
}

void io::clear() {
    for (int i = 0; i < 3; i++) {
        mylastbut[i] = 0;
    }
    for (int i = 0; i < controllers.size(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            mylastjoybut[i][ii] = 0;
            myjoybut[i][ii] = 0;
        }
    }
}

void update()
{
    //findControllers();
    SDL_SetRenderDrawBlendMode(gb_win->ren, SDL_BlendMode::SDL_BLENDMODE_BLEND);
    for (int i = 0; i < 3; i++) {
        mylastbut[i] = mybut[i];
    }
    for (int i = 0; i < controllers.size(); i++) {
        for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ii++) {
            mylastjoybut[i][ii] = myjoybut[i][ii];
            myjoybut[i][ii] = SDL_GameControllerGetButton(controllers[i], (SDL_GameControllerButton)ii);
        }
    }

    while (SDL_PollEvent(&gb_win->ev) != 0) {
        if (gb_win->ev.type == SDL_QUIT)
            gb_win->running = 0;
        switch (gb_win->ev.button.button) {
            case SDL_BUTTON_LEFT:
                mybut[1] = gb_win->ev.button.type == SDL_MOUSEBUTTONDOWN;
                break;
            case SDL_BUTTON_MIDDLE:
                mybut[2] = gb_win->ev.button.type == SDL_MOUSEBUTTONDOWN;
                break;
            case SDL_BUTTON_RIGHT:
                mybut[3] = gb_win->ev.button.type == SDL_MOUSEBUTTONDOWN;
                break;
        }
    }
    current_time=SDL_GetTicks();
    SDL_GetMouseState(&mouse::x, &mouse::y);
}
int running(void) { update(); return gb_win->running; }

/**
 * returns  string with all of the ds_list data separated with sep
 **/
gb_str list::get_string(std::vector<__gblist> list, gb_str sep)
{
    gb_str tempstr;
    for (int i = 0; i < list.size(); i++) {
        tempstr += list[i].data + sep;
    }
    return tempstr;
}

/**
 * sets window width and height
 **/
void window::size(int w, int h)
{
    SDL_SetWindowSize(gb_win->win, w, h);
    gb_win->w = w;
    gb_win->h = h;
}
/**
 * sets window position (x and y)
 **/
void window::pos(int x, int y)
{
    SDL_SetWindowPosition(gb_win->win, x, y);
    gb_win->x = x;
    gb_win->y = y;
}
/**
 * returns window x
 **/
int window::get_x() { return gb_win->x; }
/**
 * returns window y
 **/
int window::get_y() { return gb_win->y; }
/**
 * returns window width
 **/
int window::get_width() { return gb_win->w; }
/**
 * returns window height
 **/
int window::get_height() { return gb_win->h; }

/**
 * returns window size as a struct {w,h} that can be used somewhere
 **/
SDL_Point window::get_size() { return (SDL_Point) { gb_win->w, gb_win->h }; }

void graphics::draw::blendmode(SDL_BlendMode mode) { SDL_SetRenderDrawBlendMode(gb_win->ren, mode); }

/**
 * updates screen
 **/
void screen::draw(double fps)
{
    SDL_RenderPresent(gb_win->ren);
    SDL_Delay(1000.f / fps);
}

GBFont* font::add(gb_str fname, int size)
{
    GBFont* fn = new GBFont;
    fn->font = TTF_OpenFont(fname.c_str(), size);
    fn->size = size;
    gb_fonts.resize(gb_fonts.size() + 1);
    gb_fonts[gb_fonts.size() - 1] = fn;
    return fn;
}
void font::destroy(GBFont* font)
{
    TTF_CloseFont(font->font);
    font->size = 0;
    delete font;
}

void shutdown()
{
    for (int i = 0; i < gb_objects.size(); i++) {
        delete[] gb_objects[i];
    }
    for (int i = 0; i < gb_sprites.size(); i++) {
        graphics::sprite::destroy(gb_sprites[i]);
    }
    for (int i = 0; i < gb_sounds.size(); i++) {
        sound::destroy(gb_sounds[i]);
    }
    for (int i = 0; i < gb_fonts.size(); i++) {
        font::destroy(gb_fonts[i]);
    }

    gb_objects.clear();
    gb_sounds.clear();
    gb_sprites.clear();
    gb_fonts.clear();
}

/**
 * returns true (1) if file/directory exists, otherwise return false (0)
 **/
int fs::exists(std::string fname)
{
    return std::filesystem::exists(fname);
}

SDL_Renderer* window::get_renderer() { return gb_win->ren; }

/**
 * returns ds_list that contains all the files in directory found with filter and mask
 * \sa directory - directory
 * \sa filter - thing like "*.ogg;*.wav" or "*.* .fla"
 * \sa mask - fa::*
 **/
ds_list fs::find::list(gb_str directory, gb_str filter, Uint32 mask)
{
    ds_list list;

    int i_path=mask&fa::fullpath,
        i_dir=mask&fa::dir,
        i_hidden=mask&fa::hidden,
        i_sysfile=mask&fa::sysfile;

    struct dirent* d = nullptr;
    DIR* dir = opendir(directory.c_str());

    char* mytempdir = (char*)malloc(2 * sizeof(char));
    directory.copy(mytempdir, 1, directory.length() - 1);
    std::string mynewdir = mytempdir;
    delete[] mytempdir;

    if (mynewdir.compare("/") != 0)
        mynewdir = directory + "/";

    while ((d = readdir(dir)) != nullptr) {
        std::filesystem::path temp = d->d_name;
        if(temp.compare(".") != 0 && temp.compare("..") != 0) {
            if((d->d_type==DT_REG&&!i_dir)) {
                if(directory.find_last_of(filter)!=std::string::npos) {
                    list.resize(list.size()+1);
                    list[list.size()-1].type=d->d_type;
                    list[list.size()-1].data=i_path ? mynewdir+d->d_name : d->d_name;
                }
            }
            if(d->d_type==DT_DIR&&i_dir) {
                list.resize(list.size()+1);
                list[list.size()-1].type=d->d_type;
                list[list.size()-1].data=i_path ? mynewdir+d->d_name : d->d_name;
            }
        }
    }
    closedir(dir);
    delete[] d;
    return list;
}

/**
 * returns new sound that was added from fname and type (unused)
 */
GBMusic* music::add(std::string fname, int type)
{
    GBMusic* mus = new GBMusic;
    mus->pos = 0;
    mus->vol = 1 * master_vol;
    mus->type = type;
    mus->x = 0;
    mus->y = 0;
    mus->pan = 0;
    mus->chunk = Mix_LoadMUS(fname.c_str());
    if(mus->chunk==nullptr) __error_write("At function music::add:\nCan't load file with name "+fname);
    mus->tag[0]=Mix_GetMusicArtistTag(mus->chunk);
    mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
    mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
    mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
    curmusic = mus;
    return mus;
}

void music::get_tags(GBMusic *mus) {
    mus->tag[0]=Mix_GetMusicArtistTag(mus->chunk);
    mus->tag[1]=Mix_GetMusicTitle(mus->chunk);
    mus->tag[2]=Mix_GetMusicAlbumTag(mus->chunk);
    mus->tag[3]=Mix_GetMusicCopyrightTag(mus->chunk);
}

/**
 * set sound pos
 **/

void music::set_pos(GBMusic* snd, double pos)
{
    snd->pos = pos;
    Mix_SetMusicPosition(snd->pos);
}

/**
 * play sound
 * \sa snd - sound
 **/
void music::play(GBMusic* snd) { Mix_PlayMusic(snd->chunk, 0); }
/**
 * play sound looped
 * \sa snd - sound
 * \sa loops - how many times the sound should be repeated
 **/
void music::loop(GBMusic* snd, int loops) { Mix_PlayMusic(snd->chunk, loops); }
/**
 * pauses the sound
 * \sa snd - sound
 **/
void music::pause(GBMusic* snd) { Mix_PauseMusic(); }
/**
 * stops the sound entirely
 * \sa snd - sound
 **/
void music::stop(GBMusic* snd) { Mix_HaltMusic(); }
/**
 * sets the volume of a sound
 * \sa snd - sound
 * \sa vol - volume
 **/
void music::set_vol(GBMusic* snd, double vol) { Mix_VolumeMusic(vol * 128); }
/**
 * destroy sound if it will not be used anymore
 * \sa snd - sound
 **/
void music::destroy(GBMusic* snd)
{
    snd->x = 0;
    snd->y = 0;
    Mix_FreeMusic(snd->chunk);
    snd->pan = 0;
    snd->pos = 0;
    snd->type = 0;
    snd->vol = 0;
    delete snd;
}

/**
 * returns new sound that was added from fname and type (unused)
 */
GBSound* sound::add(std::string fname, int type)
{
    if (!fs::exists(fname)) {
        graphics::message("FATAL ERROR", "At sound::add:\nFile doesn't exist: \"" + fname + "\".");
        exit(0x0010010);
        return nullptr;
    }
    GBSound* snd = new GBSound;
    snd->pos = 0;
    snd->vol = 1 * master_vol;
    snd->type = type;
    snd->x = 0;
    snd->y = 0;
    snd->pan = 0;
    snd->chunk = Mix_LoadWAV(fname.c_str());
    gb_sounds.resize(gb_sounds.size() + 1);
    gb_sounds[gb_sounds.size() - 1] = snd;
    return snd;
}
/**
 * set sound pos (unused for a while)
 **/

void sound::set_pos(GBSound* snd, double pos)
{
    snd->pos = pos;
    // Mix_SetMusicPosition(snd->pos);
}
int sound::get_wave(GBSound* snd, int pos)
{
    int h = snd->chunk->abuf[pos];

    return h;
}

/**
 * play sound
 * \sa snd - sound
 **/
void sound::play(GBSound* snd) { snd->channel = Mix_PlayChannel(-1, snd->chunk, 0); }
/**
 * play sound looped
 * \sa snd - sound
 * \sa loops - how many times the sound should be repeated
 **/
void sound::loop(GBSound* snd, int loops) { snd->channel = Mix_PlayChannel(-1, snd->chunk, loops); }
/**
 * pauses the sound
 * \sa snd - sound
 **/
void sound::pause(GBSound* snd) { Mix_Pause(snd->channel); }
/**
 * stops the sound entirely
 * \sa snd - sound
 **/
void sound::stop(GBSound* snd) { Mix_HaltChannel(snd->channel); }
/**
 * sets the volume of a sound
 * \sa snd - sound
 * \sa vol - volume
 **/
void sound::set_vol(GBSound* snd, double vol) { Mix_Volume(snd->channel, vol * 128); }
/**
 * destroy sound if it will not be used anymore
 * \sa snd - sound
 **/
void sound::destroy(GBSound* snd)
{
    snd->x = 0;
    snd->y = 0;
    Mix_FreeChunk(snd->chunk);
    snd->pan = 0;
    snd->pos = 0;
    snd->type = 0;
    snd->vol = 0;
    delete snd;
}

int fs::text::open(gb_str fname, int mode) {
    _gm_file *f=new _gm_file;
    std::string md=(mode==fs::fmode::read)?"r":(mode==fs::fmode::append)?"a":"w";
    f->file=fopen(fname.c_str(),md.c_str());
    f->mode=mode;
    gb_files.resize(gb_files.size()+1);
    gb_files[gb_files.size()-1]=f;
    return gb_files.size()-1;
}

void fs::text::write(int file,gb_str str) {
    fprintf(gb_files[file]->file,"%s", str.c_str());
}

void fs::text::close(int file) {
    fclose(gb_files[file]->file);
    gb_files[file]->file=nullptr;
    gb_files[file]->mode=0;
    delete[] gb_files[file];
    gb_files.erase(gb_files.begin() + file);
}

/**
 * returns new object
 * \sa spr - sprite, can be passed as nullptr
 * \sa mask - mask of the object, if passed as nullptr, the mask will be the same as the sprite
 * \sa x, y - coordinates of the object
 **/
GBObject* object::add(GBSprite* spr, GBSprite* mask, double x, double y)
{
    GBObject* obj = new GBObject;
    obj->spr = spr;
    obj->mask = mask != nullptr ? mask : spr;
    obj->x = x;
    obj->y = y;
    obj->direction = 0;
    obj->gravity_direction = 270;
    obj->gravity = 0;
    obj->xprevious = 0;
    obj->yprevious = 0;
    gb_objects.resize(gb_objects.size() + 1);
    gb_objects[gb_objects.size() - 1] = obj;
    return obj;
}
/**
 * show a message box with title and message
 * \sa title - message box title
 * \sa msg - message box message
 **/
void graphics::message(std::string title, std::string msg)
{
    SDL_ShowSimpleMessageBox(0, title.c_str(), msg.c_str(), gb_win->win);
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
        graphics::message("FATAL ERROR", "At graphics::sprite::add:\nFile doesn't exist: \"" + fname + "\".");
        exit(0x0010010);
        return nullptr;
    }
    GBSprite* spr = new GBSprite;
    spr->frames = (frames < 1) ? 1 : frames;
    SDL_Surface* temp = IMG_Load(fname.c_str());
    spr->tex = SDL_CreateTextureFromSurface(gb_win->ren, temp);
    spr->w = temp->w;
    spr->h = temp->h;
    SDL_FreeSurface(temp);
    gb_sprites.resize(gb_sprites.size() + 1);
    gb_sprites[gb_sprites.size() - 1] = spr;
    return spr;
}

void graphics::draw::text(float x, float y, GBText* text)
{
    SDL_Rect myrect = { 0, 0, text->surf->w, text->surf->h };
    SDL_FRect extrect = { x - (float)_gm_halign * text->surf->w, y - (float)_gm_valign * text->surf->h, (float)text->surf->w, (float)text->surf->h };
    SDL_SetTextureColorMod(text->tex,_realcol_.r,_realcol_.g,_realcol_.b);
    SDL_RenderCopyF(gb_win->ren, text->tex, &myrect, &extrect);
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
}
/**
 * draw a sprite on screen
 * \sa spr - sprite
 * \sa frame - sprite frame
 * \sa x,y - coordinates where the sprite should be drawn
 * \sa xscale, yscale - image scale (spr->w*xscale, spr->h*yscale)
 * \sa rot - rotate by 0-360 degrees
 **/
void graphics::draw::sprite(GBSprite* spr, int frame, int x, int y, int xscale, int yscale, int rot)
{
    SDL_Rect rect = { (spr->w / spr->frames) * (frame % spr->frames), 0, (spr->w / spr->frames) * ((frame % spr->frames) + 1), spr->h };
    SDL_FRect dstrect = { (float)x, (float)y, ((float)spr->w / spr->frames) * xscale, (float)spr->h * yscale };
    SDL_FPoint cen = { (float)spr->offx, (float)spr->offy };
    SDL_SetTextureColorMod(spr->tex,_realcol_.r,_realcol_.g,_realcol_.b);
    SDL_RenderCopyExF(gb_win->ren, spr->tex, &rect, &dstrect, rot, &cen, SDL_FLIP_NONE);
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
void graphics::draw::sprite_ext(GBSprite* spr, int frame, int x, int y, int xscale, int yscale, int rot,SDL_Color col)
{
    graphics::draw::color_sdl(col);
    SDL_Rect rect = { (spr->w / spr->frames) * (frame % spr->frames), 0, (spr->w / spr->frames) * ((frame % spr->frames) + 1), spr->h };
    SDL_FRect dstrect = { (float)x, (float)y, ((float)spr->w / spr->frames) * xscale, (float)spr->h * yscale };
    SDL_FPoint cen = { (float)spr->offx, (float)spr->offy };
    SDL_SetTextureColorMod(spr->tex,col.r,col.g,col.b);
    SDL_RenderCopyExF(gb_win->ren, spr->tex, &rect, &dstrect, rot, &cen, SDL_FLIP_NONE);
}

/**
 * draws a rectangle
 * \sa x,y - coordinates where the rectanggle should be drawn
 * \sa w,h - size of the rectangle
 * \sa outline - if true, the rectangle will be drawn outlined only, otherwise rectangle will be filled
 **/
void graphics::draw::rect(int x, int y, int w, int h, int outline)
{
    SDL_Rect myrect = { x, y, w, h };
    if (outline == 0)
        SDL_RenderFillRect(gb_win->ren, &myrect);
    else
        SDL_RenderDrawRect(gb_win->ren, &myrect);
}

gb_str fs::path_parent(gb_str path) {
    std::filesystem::path mypath=path;
    return mypath.parent_path();
}

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
    const std::vector<SDL_Vertex> verts = {
        {
            SDL_FPoint { x1, y1 },
            SDL_Color { col1.r, col1.g, col1.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x2, y2 },
            SDL_Color { col2.r, col2.g, col2.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x3, y3 },
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
    curfon=fnt;
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
    if (outline)
        SDL_RenderDrawCircle(gb_win->ren, x, y, r);
    else
        SDL_RenderFillCircle(gb_win->ren, x, y, r);
}
/**
 * draws a line
 * \sa x1,y1 - first point
 * \sa x2,y2 - second point
 **/
void graphics::draw::line(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(gb_win->ren, x1, y1, x2, y2);
}
/**
 * draws a point
 * \sa x,y - point coordinates
 **/
void graphics::draw::point(int x, int y)
{
    SDL_RenderDrawPoint(gb_win->ren, x, y);
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

SDL_Color color::black = { 0, 0, 0, 255 },
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

/**
 * check if mouse button was pressed
 * \sa mouse_button - mb::*
 **/
int mouse::pressed(mb mouse_button)
{
    return mybut[mouse_button] && !mylastbut[mouse_button];
}
/**
 * check if mouse button was released
 * \sa mouse_button - mb::*
 **/
int mouse::released(mb mouse_button)
{
    return !mybut[mouse_button] && mylastbut[mouse_button];
}
/**
 * check if mouse button is holding
 * \sa mouse_button - mb::*
 **/
int mouse::holding(mb mouse_button)
{
    return mybut[mouse_button] && mylastbut[mouse_button];
}

/**
 * convert degrees to radians or opposite
 * \sa deg - degree/radian
 **/
double math::degtorad(double deg)
{
    return deg * M_PI / 180;
}
/**
 * returns a length with given direction for x
 * \sa len - length
 * \sa dir - direction
 **/
double math::lendir_x(double len, int dir)
{
    return cos(degtorad(dir)) * len;
}
/**
 * returns a length with given direction for y
 * \sa len - length
 * \sa dir - direction
 **/
double math::lendir_y(double len, int dir)
{
    return sin(degtorad(dir)) * len;
}
/**
 * clamps a value between two others
 * \sa val - value that should be clamped
 * \sa minval - minimum value
 * \sa maxval - maximum value
 * \sa if val < minval return minval, else if val>maxval return maxval, else return val
 **/
double math::clamp(double val, double minval, double maxval)
{
    return val < minval ? minval : val > maxval ? maxval
                                                : val;
} // uhhhh

/**
 * returns true if point is in rectangle
 * \sa px, py - point coordinates
 * \sa rx*, ry* - x/y of rectangle
 **/
double math::point_in_rect(double px, double py, double rx1, double ry1, double rx2, double ry2)
{
    return px > rx1 && py > ry1 && px <= rx2 && py <= ry2;
}
};
