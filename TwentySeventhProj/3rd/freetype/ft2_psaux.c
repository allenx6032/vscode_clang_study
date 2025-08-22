/***************************************************************************/
/*                                                                         */
/*  psaux.c                                                                */
/*                                                                         */
/*    FreeType auxiliary PostScript driver component (body only).          */
/*                                                                         */
/*  Copyright 1996-2001, 2002, 2006 by                                     */
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
#include "freetype/ft2_psobjs.c.h"
#include "freetype/ft2_psauxmod.c.h"
#include "freetype/ft2_t1decode.c.h"
#include "freetype/ft2_t1cmap.c.h"

#ifndef T1_CONFIG_OPTION_NO_AFM
#include "freetype/ft2_afmparse.c.h"
#endif

#include "freetype/ft2_psconv.c.h"


/* END */
