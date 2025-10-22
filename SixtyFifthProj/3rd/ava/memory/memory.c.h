#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef MEMORY_C
#pragma once
#define WATCH_C
#define REALLOC_C
#define MALLOCA_C
#define VREALLOC_C
#endif

#include "memory_watch.c.h"
#include "memory_realloc.c.h"
#include "memory_malloca.c.h"
#include "memory_vrealloc.c.h"
