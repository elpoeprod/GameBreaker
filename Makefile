CXX_COMPILER=g++
CXX_ARGS=-c -Wall -Werror -fpic -g -ggdb
CXX_ARGS_LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf  #-lSDL2_main
CXX_ARGS_SOLOUD=include/SoLoud/libSoLoud_MA.a
CXX_ARGS_GTK=`pkg-config --libs --cflags gtk+-3.0`
CXX_ARGS_TAGLIB=`pkg-config --libs --cflags taglib`
CXX_ARGS_OPENMPT=-lopenmpt#`pkg-config --libs --cflags openmpt`
CXX_CMD=$(CXX_COMPILER) $(CXX_ARGS)
LIB_NAME=libgb.so

all:
	mkdir -p ./build/
	$(CXX_CMD) gb/window.cpp 	-o build/window.o
	$(CXX_CMD) gb/sound.cpp 	-o build/sound.o $(CXX_ARGS_SOLOUD) $(CXX_ARGS_TAGLIB) $(CXX_ARGS_OPENMPT)
	$(CXX_CMD) gb/display.cpp 	-o build/display.o
	$(CXX_CMD) gb/graphics.cpp 	-o build/graphics.o
	$(CXX_CMD) gb/object.cpp 	-o build/object.o
	$(CXX_CMD) gb/room.cpp 	-o build/room.o
	$(CXX_CMD) gb/msg.cpp 	-o build/msg.o $(CXX_ARGS_GTK)
	$(CXX_CMD) gb/fs.cpp 	-o build/fs.o $(CXX_ARGS_GTK)
	$(CXX_CMD) gb/font.cpp 	-o build/font.o
	$(CXX_CMD) gb/system.cpp 	-o build/main.o $(CXX_ARGS_SOLOUD) $(CXX_ARGS_TAGLIB) $(CXX_ARGS_OPENMPT)
	$(CXX_CMD) gb/str.cpp 	-o build/str.o
	$(CXX_CMD) gb/math.cpp 	-o build/math.o
	$(CXX_CMD) gb/list.cpp 	-o build/list.o
	$(CXX_CMD) gb/keyboard.cpp 	-o build/kbd.o
	$(CXX_CMD) gb/mouse.cpp 	-o build/mouse.o
	$(CXX_CMD) gb/ini.cpp 	-o build/ini.o
	$(CXX_CMD) gb/joystick.cpp -o build/joy.o
	$(CXX_CMD) gb/surface.cpp  -o build/surf.o
	$(CXX_CMD) gb/color.cpp  -o build/color.o
	$(CXX_CMD) gb/3rdparty/nfd/nfd_gtk.cpp -o build/nfd.o $(CXX_ARGS_GTK)
	$(CXX_COMPILER) -g -ggdb -fpic -rdynamic -Lstatic -Wall -Werror -shared -o $(LIB_NAME) build/*.o $(CXX_ARGS_LIBS) $(CXX_ARGS_GTK) include/SoLoud/libSoLoud_MA.a -lasound $(CXX_ARGS_TAGLIB) $(CXX_ARGS_OPENMPT) #-lstatic 

install:
	rm -rf /usr/local/include/gamebreaker/
	rm /usr/lib/$(LIB_NAME)
	cp -rf include/ /usr/local/include/gamebreaker/
	cp $(LIB_NAME) /usr/lib/

windows:
	echo Not implemented. Linux is the only supported OS at this time.

archive:
	7z a libgb.zip include/ gb/

compiled_archive:
	7z a libgb_compiled.zip libgb.so include/

compile_games:
	find -wholename "examples/*/*.cpp" -exec g++ {} -o {}".o" -lgb -O3 \;
