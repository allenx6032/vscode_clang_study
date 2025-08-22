/***************************************************************************/
/*                                                                         */
/*  autofit.c                                                              */
/*                                                                         */
/*    Auto-fitter module (body).                                           */
/*                                                                         */
/*  Copyright 2003-2007, 2011, 2013 by                                     */
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
#include "freetype/ft2_afpic.c.h"
#include "freetype/ft2_afangles.c.h"
#include "freetype/ft2_afblue.c.h"
#include "freetype/ft2_afglobal.c.h"
#include "freetype/ft2_afhints.c.h"

#include "freetype/ft2_afranges.c.h"

#include "freetype/ft2_afdummy.c.h"
#include "freetype/ft2_aflatin.c.h"
#ifdef FT_OPTION_AUTOFIT2
#include "freetype/ft2_aflatin2.c.h"
#endif
#include "freetype/ft2_afcjk.c.h"
#include "freetype/ft2_afindic.c.h"

#include "freetype/ft2_hbshim.c.h"

#include "freetype/ft2_afloader.c.h"
#include "freetype/ft2_afmodule.c.h"

#ifdef AF_CONFIG_OPTION_USE_WARPER
#include "freetype/ft2_afwarp.c.h"
#endif

/* END */
