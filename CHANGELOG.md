Changelog updates from 08.21.2025.

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
