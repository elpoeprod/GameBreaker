/*
 * Messages, errors, etc functions
 * 2025 elpoep
*/
//#include <gtk/gtk.h>
#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_messagebox.h>

typedef struct _GB_POM_T{
	SDL_MessageBoxData *data;
} _GB_POM_T;

std::vector<_GB_POM_T *> _pom_db_;

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
	int popover::create() {
		SDL_MessageBoxData *mydata=new SDL_MessageBoxData;//{.flags=SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,.window=gb_win->win,.title="PopOverMenu"};
		mydata->title="PopOverMenu";
		mydata->window=gb_win->win;
		mydata->flags=SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT;
		_GB_POM_T *mypom=new _GB_POM_T;
		mypom->data=mydata;
		_pom_db_.push_back(
			mypom
		);
		return _pom_db_.size()-1;
	}
	/* TODO
	int popover::add_entry(int menu_id,gb_str str) {
		const SDL_MessageBoxButtonData mybutdata={.buttonid=_pom_db_[menu_id]->data->numbuttons+1,.text=str.c_str()};
		_pom_db_[menu_id]->data->numbuttons++;
		_pom_db_[menu_id]->data->buttons[_pom_db_[menu_id]->data->numbuttons-1]=mybutdata;
		return mybutdata->buttonid;
	}
	*/
}
