#include "gm.hpp"
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <filesystem>

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

std::vector<SDL_GameController *>controllers;

void findControllers()
{
    int ii=0;
    controllers.resize(SDL_NumJoysticks());
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            controllers[ii]=SDL_GameControllerOpen(i);
            ii++;
        }
    }
}

int joy_count=0;

namespace GameMaker {
double master_vol = 1;
std::vector<GMSound*> gm_sounds;
std::vector<GMSprite*> gm_sprites;
GMWindow* gm_win;

int joy::count() {
    joy_count=SDL_NumJoysticks();

    return joy_count;
}
int joy::button_pressed(int joy, int button) {return myjoybut[joy][button]&&!mylastjoybut[joy][button];}
int joy::button_released(int joy, int button) {return !myjoybut[joy][button]&&mylastjoybut[joy][button];}
int joy::button_holding(int joy, int button) {return myjoybut[joy][button]&&mylastjoybut[joy][button];}

int init(int x, int y, int w, int h, std::string label)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OPUS | MIX_INIT_WAVPACK | MIX_INIT_MP3);
    IMG_Init(IMG_INIT_WEBP | IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    gm_win = new GMWindow;
    gm_win->win = SDL_CreateWindow(label.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
    gm_win->ren = SDL_CreateRenderer(gm_win->win, -1, SDL_RENDERER_ACCELERATED);
    gm_win->x = x;
    gm_win->y = y;
    gm_win->w = w;
    gm_win->h = h;
    gm_win->running = 1;
    for (int i = 0; i < 3; i++) {
        mybut[i] = 0;
        mylastbut[i] = 0;
    }
    for(int i=0;i<joy::count();i++) {
        for(int ii=0;ii<SDL_CONTROLLER_BUTTON_MAX;ii++) {
            myjoybut[i][ii]=0;
            mylastjoybut[i][ii]=0;
        }
    }

    return 1;
}
int running(void) { return gm_win->running; }
void update()
{
    findControllers();
    for (int i = 0; i < 3; i++) {
        mylastbut[i] = mybut[i];
    }
    for(int i=0;i<controllers.size();i++) {
        for(int ii=0;ii<SDL_CONTROLLER_BUTTON_MAX;ii++) {
            mylastjoybut[i][ii]=myjoybut[i][ii];
            myjoybut[i][ii]=SDL_GameControllerGetButton(controllers[i],(SDL_GameControllerButton)i);
        }
    }

    while (SDL_PollEvent(&gm_win->ev) != 0) {
        if (gm_win->ev.type == SDL_QUIT)
            gm_win->running = 0;
        switch (gm_win->ev.button.button) {
        case SDL_BUTTON_LEFT:
            mybut[1] = gm_win->ev.button.type == SDL_MOUSEBUTTONDOWN;
            break;
        case SDL_BUTTON_MIDDLE:
            mybut[2] = gm_win->ev.button.type == SDL_MOUSEBUTTONDOWN;
            break;
        case SDL_BUTTON_RIGHT:
            mybut[3] = gm_win->ev.button.type == SDL_MOUSEBUTTONDOWN;
            break;
        }
    }
}

void window::size(int w, int h)
{
    SDL_SetWindowSize(gm_win->win, w, h);
    gm_win->w = w;
    gm_win->h = h;
}
void window::pos(int x, int y)
{
    SDL_SetWindowPosition(gm_win->win, x, y);
    gm_win->x = x;
    gm_win->y = y;
}
int window::get_x() { return gm_win->x; }
int window::get_y() { return gm_win->y; }
int window::get_width() { return gm_win->w; }
int window::get_height() { return gm_win->h; }

void screen::draw(double fps)
{
    SDL_RenderPresent(gm_win->ren);
    SDL_Delay(1000.f / fps);
}
int fs::exists(std::string fname)
{
    return std::filesystem::exists(fname);
}
GMSound* sound::add(std::string fname, int type)
{
    if (!fs::exists(fname)) {
        graphics::message("FATAL ERROR","At sound::add:\nFile doesn't exist: \""+fname+"\".");
        exit(0x0010010);
        return nullptr;
    }
    GMSound* snd = new GMSound;
    snd->pos = 0;
    snd->vol = 1 * master_vol;
    snd->type = type;
    snd->x = 0;
    snd->y = 0;
    snd->pan = 0;
    snd->chunk = Mix_LoadWAV(fname.c_str());
    gm_sounds.resize(gm_sounds.size() + 1);
    gm_sounds[gm_sounds.size() - 1] = snd;
    return snd;
}
void sound::set_pos(GMSound* snd, double pos)
{
    snd->pos = pos;
    //Mix_SetMusicPosition(snd->pos);
}

void sound::play(GMSound *snd) {Mix_PlayChannel(-1,snd->chunk,0);}
void sound::loop(GMSound *snd, int loops) {snd->channel=Mix_PlayChannel(-1,snd->chunk,loops);}
void sound::pause(GMSound *snd) {Mix_Pause(snd->channel);}
void sound::stop(GMSound *snd) {Mix_HaltChannel(snd->channel);}
void sound::set_vol(GMSound *snd, double vol) {Mix_Volume(snd->channel,vol*128);}
void sound::destroy(GMSound* snd)
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

void graphics::message(std::string title, std::string msg)
{
    SDL_ShowSimpleMessageBox(0, title.c_str(), msg.c_str(), gm_win->win);
}

GMSprite* graphics::sprite::add(std::string fname, int frames, int offx, int offy)
{
    if (!fs::exists(fname)) {
        graphics::message("FATAL ERROR","At graphics::sprite::add:\nFile doesn't exist: \""+fname+"\".");
        exit(0x0010010);
        return nullptr;
    }
    GMSprite* spr = new GMSprite;
    spr->frames = (frames < 1) ? 1 : frames;
    SDL_Surface* temp = IMG_Load(fname.c_str());
    spr->tex = SDL_CreateTextureFromSurface(gm_win->ren, temp);
    spr->w = temp->w;
    spr->h = temp->h;
    SDL_FreeSurface(temp);
    gm_sprites.resize(gm_sprites.size() + 1);
    gm_sprites[gm_sprites.size() - 1] = spr;
    return spr;
}
void graphics::sprite::destroy(GMSprite* spr)
{
    spr->frames = 0;
    spr->h = 0;
    spr->offx = 0;
    spr->offy = 0;
    spr->w = 0;
    SDL_DestroyTexture(spr->tex);
    delete spr;
}

void graphics::draw::sprite(GMSprite* spr, int frame, int x, int y, int xscale, int yscale, int rot)
{
    SDL_Rect rect = { (spr->w / spr->frames) * (frame % spr->frames), 0, (spr->w / spr->frames) * ((frame % spr->frames) + 1), spr->h };
    SDL_FRect dstrect = { (float)x, (float)y, ((float)spr->w / spr->frames) * xscale, (float)spr->h * yscale };
    SDL_FPoint cen = { (float)spr->offx, (float)spr->offy };
    SDL_RenderCopyExF(gm_win->ren, spr->tex, &rect, &dstrect, rot, &cen, SDL_FLIP_NONE);
}

void graphics::draw::rect(int x, int y, int w, int h, int outline)
{
    SDL_Rect myrect = { x, y, w, h };
    if (outline == 0)
        SDL_RenderFillRect(gm_win->ren, &myrect);
    else
        SDL_RenderDrawRect(gm_win->ren, &myrect);
}

int graphics::draw::rect_color(float x, float y, float w, float h, SDL_Color col1, SDL_Color col2, SDL_Color col3, SDL_Color col4, int outline)
{
    const std::vector<SDL_Vertex> verts = {
        {
            SDL_FPoint { x, y },
            SDL_Color { col1.r, col1.g, col1.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x+w, y },
            SDL_Color { col2.r, col2.g, col2.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x+w, y+h },
            SDL_Color { col3.r, col3.g, col3.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x+w, y+h },
            SDL_Color { col3.r, col3.g, col3.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x, y+h },
            SDL_Color { col4.r, col4.g, col4.b, 255 },
            SDL_FPoint { 0 },
        },
        {
            SDL_FPoint { x, y },
            SDL_Color { col1.r, col1.g, col1.b, 255 },
            SDL_FPoint { 0 },
        },
    };
    return SDL_RenderGeometry(gm_win->ren, nullptr, verts.data(), verts.size(), nullptr, 0);
}

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
    SDL_RenderGeometry(gm_win->ren, nullptr, verts.data(), verts.size(), nullptr, 0);
}
void graphics::draw::color(Uint32 color)
{
    SDL_SetRenderDrawColor(gm_win->ren, (color >> 8) & 0xFF, (color >> 4) & 0xFF, color & 0xFF, 255);
}
void graphics::draw::circle(int x, int y, int r, int outline)
{
    if (outline)
        SDL_RenderDrawCircle(gm_win->ren, x, y, r);
    else
        SDL_RenderFillCircle(gm_win->ren, x, y, r);
}
void graphics::draw::line(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(gm_win->ren, x1, y1, x2, y2);
}
void graphics::draw::point(int x, int y)
{
    SDL_RenderDrawPoint(gm_win->ren, x, y);
}
void graphics::draw::color_sdl(SDL_Color color)
{
    SDL_SetRenderDrawColor(gm_win->ren, color.r, color.g, color.b, color.a);
}

SDL_Color color::black = { 0, 0, 0 },
          color::white = { 255, 255, 255 },
          color::red = { 255, 0, 0 },
          color::blue = { 0, 0, 255 },
          color::green = { 0, 200, 0 },
          color::lime = { 0, 255, 50 };

int mouse::pressed(mb mouse_button)
{
    return mybut[mouse_button] && !mylastbut[mouse_button];
}
int mouse::released(mb mouse_button)
{
    return !mybut[mouse_button] && mylastbut[mouse_button];
}
int mouse::holding(mb mouse_button)
{
    return mybut[mouse_button] && mylastbut[mouse_button];
}

double math::degtorad(double deg)
{
    return deg * M_PI / 180;
}
double math::lendir_x(double len, int dir)
{
    return cos(degtorad(dir)) * len;
}
double math::lendir_y(double len, int dir)
{
    return sin(degtorad(dir)) * len;
}
double math::clamp(double val, double minval, double maxval)
{
    return val < minval ? minval : val > maxval ? maxval
                                                : val;
} // uhhhh
double math::point_in_rect(double px, double py, double rx1, double ry1, double rx2, double ry2)
{
    return px > rx1 && py > ry1 && px <= rx2 && py <= ry2;
}
};
