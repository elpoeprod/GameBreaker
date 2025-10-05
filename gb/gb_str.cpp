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
        auto tempt=text;
        auto mypos=0;
        for(int __i=0;__i<gstr::count(tempt,in);__i++) {
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
        int i=0;repeat(str.length()) {
            ret+=tolower(str[i]);
            i++;
        }
        return ret;
    }

    gb_str gstr::uppercase(gb_str str) {
        gb_str ret;
        int i=0;repeat(str.length()) {
            ret+=toupper(str[i]);
            i++;
        }
        return ret;
    }
    
	gb_str gstr::char_at(gb_str str, int pos) {
		return ""+str.at(pos);
	}

	int gstr::ord_at(gb_str str, int pos) {
		return (int)str.at(pos);
	}

    int gstr::length(gb_str str) {
        return str.length(); // stupid but maybe needed
    }

    int gstr::pos(gb_str substr, gb_str str) {
        static int pos;
        pos+=str.find(substr,pos);
        return pos;
    }

    gb_str gstr::copy(gb_str str, int pos, int len) {
        if(len<1) return "";
        gb_str mystr;
        for(int i=0;i<len;i++) {
            mystr+=str[pos+i];
        }
        return mystr;
    }
    gb_str gstr::del(gb_str str, int pos, int len) {
        if(len<1) return str;
        gb_str mystr=gstr::copy(str,0,pos);
        mystr+=gstr::copy(str,pos+len,str.length()-(pos+len));
        return mystr;
    }

    gb_str gstr::insert(gb_str str, gb_str substr, int pos) {
        if(substr=="") return str;
        gb_str mystr=gstr::copy(str,0,pos);
        mystr+=substr;
        mystr+=gstr::copy(str,pos+substr.length(),str.length()-(pos+substr.length()));
        return mystr;
    }

    gb_str gstr::duplicate(gb_str str, int count) {
        gb_str mystr;
        for(int i=0;i<count;i++) {
            mystr+=str;
        }
        return mystr;
    }
    
    gb_str gstr::format(int num, int tot, int dec) {
    	gb_str mynumstr=stringify(num);
    	return gstr::duplicate("0",tot-mynumstr.length()-1)+mynumstr+((dec>0) ? "."+gstr::duplicate("0",dec) : "");
    }

   	gb_str gstr::pad(int num, int padding) {
   		str nnnnum=stringify(num);
   		return gstr::duplicate("-",num<0)+gstr::duplicate("0",padding-nnnnum.length())+gstr::format(math::abs(num),padding,0);
   	}
   	
   	gb_str gstr::file_ext(gb_str fname) {
   		auto ppos=fname.find_last_of(".");
   		return gstr::copy(fname,ppos,fname.length()-ppos);
   	}
    
}
