#include "../include/gamebreaker.hpp"
#include "../include/inicpp.hpp"

static std::vector<inicpp::IniManager *> __gb_inis;

inicpp::IniManager *retiin(str txt) {
    return new inicpp::IniManager(txt);
}

namespace GameBreaker {

    int ini::open(str fname) {
        int msize = __gb_inis.size();
        __gb_inis.resize(msize + 1);
        __gb_inis[msize]=retiin(fname);
        return msize;
    }

    int ini::read_int(int file, str section, str keyName, int defKey)  {
        return __gb_inis[file]->isSectionExists(section)?(*__gb_inis[file])[section].toInt(keyName):defKey;
    }

    str ini::read_str(int file, str section, str keyName, str defKey)  {
        return __gb_inis[file]->isSectionExists(section)?(*__gb_inis[file])[section].toString(keyName):defKey;
    }

    void ini::write_int(int file, str section, str key, int num) {
        __gb_inis[file]->modify(section,key,num);
    }

    void ini::write_str(int file, str section, str key, str txt) {
        __gb_inis[file]->modify(section,key,txt);
    }

    void ini::close(int file) {
        delete __gb_inis[file];
        __gb_inis.erase(__gb_inis.begin()+file); 
    }

} // namespace GameBreaker
