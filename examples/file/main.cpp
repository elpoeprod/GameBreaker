#define GB_USE_SMALL_FUNCNAMES
#include <gamebreaker/gamebreaker.hpp>
namespace gb=GameBreaker;

int main(int argc,char **argv) {
	gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"File write test");
	std::string myargv[argc];
	for(int i=0;i<argc;i++) {
		myargv[i]=argv[i];
	}
	if(myargv[1]=="write") {
		var myfile=file::text::open("testfile.txt",file::fmode::write);
		file::text::write(myfile,"Hello, GameBreaker text file!\n\nTESTTEST");
		file::text::ln(myfile);
		file::text::write(myfile,"This is another line!");
		file::text::close(myfile);
	}
	if(myargv[1]=="read") {
		var newfile=file::text::open("testfile.txt",file::fmode::read);
		while(!file::text::eof(newfile)) puts(file::text::read(newfile).c_str());
		file::text::close(newfile);
	}
	gb::shutdown();
}
