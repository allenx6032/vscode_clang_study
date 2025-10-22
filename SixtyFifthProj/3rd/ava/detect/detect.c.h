#ifdef CONFIG_H
#include CONFIG_H
#endif

// @todo -> rename as MACROS instead

#undef DETECT_C
#ifdef DETECT_C
#pragma once
#define API_C
#define AUTO_C
#define AUTORUN_C
#define BITS_C
#define CALLSTACK_C
#define CAST_C
#define INCLUDES_C
#define INLINE_C
#define LINKAGE_C
#define MEMORY_C
#define PLATFORM_C
#define RESTRICT_C
#define SHORTFILE_C
#define TEST_C
#define THREADLOCAL_C
#define TYPES_C
#define VA_C
#define ENDIAN_C
#endif

#include "detect_assert.c.h"

#include "detect_api.c.h"
#include "detect_auto.c.h"
#include "detect_autorun.c.h"
#include "detect_bits.c.h"
#include "detect_callstack.c.h"
#include "detect_cast.c.h"
#include "detect_countof.c.h"
#include "detect_includes.c.h"
#include "detect_inline.c.h"
#include "detect_linkage.c.h"
#include "detect_memory.c.h"
#include "detect_platform.c.h"
#include "detect_restrict.c.h"
#include "detect_shortfile.c.h"
#include "detect_test.c.h"
#include "detect_threadlocal.c.h"
#include "detect_types.c.h"
#include "detect_endian.c.h"

#include "detect_va.c.h"
