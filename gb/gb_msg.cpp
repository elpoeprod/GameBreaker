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

    int show::popover_menu(GBPOMItems items) {
    	gtk_init(nullptr,nullptr);
		int clicked=-1;
		GtkWidget *button=gtk_button_new_with_label("none");
		GtkWidget* popover = gtk_popover_new(button);
	    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	    for(long unsigned int _i=0;_i<items.size();_i++) {
	    // Add items to the popover
		    GtkWidget* item = gtk_button_new_with_label("Item 1");
		    g_signal_connect(item, "clicked", G_CALLBACK(items[_i].func), NULL);
		    gtk_box_pack_start(GTK_BOX(box), item, TRUE, TRUE, 0);
	    }
	    gtk_container_add(GTK_CONTAINER(popover), box);
	    gtk_widget_show_all(popover);
	    gtk_widget_show(popover);
    	//gtk_main();
    	return clicked;
    }
}
