#define GB_USE_SMALL_FUNCNAMES
#include "../../gb/gamebreaker.hpp"
namespace gb=GameBreaker;


int main() {

    gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,320,240,"File catalog");

    ds_list myfiles;
    std::vector<str> _myfilter={"*.*"};
    str dafolda=file::get_folder("Choose a folder to get files from...");
    
    myfiles=file::find::list_ext(dafolda, _myfilter, file::fa::hidden|file::fa::dir);
    
    show::message("Your files", "Files from "+dafolda+":\n"+gb::list::get_string(myfiles,"\n"));

    gb::shutdown();
    return 0;
}