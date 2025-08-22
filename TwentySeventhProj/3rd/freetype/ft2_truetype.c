/***************************************************************************/
/*                                                                         */
/*  truetype.c                                                             */
/*                                                                         */
/*    FreeType TrueType driver component (body only).                      */
/*                                                                         */
/*  Copyright 1996-2001, 2004, 2006, 2012 by                               */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


#define FT_MAKE_OPTION_SINGLE_OBJECT

#include <freetype/ft2_build.h>
#include "freetype/ft2_ttpic.c.h"
#include "freetype/ft2_ttdriver.c.h"   /* driver interface    */
#include "freetype/ft2_ttpload.c.h"    /* tables loader       */
#include "freetype/ft2_ttgload.c.h"    /* glyph loader        */
#include "freetype/ft2_ttobjs.c.h"     /* object manager      */

#ifdef TT_USE_BYTECODE_INTERPRETER
#include "freetype/ft2_ttinterp.c.h"
#include "freetype/ft2_ttsubpix.c.h"
#endif

#ifdef TT_CONFIG_OPTION_GX_VAR_SUPPORT
#include "freetype/ft2_ttgxvar.c.h"    /* gx distortable font */
#endif


/* END */
