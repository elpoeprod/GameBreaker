Changelog updates from 08.21.2025.

0.0.17
- fixed `mouse::which()` function.
- added `surface` class, with `add()`, `clone()`, `target_set()` and `target_reset()` functions. They are used to draw in them without touching any other drawable outside of `GBSurface` surface.
- additionally to this, `graphics::draw::surface()` was added to draw surfaces.
- added `fs::create_folder()` function to create directories.
- added `taglib` support to get tags from audio files. Now requires `taglib` to compile GameBreaker.
- updated `SoLoud` audio library. Now requires `libopenmpt` to compile GameBreaker.
- added `fs::fname()` to get filename from full path string. (or other types of path string)
- added `graphics::sprite::replace()` and `replace_ext()` functions to replace sprites.
- added `audio::get_fft()` and `get_wave()`. WARNING! Can be laggy. ANOTHER WARNING! Every second byte in audio buffer() is second channel. 
Use those functions like this: `int i=0; repeat(50) {draw::point(i,50-audio::get_wave(sndMusic,i*2)); i++;}`
- updated `graphics::draw::line()` function, now it receives `float` variables instead of `int`.
- updated `graphics::draw::alpha()` function, now it can receive only a number in between 0..1.


0.0.16
- renamed `GB_INIT_WIN_FLAGS` to `GB_INIT_REN_FLAGS`.
- added `GB_INIT_WIN_FLAGS` for window creation flags used in `::init()`.
- audio sample size now works.
- fixed objects' create event isn't initializing.
- fixed drawables are not drawing even with camera enabled.
- fixed setting object position in `room::add_instance`.
- fixed sprite width and height. to get full sprite width, do `spr->w*spr->frames`.
- added `GBObject *self` argument to event functions, to handle `self` instead of full object name.
- fixed drawables are drawing many times if there are many objects with the same depths
- new function `object::event_add()` to easily add events to an object.

0.0.15
- now you can access GameBreaker version with `GameBreaker::gb_version` variable.
- `mouse::wheel_up()` and `mouse::wheel_down()` functions added.
