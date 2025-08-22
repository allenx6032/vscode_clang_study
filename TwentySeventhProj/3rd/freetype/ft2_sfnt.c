/***************************************************************************/
/*                                                                         */
/*  sfnt.c                                                                 */
/*                                                                         */
/*    Single object library component.                                     */
/*                                                                         */
/*  Copyright 1996-2006, 2013 by                                           */
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
#include "freetype/ft2_sfntpic.c.h"
#include "freetype/ft2_ttload.c.h"
#include "freetype/ft2_ttmtx.c.h"
#include "freetype/ft2_ttcmap.c.h"
#include "freetype/ft2_ttkern.c.h"
#include "freetype/ft2_sfobjs.c.h"
#include "freetype/ft2_sfdriver.c.h"

#ifdef TT_CONFIG_OPTION_EMBEDDED_BITMAPS
#include "freetype/ft2_pngshim.c.h"
#include "freetype/ft2_ttsbit.c.h"
#endif

#ifdef TT_CONFIG_OPTION_POSTSCRIPT_NAMES
#include "freetype/ft2_ttpost.c.h"
#endif

#ifdef TT_CONFIG_OPTION_BDF
#include "freetype/ft2_ttbdf.c.h"
#endif

/* END */
