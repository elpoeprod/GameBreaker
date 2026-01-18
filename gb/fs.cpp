/*
 * Filesystem functions
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"
#include "../include/nfd/nfd.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstring>

int strcasecmp(str str1, str str2) {
	for(luint i=0; i<str1.length();i++) {
		for(luint ii=0; ii<str2.length();ii++) {
			str ms;ms+=(char)tolower(str1[i]);
			str md;md+=(char)tolower(str2[ii]);
			return strcmp(ms.c_str(),md.c_str());
		}
	}
	return 1;
}

namespace GameBreaker {

    std::vector<_gm_file *>gb_files;

    /**
    * returns true (1) if file/directory exists, otherwise return false (0)
    **/
    int fs::exists(std::string fname)
    {
        return std::filesystem::exists(fname);
    }


    /**
    * returns ds_list that contains all the files in directory found with filter and mask
    * \sa directory - directory
    * \sa filter - thing like "*.ogg;*.wav" or "*.* .fla"
    * \sa mask - fa::*
    **/
    ds_list fs::find::list(str directory, str filter, luint mask)
    {
        ds_list list;

        int i_path=mask&fa::fullpath,
            i_dir=mask&fa::dir;

        struct dirent* d = nullptr;
        DIR* dir = opendir(directory.c_str());

        std::string mynewdir=directory;
        if (strcasecmp(&mynewdir[mynewdir.length()-1],"/")!=0)
            mynewdir = directory + "/";

        while ((d = readdir(dir)) != nullptr) {
            std::filesystem::path temp = d->d_name;
            std::string temptemp=temp.extension();
            if(temp.compare(".") != 0 && temp.compare("..") != 0) {
                if((d->d_type==DT_REG&&!i_dir)) {
                    if(temptemp.find(filter)!=std::string::npos) {
                        list.push_back({d->d_type,i_path?mynewdir+d->d_name:d->d_name});
                    }
                }
                if(d->d_type==DT_DIR&&i_dir) {
                    list.push_back({d->d_type,i_path?mynewdir+d->d_name:d->d_name});
                }
            }
        }
        closedir(dir);
        delete[] d;
        return list;
    }

    ds_list fs::find::list_ext(str directory, std::vector<str> filter, luint mask)
    {
        ds_list list;

        int i_path=mask&fa::fullpath,
        i_dir=mask&fa::dir;

        struct dirent* d = nullptr;
        DIR* dir = opendir(directory.c_str());

        std::string mynewdir=directory;
        if (strcasecmp(&mynewdir[mynewdir.length()-1],"/")!=0)
            mynewdir = directory + "/";

        while ((d = readdir(dir)) != nullptr) {
            std::filesystem::path temp = d->d_name;
            std::string temptemp=temp.extension();
            if(temp.compare(".") != 0 && temp.compare("..") != 0) {
                if((d->d_type==DT_REG&&!i_dir)) {
                    for(int i=0;i<(int)filter.size();i++) {
                        if(temptemp.find(filter[i])!=std::string::npos) {
                            list.resize(list.size()+1);
                            list[list.size()-1].type=d->d_type;
                            list[list.size()-1].data=i_path ? mynewdir+d->d_name : d->d_name;
                            break;
                        }
                    }
                }
                if(d->d_type==DT_DIR&&i_dir) {
                    list.resize(list.size()+1);
                    list[list.size()-1].type=d->d_type;
                    list[list.size()-1].data=i_path ? mynewdir+d->d_name : d->d_name;
                }
            }
        }
        closedir(dir);
        delete[] d;
        return list;
    }

    str fs::path(str fname) {
        return fname.substr(0,fname.find_last_of("/\\"))+"/";
    }


    int fs::text::open(str fname, int mode) {
        _gm_file *f=new _gm_file;
        auto md=(mode==fs::fmode::read) ? std::ios::in : (mode==fs::fmode::write) ? std::ios::out|std::ios::trunc : std::ios::app;
        f->file.a.open(fname,md);
        f->mode=mode;
        f->line=0;
        f->name=fname;
        gb_files.push_back(f);
        return gb_files.size()-1;
    }

    void fs::text::write(int file,str str) {
    	if(gb_files[file]->mode!=(int)fs::fmode::write) {show::error("Can't write to read-only file! Filename: "+gb_files[file]->name,1); return;}
        gb_files[file]->file.a<<str;
        return;
    }
    
    str fs::text::read(int file) {
    	if(gb_files[file]->mode!=(int)fs::fmode::read) {show::error("Can't read write-only file! Filename: "+gb_files[file]->name,1); return "";}
    	str buff;
    	getline(gb_files[file]->file.a,buff);
    	return buff;
    }

    int fs::text::eof(int file) {
    	return gb_files[file]->file.a.eof();
    }

    void fs::text::ln(int file) {
    	if(gb_files[file]->mode==fs::fmode::write) gb_files[file]->file.a<<"\n";
    	else {
    		str buff;
    		if(getline(gb_files[file]->file.a,buff)) gb_files[file]->line++;
    	}
    }

    void fs::text::close(int file) {
        gb_files[file]->file.a.close();
        //gb_files[file]->file.a=nullptr;
        gb_files[file]->mode=0;
        delete gb_files[file];
        gb_files.erase(gb_files.begin() + file);
    }

    str fs::fname(str fname) {
    	auto mypos=fname.find_last_of("/\\")+1;
    	return gstr::copy(fname,mypos,fname.length()-mypos);
    }

    str fs::path_parent(str path) {
        std::filesystem::path mypath=path;
        return mypath.parent_path();
    }

    str fs::get_fname(std::vector<fname_list> filter, str title) {

        NFD::Guard __nfd_g;

        NFD::UniquePath _mypath;

        nfdfilteritem_t _filter[filter.size()];
        for(int i=0;i<(int)filter.size();i++) {
            _filter[i]={filter[i].title.c_str(),filter[i].filter.c_str()};
        }
        nfdresult_t __res=NFD::OpenDialog(_mypath,title,_filter);
        if(__res==NFD_OKAY) 
            return _mypath.get();

        return "";
    
    }

    str fs::get_folder(str title) {
        NFD::Guard __nfd_g;

        NFD::UniquePath _mypath;

        nfdresult_t _res=NFD::PickFolder(_mypath,title);
        if(_res==NFD_OKAY) 
            return _mypath.get();

        return "";
    }

    void fs::create_folder(str path) {
		std::filesystem::create_directory(path);
    	return;
    }
    
}
