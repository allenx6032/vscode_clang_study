#ifdef __cplusplus
extern "C" {
#endif

#ifdef CORE_C
#pragma once
#define ASYNC_C
#define DEBUG_C
#define DETECT_C
#define MEMORY_C
#define OBJECT_C
#define NATIVE_C
#define STRING_C
#define STRUCT_C
#define TIME_C
#endif

#include "ava/engine_config.c.h"

#include "ava/object/object.c.h"
#include "ava/detect/detect.c.h"
#include "ava/memory/memory.c.h"
#include "ava/struct/struct.c.h"
#include "ava/async/async.c.h"
#include "ava/debug/debug.c.h"
#include "ava/native/native.c.h"
#include "ava/time/time.c.h"
#include "ava/string/string.c.h"

#include "ava/math/math.c.h"

#ifdef __cplusplus
}
#endif
