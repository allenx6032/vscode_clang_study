/**********************************************************************************************
*
*   rglfw - raylib GLFW single file compilation
*
*   This file includes latest GLFW sources (https://github.com/glfw/glfw) to be compiled together
*   with raylib for all supported platforms, this way, no external dependencies are required.
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2017-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

//#define _BUILD_DLL           // To build shared version
// Ref: http://www.glfw.org/docs/latest/compile.html#compile_manual

// Platform options:
// _WIN32      to use the Win32 API
// _X11        to use the X Window System
// _WAYLAND    to use the Wayland API (experimental and incomplete)
// _COCOA      to use the Cocoa frameworks
// _OSMESA     to use the OSMesa API (headless and non-interactive)
// _MIR        experimental, not supported at this moment

#if defined(_WIN32) || defined(__CYGWIN__)
    #define _WIN32
#endif
#if defined(__linux__)
    #if !defined(_WAYLAND)     // Required for Wayland windowing
        #define _X11
    #endif
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #define _X11
#endif
#if defined(__APPLE__)
    #define _COCOA
    #define _USE_MENUBAR       // To create and populate the menu bar when the first window is created
    #define _USE_RETINA        // To have windows use the full resolution of Retina displays
#endif
#if defined(__TINYC__)
    #define _WIN32_WINNT_WINXP      0x0501
#endif

// Common modules to all platforms
#include "context.c.h"
#include "init.c.h"
#include "input.c.h"
#include "monitor.c.h"
#include "vulkan.c.h"
#include "window.c.h"

#if defined(_WIN32) || defined(__CYGWIN__)
    #include "win32_init.c.h"
    #include "win32_joystick.c.h"
    #include "win32_monitor.c.h"
    #include "win32_time.c.h"
    #include "win32_thread.c.h"
    #include "win32_window.c.h"
    #include "wgl_context.c.h"
    #include "egl_context.c.h"
    #include "osmesa_context.c.h"
#endif

#if defined(__linux__)
    #if defined(_WAYLAND)
        #include "wl_init.c"
        #include "wl_monitor.c"
        #include "wl_window.c"
        #include "wayland-pointer-constraints-unstable-v1-client-protocol.c"
        #include "wayland-relative-pointer-unstable-v1-client-protocol.c"
        #endif
    #if defined(_X11)
        #include "x11_init.c"
        #include "x11_monitor.c"
        #include "x11_window.c"
        #include "glx_context.c"
    #endif

    #include "linux_joystick.c"
    #include "posix_thread.c"
    #include "posix_time.c"
    #include "xkb_unicode.c"
    #include "egl_context.c"
    #include "osmesa_context.c"
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined( __NetBSD__) || defined(__DragonFly__)
    #include "x11_init.c"
    #include "x11_monitor.c"
    #include "x11_window.c"
    #include "xkb_unicode.c"
    #include "null_joystick.c"
    #include "posix_time.c"
    #include "posix_thread.c"
    #include "glx_context.c"
    #include "egl_context.c"
    #include "osmesa_context.c"
#endif

#if defined(__APPLE__)
    #include "cocoa_init.m"
    #include "cocoa_joystick.m"
    #include "cocoa_monitor.m"
    #include "cocoa_window.m"
    #include "cocoa_time.c"
    #include "posix_thread.c"
    #include "nsgl_context.m"
    #include "egl_context.c"
    #include "osmesa_context.c"
#endif
