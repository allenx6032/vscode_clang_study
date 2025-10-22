#ifdef RENDER_C
#pragma once
#define OPENGL_C

#define SHADER_C
#define SHADER2_C
#define TEXTURE_C
#define TEXTURE2_C
#define FBO2_C
#define MESH_C
#define VIEWPORT2_C
#define MATERIAL2_C
#define MESH_C
#define MESH2_C
#define CUBEMAP_C

#define DDRAW2_C
#define FONT_C
#define DDRAW_C
#define POSTFX_C

#define SHADER3_C
#define PBR_C
#endif

#include <stdlib.h>

#include "render_opengl.c.h"

#include "render_shader.c.h"
#include "render_shader2.c.h"
#include "render_texture.c.h"
#include "render_texture2.c.h"
#include "render_fbo2.c.h"
#include "render_viewport2.c.h"
#include "render_material2.c.h"
#include "render_mesh.c.h"
#include "render_mesh2.c.h"
#include "render_cubemap.c.h"

#include "render_ddraw2.c.h"
#include "render_font.c.h"
#include "render_ddraw.c.h"
#include "render_postfx.c.h"

#include "render_shader3.c.h"
#include "render_pbr.c.h"
