#define GB_USE_SMALL_FUNCNAMES
#include "../../gb/gamebreaker.hpp"
namespace gb=GameBreaker;

int main() {

    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,320,240,"File Dialogs test");

    fname_list mytestlist={{"All files",""}};
    while(gb::running()) {
        
        show::message("File dialog","You have chosen this file:\n"+file::get_fname(mytestlist,"Pick a file!"));

        show::message("Folder dialog","You have chosen this folder:\n"+file::get_folder("Choose a folder!"));

        screen::end();
    }
    gb::shutdown();
    return 0;

}