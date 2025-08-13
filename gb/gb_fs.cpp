#include "../include/gamebreaker.hpp"
#include "../include/nfd/nfd.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

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
    ds_list fs::find::list(gb_str directory, gb_str filter, Uint32 mask)
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

    ds_list fs::find::list_ext(gb_str directory, std::vector<std::string> filter, Uint32 mask)
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

    gb_str fs::path(gb_str fname) {
        return fname.substr(0,fname.find_last_of("/\\"))+"/";
    }


    int fs::text::open(gb_str fname, enum fs::fmode mode) {
        _gm_file *f=new _gm_file;
        f->file.a.open(fname,(std::ios_base::openmode)mode);
        f->mode=mode;
        f->line=0;
        gb_files.resize(gb_files.size()+1);
        gb_files[gb_files.size()-1]=f;
        return gb_files.size()-1;
    }

    void fs::text::write(int file,gb_str str) {
    	if(gb_files[file]->mode!=fs::fmode::write) {show::error("Can't write to read-only file! File ID: "+stringify(file),1); return;}
        gb_files[file]->file.a<<str;
    }
    
    gb_str fs::text::read(int file) {
    	if(gb_files[file]->mode!=fs::fmode::read) {show::error("Can't write to read-only file! File ID: "+stringify(file),1); return undefined;}
    	gb_str buff;
    	getline(gb_files[file]->file.a,buff);
    	return buff;
    }

    void fs::text::ln(int file) {
    	if(gb_files[file]->mode==fs::fmode::write) gb_files[file]->file.a<<"\n";
    	else {
    		gb_str buff;
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

    gb_str fs::path_parent(gb_str path) {
        std::filesystem::path mypath=path;
        return mypath.parent_path();
    }

    gb_str fs::get_fname(std::vector<fname_list> filter, gb_str title) {

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

    gb_str fs::get_folder(gb_str title) {
        NFD::Guard __nfd_g;

        NFD::UniquePath _mypath;

        nfdresult_t _res=NFD::PickFolder(_mypath,title);
        if(_res==NFD_OKAY) 
            return _mypath.get();

        return "";
    }
    
}
