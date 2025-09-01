#include <gtk/gtk.h>
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

    int show::popover_menu(gb_str file) {
    	gtk_init(nullptr,nullptr);
		int clicked=-1;
		GtkBuilder *builder=gtk_builder_new();
		gtk_builder_add_from_file(builder,file.c_str(),NULL);
		
		GtkWidget *mymenu=GTK_WIDGET(gtk_builder_get_object(builder,"popover"));
		g_signal_connect(mymenu,"destroy",G_CALLBACK(gtk_main_quit),NULL);
		gtk_builder_connect_signals(builder, NULL);

		gtk_widget_show_all(mymenu);
		gtk_main();
    	return clicked;
    }
}
