#define SOKOL_IMPL
#if defined(_WIN32)
#define SOKOL_D3D11
#elif defined(__EMSCRIPTEN__)
#define SOKOL_GLES2
#elif defined(__APPLE__)
#define SOKOL_METAL
#else
#define SOKOL_GLCORE33
#endif
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_time.h"
#include "sokol/sokol_fetch.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_log.h"

#include "sokol/sokol_gl.h"
#include <stdio.h> // fontstash requires this
#include <stdlib.h> // fontstash requires this
#define FONTSTASH_IMPLEMENTATION
#include "fontstash/fontstash.h"
#define SOKOL_FONTSTASH_IMPL
#include "sokol/sokol_fontstash.h"
