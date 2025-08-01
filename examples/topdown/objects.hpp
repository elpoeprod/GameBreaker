#pragma once
#include "main.hpp"

#ifndef object
#define object extern GBObject *
#define sprite extern GBSprite *
#endif

object objPlayer;
object objEffector;


sprite sprCursor;

extern void init_objects();
#ifdef object
#undef object
#undef sprite
#endif
