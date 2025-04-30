#include "gamebreaker.hpp"


namespace GameBreaker {

    /**
    * returns  string with all of the ds_list data separated with sep
    **/
    gb_str list::get_string(ds_list list, gb_str sep)
    {
        gb_str tempstr;
        for (int i = 0; i < list.size(); i++) {
            tempstr += list[i].data + sep;
        }
        return tempstr;
    }
    gb_str list::find::value(ds_list list, int pos) {
        return list[pos].data;
    }
    int list::find::pos(ds_list list, gb_str str) {
        for(int i=0;i<list.size();i++) {
            if(list[i].data==str) return i;
        }
        return -1;
    }
}