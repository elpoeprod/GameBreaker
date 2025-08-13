#define GB_USE_SMALL_FUNCNAMES
#include <gamebreaker/gamebreaker.hpp>
namespace gb=GameBreaker;

int main() {
	gb::init(GB_WINPOS_CENTER,GB_WINPOS_CENTER,"File write test");
	puts("1");
	var myfile=file::text::open("testfile.txt",file::fmode::write);
	puts("11");
	file::text::write(myfile,"Hello, GameBreaker text file!");
	puts("111");
	file::text::ln(myfile);
	puts("1111");
	file::text::write(myfile,"This is another line!");
	puts("11111");
	file::text::close(myfile);

	puts("111111");
	var newfile=file::text::open("testfile.txt",file::fmode::read);
	puts("1111111");
	show::message("TEST",file::text::read(newfile));
	puts("11111111");
	file::text::close(newfile);
	puts("111111111");
	gb::shutdown();
}
