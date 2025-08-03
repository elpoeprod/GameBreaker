#include "../include/gamebreaker.hpp"
#include <SDL2/SDL_ttf.h>
#include <cctype>
#include <clocale>
#include <filesystem>
/*
* GAMEBREAKER::STRINGS
*/

namespace GameBreaker {

    int gstr::count(gb_str text, gb_str n) {
        int _count=0;
        for(long unsigned int __l=0;__l<(int)text.length()-n.length()+1;__l++) {
            gb_str tempstr="";
            for(int __h=0;__h<(int)n.length();__h++) {
                tempstr+=text[__l+__h];
            }
            if(tempstr==n) _count+=1;
        }
        return _count;
    }
    
    gb_str gstr::replace(gb_str text, gb_str in, gb_str out) {
        return text.replace(text.find_first_of(in),in.length(),out.c_str());
    }
    
    gb_str gstr::replace_all(gb_str text, gb_str in, gb_str out) {
        var tempt=text;
        var mypos=0;
        for(var __i=0;__i<gstr::count(tempt,in);__i++) {
            tempt=tempt.replace(tempt.find_first_of(in,mypos),in.length(),out);
            mypos+=out.length();
        }
        return tempt;
    }
    gb_str gstr::cat(std::vector<void *>args) {
        gb_str mystr="";
        for(int __i=0;__i<(int)args.size();__i++) {
            gb_str *temp=static_cast<gb_str *>(args[__i]);
            mystr+=*temp;
            delete temp;
        }
        return mystr;
    }

    gb_str gstr::shorten(gb_str fname) { // shortens filename to FILENA~1.* if fname length is more than 8. otherwise return fname
        std::filesystem::path _temp_fn=fname;
        std::string fe=_temp_fn.extension();
        std::string fn=_temp_fn.filename();
        std::string ret;
        if(fn.length()>8) {
            for(int i=0;i<6;i++) {
                ret+=fn[i];
            }
            ret+="~1";
        }
        return ret+fe;
    }
    gb_str gstr::lowercase(gb_str str) {
        gb_str ret;
        var i=0;repeat(str.length()) {
            ret+=tolower(str[i]);
            i++;
        }
        return ret;
    }
    gb_str gstr::uppercase(gb_str str) {
        gb_str ret;
        var i=0;repeat(str.length()) {
            ret+=toupper(str[i]);
            i++;
        }
        return ret;
    }
}
