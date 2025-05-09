# GameBreaker
GameMaker functions for C++ using SDL2

## Features:
- can add fonts, sprites, sounds
- can create objects (useful for player instances or buttons)
- window manipulating functions
- some useful math functions
- INI support (untested)
- File/folder dialogs (untested)
- can use 32 joysticks (0-31) (untested)
- can use keyboard!
- mouse/joystick functions
- additional to that, you can clear them using GameBreaker::io::clear()
- can draw circles
- can show message boxes
- can create ds_lists and ds_maps (limited)
- can find files/folders in some folder using GameBreaker::fs::find::list(). returns ds_list with all found files
- can open files (write-only for now, read mode will be soon)

## Used libraries:
- [SDL2](https://github.com/libsdl-org/) - zlib license
- [inicpp](https://github.com/dujingning/inicpp) - MIT license
- [nativefiledialog-extended](https://github.com/btzy/nativefiledialog-extended) - zlib license
