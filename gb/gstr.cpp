#include "../include/gamebreaker.hpp"
#include <cctype>
#include <clocale>
#include <filesystem>
/*
* GAMEBREAKER::STRINGS
*/

namespace GameBreaker {

    int gstr::count(str text, str n) {
        int _count=0;
        for(long unsigned int __l=0;__l<(int)text.length()-n.length()+1;__l++) {
            str tempstr="";
            for(int __h=0;__h<(int)n.length();__h++) {
                tempstr+=text[__l+__h];
            }
            if(tempstr==n) _count+=1;
        }
        return _count;
    }
    
    str gstr::replace(str text, str in, str out) {
        return text.replace(text.find_first_of(in),in.length(),out.c_str());
    }
    
    str gstr::replace_all(str text, str in, str out) {
        auto tempt=text;
        auto mypos=0;
        for(int __i=0;__i<gstr::count(tempt,in);__i++) {
            tempt=tempt.replace(tempt.find_first_of(in,mypos),in.length(),out);
            mypos+=out.length();
        }
        return tempt;
    }
    str gstr::cat(std::vector<void *>args) {
        str mystr="";
        for(int __i=0;__i<(int)args.size();__i++) {
            str *temp=static_cast<str *>(args[__i]);
            mystr+=*temp;
            delete temp;
        }
        return mystr;
    }

    str gstr::shorten(str fname) { // shortens filename to FILENA~1.* if fname length is more than 8. otherwise return fname
        std::filesystem::path _temp_fn=fname;
        str fe=_temp_fn.extension();
        str fn=_temp_fn.filename();
        str ret;
        if(fn.length()>8) {
            for(int i=0;i<6;i++) {
                ret+=fn[i];
            }
            ret+="~1";
        }
        return ret+fe;
    }
    
    str gstr::lowercase(str text) {
        str ret;
        int i=0;repeat(text.length()) {
            ret+=tolower(text[i]);
            i++;
        }
        return ret;
    }

    str gstr::uppercase(str text) {
        str ret;
        int i=0;repeat(text.length()) {
            ret+=toupper(text[i]);
            i++;
        }
        return ret;
    }
    
	str gstr::char_at(str text, int pos) {
		return ""+text.at(pos);	//dangerous
	}

	int gstr::ord_at(str text, int pos) {
		return (int)text.at(pos);
	}

    int gstr::length(str text) {
        return text.length(); // stupid but maybe needed
    }

    int gstr::pos(str substr, str text) {
        static int pos;
        pos=text.find(substr,pos);
        return pos;
    }

    str gstr::copy(str text, int pos, int len) {
        if(len<1) return "";
        str mystr;
        for(int i=0;i<len;i++) {
            mystr+=text[pos+i];
        }
        return mystr;
    }
    str gstr::del(str text, int pos, int len) {
        if(len<1) return text;
        str mystr=gstr::copy(text,0,pos);
        mystr+=gstr::copy(text,pos+len,text.length()-(pos+len));
        return mystr;
    }

    str gstr::insert(str text, str substr, int pos) {
        if(substr=="") return text;
        str mystr=gstr::copy(text,0,pos);
        mystr+=substr;
        mystr+=gstr::copy(text,pos+substr.length(),text.length()-(pos+substr.length()));
        return mystr;
    }

    str gstr::duplicate(str text, int count) {
        str mystr;
        for(int i=0;i<count;i++) {
            mystr+=text;
        }
        return mystr;
    }
    
    str gstr::format(int num, int tot, int dec) {
    	str mynumstr=stringify(num);
    	return gstr::duplicate("0",tot-mynumstr.length()-1)+mynumstr+((dec>0) ? "."+gstr::duplicate("0",dec) : "");
    }

   	str gstr::pad(int num, int padding) {
   		str nnnnum=stringify(num);
   		return gstr::duplicate("-",num<0)+gstr::duplicate("0",padding-nnnnum.length())+gstr::format(math::abs(num),padding,0);
   	}
   	
   	str gstr::file_ext(str fname) {
   		auto ppos=fname.find_last_of(".");
   		return gstr::copy(fname,ppos,fname.length()-ppos);
   	}

   	str gstr::chr(int val) {
   		return ""+(char)val;
   	}

   	int gstr::ord(str chr) {
   		return (int)chr.at(0);
   	}




   	int clipboard::has_text() {
   		return gstr::length(GetClipboardText())>0;
   	}
   	
   	void clipboard::set_text(str text) {
		SetClipboardText(text.c_str());
   		return;
   	}

   	str clipboard::get_text() {
   		return GetClipboardText();
   	}
    
}
