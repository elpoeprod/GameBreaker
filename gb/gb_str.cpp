#include "gamebreaker.hpp"

/*
* GAMEBREAKER::STRINGS
*/

namespace GameBreaker {

    int gstr::count(gb_str text, gb_str n) {
        int _count=0;
        for(int __l=0;__l<text.length()-n.length()+1;__l++) {
            gb_str tempstr="";
            for(int __h=0;__h<n.length();__h++) {
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
        for(int __i=0;__i<args.size();__i++) {
            gb_str *temp=static_cast<gb_str *>(args[__i]);
            mystr+=*temp;
            delete temp;
        }
        return mystr;
    }
}