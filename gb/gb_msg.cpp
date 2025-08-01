#include "../include/gamebreaker.hpp"

namespace GameBreaker {

    /**
    * show a message box with title and message
    * \sa title - message box title
    * \sa msg - message box message
    **/
    void show::message(std::string title, std::string msg)
    {
        SDL_ShowSimpleMessageBox(0, title.c_str(), msg.c_str(), gb_win->win);
    }

    void show::error(gb_str msg, int abort) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR", msg.c_str(), gb_win->win);
        if(abort) {
            printf("ERROR: %s\nExit code: 0xC01001\n",msg.c_str());
            exit(0xc01001);
        }
    }
}