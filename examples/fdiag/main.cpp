#define GB_USE_SMALL_FUNCNAMES
#include <gamebreaker/gamebreaker.hpp>
namespace gb=GameBreaker;



int main() {

    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"File Dialogs test");

    window::set_icon("../gb.png");

    fname_list mytestlist={{"All files",""}};
        
    show::message("File dialog","You have chosen this file:\n"+file::get_fname(mytestlist,"Pick a file!"));

    show::message("Folder dialog","You have chosen this folder:\n"+file::get_folder("Choose a folder!"));

    gb::shutdown();
    return 0;
}
