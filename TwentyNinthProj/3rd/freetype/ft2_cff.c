/***************************************************************************/
/*                                                                         */
/*  cff.c                                                                  */
/*                                                                         */
/*    FreeType OpenType driver component (body only).                      */
/*                                                                         */
/*  Copyright 1996-2001, 2002, 2013 by                                     */
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

#include "freetype/ft2_cffpic.c.h"
#include "freetype/ft2_cffdrivr.c.h"
#include "freetype/ft2_cffparse.c.h"
#include "freetype/ft2_cffload.c.h"
#include "freetype/ft2_cffobjs.c.h"
#include "freetype/ft2_cffgload.c.h"
#include "freetype/ft2_cffcmap.c.h"

#include "freetype/ft2_cf2arrst.c.h"
#include "freetype/ft2_cf2blues.c.h"
#include "freetype/ft2_cf2error.c.h"
#include "freetype/ft2_cf2font.c.h"
#include "freetype/ft2_cf2ft.c.h"
#include "freetype/ft2_cf2hints.c.h"
#include "freetype/ft2_cf2intrp.c.h"
#include "freetype/ft2_cf2read.c.h"
#include "freetype/ft2_cf2stack.c.h"

/* END */
