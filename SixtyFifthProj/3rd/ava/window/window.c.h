#ifndef WINDOW_H
#define WINDOW_H
#   ifndef UNICODE
#   define UNICODE // for glfw3.c (win32)
#   endif
#   define GLAD_IMPLEMENTATION
#   include "../engine.h"
#endif

#ifdef WINDOW_C
#pragma once
#define APP_C
#define MODULE_C
#define GETOPT_C
#define UI_C
#define ICON_C
#define TRAY_C
#endif

#include "../render/render.c.h" // opengl, pass

#include "window_ui.c.h"
#include "window_icon.c.h"
#include "window_tray.c.h"
#include "window_app.c.h"
#include "window_module.c.h"
#include "window_getopt.c.h"
